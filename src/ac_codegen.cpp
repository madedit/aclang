/* see copyright notice in aclang.h */

#include "ac_ast.h"
#include "ac_codegen.h"
#include "ac_gc.h"
#include "ac_vm.h"
#include "llvm/IR/LegacyPassManager.h"
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include <sstream>
#include <setjmp.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

using namespace llvm;

acCodeGenerator::acCodeGenerator(acVM* vm)
    : m_vm(vm)
    , m_msgHandler(vm->getMsgHandler())
    , m_gc(vm->getGarbageCollector())
    , m_programBlockAST(0)
    , m_mainFunction(0)
    , m_irBuilder(vm->getLLVMContext())
    , m_blocks()
{
    m_rootTable = (acTable*)m_gc->createObject(acVT_TABLE);
    m_rootTableVar = (acVariable*)m_gc->createObject(acVT_VAR);
    m_rootTableVar->setValue(m_rootTable);
    m_gc->addRootObj(m_rootTableVar);

    m_rootArgArray = (acArray*)m_gc->createObject(acVT_ARRAY);
    m_gc->addRootObj(m_rootArgArray);

    m_rootTmpArray = (acArray*)m_gc->createObject(acVT_ARRAY);
    m_gc->addRootObj(m_rootTmpArray);
}

acCodeGenerator::~acCodeGenerator()
{
}

acGarbageCollector* acCodeGenerator::getGarbageCollector()
{
    return m_gc;
}

LLVMContext& acCodeGenerator::getLLVMContext()
{
    return m_vm->getLLVMContext();
}

Module* acCodeGenerator::getModule()
{
    return m_vm->getCurrentModule();
}

void acCodeGenerator::generateCode()
{
    eraseMainFunction();

    if(m_programBlockAST == 0)
    {
        m_vm->getMsgHandler()->error("ProgramBlock is NULL, ignore...\n");
        return;
    }

    m_isCompileError = false;

    LLVMContext& context = m_vm->getLLVMContext();
    Module* module = m_vm->getCurrentModule();

    //m_vm->getMsgHandler()->error("Generating code...\n");
    
    /* Create the top level interpreter function to call as entry */
    std::vector<Type*> argTypes;
    FunctionType* mainFuncType = FunctionType::get(IntegerType::get(context, 32), makeArrayRef(argTypes), false);

    static int count = 0;
    Twine mainName = Twine("main") + Twine(count++);

    m_mainFunction = Function::Create(mainFuncType, GlobalValue::InternalLinkage, mainName, module);

    /*  //main function:
        //entry:
        int int32_setjmp_ret = setjmp(jmpbuf);
        if( int32_setjmp_ret == 0)
        {
        //begin:
            script_main();
        }
        else
        {
            //encounter error!!!
        }
        //end
    */

    //blocks
    BasicBlock* label_entry = BasicBlock::Create(context, "entry", m_mainFunction);
    BasicBlock* label_begin = BasicBlock::Create(context, "begin", m_mainFunction);
    BasicBlock* label_end = BasicBlock::Create(context, "end", m_mainFunction);
    
    m_irBuilder.SetInsertPoint(label_entry);

    //types
    Type* voidTy = Type::getVoidTy(context);
    PointerType* voidPtrTy = PointerType::get(Type::getInt8Ty(context), 0);
    IntegerType* int32Ty = IntegerType::get(context, 32);

    //consts
    ConstantInt* const_int32_0 = ConstantInt::get(context, APInt(32, 0));
    ConstantInt* const_int32_1 = ConstantInt::get(context, APInt(32, 1));

    //entry:
    //int32_setjmp_ret = setJmp(m_gf_setJmp);
    Constant* voidPtr_errorJmpBuf = ConstantExpr::getCast(Instruction::BitCast, m_gv_errorJmpBuf, voidPtrTy);
    CallInst* int32_setjmp_ret = m_irBuilder.CreateCall(m_gf_setJmp, voidPtr_errorJmpBuf, "setjmp_ret");
    int32_setjmp_ret->setCallingConv(CallingConv::C);

    //CallInst::Create(echoFunc, int32_setjmp_ret, "", label_entry);

    //if(int32_setjmp_ret == 0) goto label_begin; else goto label_end;
    Value* int1_cmp = m_irBuilder.CreateICmpEQ(int32_setjmp_ret, const_int32_0, "cmp");
    m_irBuilder.CreateCondBr(int1_cmp, label_begin, label_end);

    //label_begin:
    //call script_main()
    /* longjmp test * /
    Constant* voidPtr_cg = ConstantExpr::getCast(Instruction::BitCast, m_gv_cg, voidPtrTy);
    std::vector<Value*> longjmp_params;
    longjmp_params.push_back(voidPtr_cg);
    longjmp_params.push_back(const_int32_1);
    CallInst* void_call_lj = CallInst::Create(m_gf_longJmp, longjmp_params, "", label_begin);
    void_call_lj->setCallingConv(CallingConv::C);
    / * */

    m_irBuilder.SetInsertPoint(label_begin);

    Value* retVar = m_irBuilder.CreateCall3(m_gf_newArrayVar, m_gv_rootArgArray, m_irBuilder.getInt32(-1), m_gv_vm, "retVar");

    /* Push a new variable/block context */
    pushBlock(label_begin, label_end, m_programBlockAST, acCodeGenBlock::FUNCTION,
              retVar, m_gv_rootTableVar, m_gv_rootArgArray, m_gv_rootTmpArray, 0,
              &m_stringList, &m_funcDataList, &m_debugInfoList);

    currentBlock()->m_localVars.push_back(std::make_pair("this", m_gv_rootTableVar));
    m_programBlockAST->codeGen(this); /* emit bytecode for the toplevel block */

    popBlock();

    //goto label_end
    m_irBuilder.CreateBr(label_end);

    //label_end:
    //return int32_setjmp_ret
    m_irBuilder.SetInsertPoint(label_end);
    m_irBuilder.CreateRet(int32_setjmp_ret);

    if(m_vm->getPrintIR())
    {
        m_vm->getMsgHandler()->error(">>>LLVM IR<<<\n");
        legacy::PassManager pm;
        pm.add(createPrintModulePass(outs()));
        pm.run(*module);
    }
}


GenericValue acCodeGenerator::runCode()
{
    if(m_mainFunction != 0)
    {
        //m_vm->getMsgHandler()->error("Running code...\n");
        ExecutionEngine* ee = m_vm->getCurrentExecutionEngine();
        ee->finalizeObject();

        std::vector<GenericValue> noargs;
        GenericValue v = ee->runFunction(m_mainFunction, noargs);
        //printf("ret = %d\n", v.IntVal.getZExtValue());
        if(v.IntVal.getZExtValue() == 0)
        {
            //m_msgHandler->error("Code was run.\n");
        }
        else
        {
            m_msgHandler->error("Encounter error!\n");
        }

        //release unused data
        m_rootArgArray->m_data.clear();
        m_rootTmpArray->m_data.clear();
        m_stringList.clear();
        m_funcDataList.clear();
        m_debugInfoList.clear();

        return v;
    }

    return GenericValue();
}

void acCodeGenerator::pushBlock(BasicBlock* bblock, BasicBlock* leave,
    NodeAST* ast, acCodeGenBlock::BlockType type,
    Value* retVar, Value* thisVar, Value* argArray,
    Value* tmpArray, int tmpArraySize,
    std::list<std::string>* strList, std::list<acGCObject*>* funcDataList,
    std::list<acDebugInfo>* debugInfoList)
{
    acCodeGenBlock* block = new acCodeGenBlock();
    block->m_bblock = bblock;
    block->m_leave = leave;
    block->m_ast = ast;
    block->m_type = type;
    block->m_retVar = retVar;
    block->m_thisVar = thisVar;
    block->m_argArray = argArray;
    block->m_tmpArray = tmpArray;
    block->m_tmpArraySize = tmpArraySize;
    block->m_isBlockEnd = false;
    block->m_stringList = strList;
    block->m_funcDataList = funcDataList;
    block->m_debugInfoList = debugInfoList;
    m_blocks.push_front(block);
}

void acCodeGenerator::popBlock()
{
    acCodeGenBlock *top = m_blocks.front();
    m_blocks.pop_front();
    delete top;
}

Value* acCodeGenerator::findLocalVar(const std::string& name)
{
    std::list<acCodeGenBlock*> funcBlocks;
    Value* val = 0;

    std::list<acCodeGenBlock*>::iterator it = m_blocks.begin();
    std::list<acCodeGenBlock*>::iterator end = m_blocks.end();
    while(it != end && val == 0)
    {
        acCodeGenBlock* cgblock = *it;
        std::list<std::pair<std::string, Value*> >& localVars = cgblock->m_localVars;
        if(localVars.size() > 0)
        {
            std::list<std::pair<std::string, Value*> >::reverse_iterator rit = localVars.rbegin();
            std::list<std::pair<std::string, Value*> >::reverse_iterator rend = localVars.rend();

            while(rit != rend && val == 0)
            {
                if(rit->first == name)
                {
                    val = rit->second;
                    break;
                }
                ++rit;
            }
        }

        if(val == 0 && cgblock->m_type == acCodeGenBlock::FUNCTION)
        {
            funcBlocks.push_front(cgblock);
        }

        ++it;
    }

    //across function blocks
    if(val != 0 && funcBlocks.size() > 0)
    {
        it = funcBlocks.begin();
        end = funcBlocks.end();
        do
        {
            FunctionAST* ast = (FunctionAST*)((*it)->m_ast);
            val = ast->codeGenForUpValue(this, name, val);
        }
        while(++it != end);
    }

    return val;
}

acCodeGenBlock* acCodeGenerator::findWhereIsBreak()
{
    std::list<acCodeGenBlock*>::iterator it = m_blocks.begin();
    std::list<acCodeGenBlock*>::iterator end = m_blocks.end();
    while(it != end)
    {
        acCodeGenBlock* cgblock = *it;
        switch(cgblock->m_type)
        {
        case acCodeGenBlock::SWITCH:
        case acCodeGenBlock::WHILE:
        case acCodeGenBlock::DOWHILE:
        case acCodeGenBlock::FOR:
        case acCodeGenBlock::FOREACH:
            return cgblock;

        case acCodeGenBlock::FUNCTION:
            return 0;
        }

        ++it;
    }
    return 0;
}

acCodeGenBlock* acCodeGenerator::findWhereIsContinue()
{
    std::list<acCodeGenBlock*>::iterator it = m_blocks.begin();
    std::list<acCodeGenBlock*>::iterator end = m_blocks.end();
    while(it != end)
    {
        acCodeGenBlock* cgblock = *it;
        switch(cgblock->m_type)
        {
        case acCodeGenBlock::WHILE:
        case acCodeGenBlock::DOWHILE:
        case acCodeGenBlock::FOR:
        case acCodeGenBlock::FOREACH:
            return cgblock;

        case acCodeGenBlock::FUNCTION:
            return 0;
        }

        ++it;
    }
    return 0;
}

llvm::Value* acCodeGenerator::createStringPtr(const std::string& str, acCodeGenBlock* block, IRBuilder<>& builder)
{
    std::list<std::string>* strList = block->m_stringList;
    std::list<std::string>::iterator it = strList->begin(), end = strList->end();

    const char* strPtr = 0;
    for(; it != end; ++it)
    {
        if((*it) == str)
        {
            strPtr = it->c_str();
            break;
        }
    }
    
    if(strPtr == 0)
    {
        strList->push_back(str);
        strPtr = strList->back().c_str();
    }

    return builder.CreateIntToPtr(
            (sizeof(const char*) == sizeof(uint64_t) ?
                builder.getInt64((uintptr_t)strPtr) :
                builder.getInt32((uintptr_t)strPtr)
            ),
            builder.getInt8PtrTy()
        );
}

Value* acCodeGenerator::createDebugInfoPtr(int line, acCodeGenBlock* block, IRBuilder<>& builder)
{
    return createDebugInfoPtr(getMsgHandler()->getFileName().c_str(), line, block, builder);
}

Value* acCodeGenerator::createDebugInfoPtr(const char* file, int line, acCodeGenBlock* block, IRBuilder<>& builder)
{
    //add file to stringList
    std::list<std::string>* strList = block->m_stringList;
    std::list<std::string>::iterator it = strList->begin(), end = strList->end();

    const char* strPtr = 0;
    for(; it != end; ++it)
    {
        if((*it) == file)
        {
            strPtr = it->c_str();
            break;
        }
    }

    if(strPtr == 0)
    {
        strList->push_back(std::string(file));
        strPtr = strList->back().c_str();
    }

    block->m_debugInfoList->push_back(acDebugInfo());
    acDebugInfo* debugInfo = &(block->m_debugInfoList->back());
    debugInfo->file = strPtr;
    debugInfo->line = line;

    return builder.CreateIntToPtr(
            (sizeof(acDebugInfo*) == sizeof(uint64_t) ?
                builder.getInt64((uintptr_t)debugInfo) :
                builder.getInt32((uintptr_t)debugInfo)
            ),
            builder.getInt8PtrTy()
        );
}

void acCodeGenerator::eraseMainFunction()
{
    if(m_mainFunction != 0)
    {
        //ExecutionEngine* ee = m_vm->getExecutionEngine();
        //ee->freeMachineCodeForFunction(m_mainFunction);
        //m_mainFunction->replaceAllUsesWith(UndefValue::get(m_mainFunction->getType()));
        //m_mainFunction->deleteBody();
        //m_mainFunction->eraseFromParent();
        m_mainFunction = 0;
    }
}

void acCodeGenerator::createCoreFunctions()
{
    createGlobalValues();
    createGlobalFunctions();
}

namespace {
extern "C" {

// global functions in VM
int setErrorJmp(void* pjb)
{
    jmp_buf* jb = (jmp_buf*)pjb;
    int v = setjmp(*jb);
    //printf("setErrorJmp~~~~~%p~~~~~\n", jb);
    return v;
}

void myLongJmp(acCodeGenerator* cg, int v)
{
    //printf("myLongJmp~~~~~%p~~~~~%d\n", cg->getErrorJmpBuf(), v);
    longjmp(*cg->getErrorJmpBuf(), v);
}

void* newArrayVar(acArray* arr, int idx, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    if(idx < 0 || idx >= arr->size())
    {
        arr->m_data.push_back(var);
    }
    else
    {
        arr->m_data[idx] = var;
    }
    return var;
}

void setArrayVar(acArray* arr, int idx, acVariable* var, acVM* vm)
{
    if(idx < 0 || idx >= arr->size())
    {
        arr->m_data.push_back(var);
    }
    else
    {
        arr->m_data[idx] = var;
    }
}

void* getArrayVar_int(acArray* arr, int idx, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    if(idx < 0)
    {
        vm->runtimeError("Error: negtive index for getArrayVar()");
        return 0;
    }

    int size = arr->size();
    if(idx < size)
    {
        return arr->m_data[idx];
    }

    arr->m_data.resize(idx+1);
    acVariable* var;
    do
    {
        var = (acVariable*)gc->createObject(acVT_NULL);
        arr->m_data[size] = var;
    }
    while(++size < idx);

    return var;
}

void* getArrayVar(acArray* arr, acVariable* var, acVM* vm)
{
    int idx = toInt32(var, vm);
    return getArrayVar_int(arr, idx, vm);
}

void addTableKeyValue(acTable* tab, acVariable* key, acVariable* value, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    var->setValue(value);

    tab->add(key, var);
}

void addTableKeyValue_str(acTable* tab, char* name, acVariable* value, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* key = gc->createVarWithData(name);
    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    var->setValue(value);

    tab->add(key, var);
}

void* addTableVar(acTable* tab, acVariable* key, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    tab->add(key, var);
    return var;
}

void* addTableVar_str(acTable* tab, const char* name, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* key = (acVariable*)gc->createObject(acVT_VAR);
    acString* str = (acString*)gc->createObject(acVT_STRING);
    str->setData(name);
    key->setValue(str);

    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    tab->add(key, var);
    return var;
}

void* addTableVar_int32(acTable* tab, acInt32 idx, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* key = (acVariable*)gc->createObject(acVT_VAR);
    key->setValue(idx);

    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    tab->add(key, var);
    return var;
}

void* addTableVar_int64(acTable* tab, acInt64 idx, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* key = (acVariable*)gc->createObject(acVT_VAR);
    key->setValue(idx);

    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    tab->add(key, var);
    return var;
}

void* getTableVar(acTable* tab, char* name, acVM* vm)
{
    acVariable* var = tab->get(name);
    return var;
}

void* createUpValueTable(acVariable* funcVar, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acTable* tab = (acTable*)gc->createObject(acVT_TABLE);
    acFunction* func = (acFunction*)funcVar->m_gcobj;
    func->m_upValueTable = tab;
    return tab;
}

void createFunc(acVariable* funcVar, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acFunction* func = (acFunction*)gc->createObject(acVT_FUNCTION);
    funcVar->setValue(func);
}

void assignFunc(acVariable* funcVar, acFunction* func)
{
    funcVar->setValue(func);
}

void setFuncPtr(acVariable* funcVar, acFunctionData* funcData)
{
    acFunction* func = (acFunction*)funcVar->m_gcobj;
    func->m_funcData = funcData;
}

void setFuncMiscData(acVariable* funcVar, std::list<acGCObject*>* funcList)
{
    acFunction* func = (acFunction*)funcVar->m_gcobj;
    func->m_createdFuncDataList = funcList;
}

void* createTmpArray(acArray* arr, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();

    acVariable* var = (acVariable*)gc->createObject(acVT_NULL);
    acArray* tmpArray = (acArray*)gc->createObject(acVT_ARRAY);
    var->setValue(tmpArray);
    arr->m_data.push_back(var);

    return tmpArray;
}

void* createTable(acVariable* var, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acTable* tab = (acTable*)gc->createObject(acVT_TABLE);
    var->setValue(tab);
    return tab;
}

void* createArray(acVariable* var, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acArray* arr = (acArray*)gc->createObject(acVT_ARRAY);
    var->setValue(arr);
    return arr;
}

//parent.key or parent[key]
void* opGetVar(acVariable* parent, acVariable* key, int findInGlobal, int isFuncCall, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    if(parent->m_valueType == acVT_ARRAY)
    {
        acInt64 idx = 0;
        switch(key->m_valueType)
        {
        case acVT_INT32:
            idx = key->m_int32;
            break;
        case acVT_INT64:
            idx = key->m_int64;
            break;
        default:
            {
                char msg[128];
                sprintf(msg, "Error: attempt to index array by '%s'", getVarTypeStr(key->m_valueType).c_str());
                vm->runtimeError(msg);
            }
            return 0;
        }

        acArray* arr = (acArray*)parent->m_gcobj;
        if(idx < 0 || idx >= (acInt64)arr->size())
        {
            char msg[128];
            sprintf(msg, "Error: array index out of bounds: %ld", idx);
            vm->runtimeError(msg);
            return 0;
        }

        return arr->m_data[idx];
    }

    if(parent->m_valueType == acVT_STRING)
    {
        acInt64 idx = 0;
        switch(key->m_valueType)
        {
        case acVT_INT32:
            idx = key->m_int32;
            break;
        case acVT_INT64:
            idx = (int)key->m_int64;
            break;
        default:
            {
                char msg[128];
                sprintf(msg, "Error: attempt to index string by '%s'", getVarTypeStr(key->m_valueType).c_str());
                vm->runtimeError(msg);
            }
            return 0;
        }

        acString* str = (acString*)parent->m_gcobj;
        if(idx < 0 || idx >= (acInt64)str->m_data.size())
        {
            char msg[128];
            sprintf(msg, "Error: string index out of bounds: %ld", idx);
            vm->runtimeError(msg);
            return 0;
        }

        acGarbageCollector* gc = vm->getGarbageCollector();
        return gc->createVarWithData((acInt32)str->m_data[idx]);
    }

    if(parent->m_valueType != acVT_TABLE)
    {
        char msg[128];
        sprintf(msg, "Error: attempt to get element on '%s'", getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return 0;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(key);
    if(value == 0)
    {
        if(isFuncCall && (value = table->getBindFunc(key)) != 0)
        {
            return value;
        }

        if(findInGlobal != 0)
        {
            acCodeGenerator* cg = vm->getCodeGenerator();
            value = cg->getRootTable()->get(key);
        }

        if(value == 0)
        {
            char s1[64];
            s1[snprintf(s1, 63, "%s", toString(key, vm).c_str())] = 0;
            char msg[128];
            sprintf(msg, "Error: element '%s' not found", s1);
            vm->runtimeError(msg);
            return 0;
        }
    }

    return value;
}
void* opGetVar_int32(acVariable* parent, acInt32 idx, int findInGlobal, int isFuncCall, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    if(parent->m_valueType == acVT_ARRAY)
    {
        acArray* arr = parent->toArray();
        if(idx < 0 || idx >= arr->size())
        {
            char msg[128];
            sprintf(msg, "Error: array index out of bounds: %d", idx);
            vm->runtimeError(msg);
            return 0;
        }

        return arr->m_data[idx];
    }

    if(parent->m_valueType == acVT_STRING)
    {
        acString* str = parent->toString();
        if(idx < 0 || idx >= (int)str->m_data.size())
        {
            char msg[128];
            sprintf(msg, "Error: string index out of bounds: %d", idx);
            vm->runtimeError(msg);
            return 0;
        }

        acGarbageCollector* gc = vm->getGarbageCollector();
        return gc->createVarWithData((acInt32)str->m_data[idx]);
    }

    if(parent->m_valueType != acVT_TABLE)
    {
        char msg[128];
        sprintf(msg, "Error: attempt to get element '%d' on '%s'", idx, getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return 0;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(idx);
    if(value == 0)
    {
        if(findInGlobal != 0)
        {
            acCodeGenerator* cg = vm->getCodeGenerator();
            value = cg->getRootTable()->get(idx);
        }

        if(value == 0)
        {
            char msg[128];
            sprintf(msg, "Error: element '%d' not found", idx);
            vm->runtimeError(msg);
            return 0;
        }
    }

    return value;
}
void* opGetVar_int64(acVariable* parent, acInt64 idx, int findInGlobal, int isFuncCall, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    if(parent->m_valueType == acVT_ARRAY)
    {
        acArray* arr = parent->toArray();
        if(idx < 0 || idx >= arr->size())
        {
            char msg[128];
            sprintf(msg, "Error: array index out of bounds : %d", idx);
            vm->runtimeError(msg);
            return 0;
        }

        return arr->m_data[idx];
    }

    if(parent->m_valueType == acVT_STRING)
    {
        acString* str = parent->toString();
        if(idx < 0 || idx >= (acInt64)str->m_data.size())
        {
            char msg[128];
            sprintf(msg, "Error: string index out of bounds: %d", idx);
            vm->runtimeError(msg);
            return 0;
        }

        acGarbageCollector* gc = vm->getGarbageCollector();
        return gc->createVarWithData((acInt32)str->m_data[idx]);
    }

    if(parent->m_valueType != acVT_TABLE)
    {
        char msg[128];
        sprintf(msg, "Error: attempt to get element '%d' on '%s'", idx, getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return 0;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(idx);
    if(value == 0)
    {
        if(findInGlobal != 0)
        {
            acCodeGenerator* cg = vm->getCodeGenerator();
            value = cg->getRootTable()->get(idx);
        }

        if(value == 0)
        {
            char msg[128];
            sprintf(msg, "Error: element '%d' not found", idx);
            vm->runtimeError(msg);
            return 0;
        }
    }

    return value;
}
void* opGetVar_str(acVariable* parent, char* name, int findInGlobal, int isFuncCall, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    if(parent->m_valueType != acVT_TABLE)
    {
        char s1[64];
        s1[snprintf(s1, 63, "%s", name)] = 0;
        char msg[256];
        sprintf(msg, "Error: attempt to get element '%s' on '%s'", s1, getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return 0;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(name);
    if(value == 0)
    {
        if(isFuncCall && (value = table->getBindFunc(name)) != 0)
        {
            return value;
        }

        if(findInGlobal != 0)
        {
            acCodeGenerator* cg = vm->getCodeGenerator();
            if(table != cg->getRootTable())
            {
                value = cg->getRootTable()->get(name);
            }
        }

        if(value == 0)
        {
            char msg[128];
            sprintf(msg, "Error: element '%s' not found", name);
            vm->runtimeError(msg);
            return 0;
        }
    }

    return value;
}

//var parent.key or var parent[key]
void* opNewVar(acVariable* parent, acVariable* key, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_ARRAY:
        {
            acInt64 idx = 0;
            switch(key->m_valueType)
            {
            case acVT_INT32:
                idx = key->m_int32;
                break;
            case acVT_INT64:
                idx = key->m_int64;
                break;
            default:
                {
                    char msg[128];
                    sprintf(msg, "Error: attempt to index array by '%s'", getVarTypeStr(key->m_valueType).c_str());
                    vm->runtimeError(msg);
                }
                return 0;
            }

            acArray* arr = (acArray*)parent->m_gcobj;
            if(idx < 0 || idx >= (acInt64)arr->size())
            {
                char msg[128];
                sprintf(msg, "Error: array index out of bounds: %ld", idx);
                vm->runtimeError(msg);
                return 0;
            }

            var = (acVariable*)gc->createObject(acVT_NULL);
            arr->m_data[idx] = var;
        }
        break;
    case acVT_TABLE:
        {
            acTable* tab = parent->toTable();
            var = (acVariable*)gc->createObject(acVT_NULL);
            tab->add(key, var);
        }
        break;
    default:
        {
            char msg[128];
            sprintf(msg, "Error: attempt to create new var on '%s'", getVarTypeStr(parent->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return 0;
    }

    return var;
}
void* opNewVar_int32(acVariable* parent, acInt32 key, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_ARRAY:
        {
            acArray* arr = parent->toArray();
            if(key < 0 || key >= arr->size())
            {
                char msg[128];
                sprintf(msg, "Error: array index out of bounds: %d", key);
                vm->runtimeError(msg);
                return 0;
            }

            var = (acVariable*)gc->createObject(acVT_NULL);
            arr->m_data[key] = var;
        }
        break;
    case acVT_TABLE:
        {
            var = (acVariable*)addTableVar_int32(parent->toTable(), key, vm);
        }
        break;
    default:
        {
            char msg[128];
            sprintf(msg, "Error: attempt to create new var on '%s'", getVarTypeStr(parent->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return 0;
    }

    return var;
}
void* opNewVar_int64(acVariable* parent, acInt64 key, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_ARRAY:
        {
            acArray* arr = parent->toArray();
            if(key < 0 || key >= arr->size())
            {
                char msg[128];
                sprintf(msg, "Error: array index out of bounds: %ld", key);
                vm->runtimeError(msg);
                return 0;
            }

            var = (acVariable*)gc->createObject(acVT_NULL);
            arr->m_data[key] = var;
        }
        break;
    case acVT_TABLE:
        {
            var = (acVariable*)addTableVar_int64(parent->toTable(), key, vm);
        }
        break;
    default:
        {
            char msg[128];
            sprintf(msg, "Error: attempt to create new var on '%s'", getVarTypeStr(parent->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return 0;
    }

    return var;
}
void* opNewVar_str(acVariable* parent, char* key, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_TABLE:
        {
            var = (acVariable*)addTableVar_str(parent->toTable(), key, vm);
        }
        break;
    default:
        {
            char s1[64];
            s1[snprintf(s1, 63, "%s", key)] = 0;
            char msg[256];
            sprintf(msg, "Error: attempt to create new var '%s' on '%s'", s1, getVarTypeStr(parent->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return 0;
    }

    return var;
}

//v1 = v2
void opAssignVar(acVariable* v1, acVariable* v2)
{
    v1->assignFrom(v2);
}
void opAssignVar_null(acVariable* v1)
{
    v1->setNull();
}
void opAssignVar_bool(acVariable* v1, int v2)
{
    v1->setValue(v2!=0);
}
void opAssignVar_int32(acVariable* v1, acInt32 v2)
{
    v1->setValue(v2);
}
void opAssignVar_int64(acVariable* v1, acInt64 v2)
{
    v1->setValue(v2);
}
void opAssignVar_float(acVariable* v1, acFloat v2)
{
    v1->setValue(v2);
}
void opAssignVar_double(acVariable* v1, acDouble v2)
{
    v1->setValue(v2);
}
void opAssignVar_str(acVariable* v1, char* v2, acVM* vm)
{
    acString* s = (acString*)vm->getGarbageCollector()->createObject(acVT_STRING);
    s->setData(v2);
    v1->setValue(s);
}

void callOpFunc(acVariable* func, acVariable* ret, acVariable* thisVar, acVariable* v1, acVariable* v2, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acArray* args = (acArray*)gc->createObject(acVT_ARRAY);
    gc->addTempObj(args);
    args->add(v1);
    args->add(v2);
    callFunction(func, thisVar, args, vm);
    ret->setValue(args->get(0));
    gc->removeTempObj(args);
}

//ret = v1 + v2
void opAddVar(acVariable* ret, acVariable* v1, acVariable* v2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    //call default add function; type promotion
    switch(v1->m_valueType)
    {
    case acVT_INT32:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
            addInt32(ret, v1, v2, vm);
            return;
        case acVT_INT64:
            addInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
            addFloat(ret, v1, v2, vm);
            return;
        case acVT_DOUBLE:
            addDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_INT64:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_INT64:
            addInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
        case acVT_DOUBLE:
            addDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_FLOAT:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_FLOAT:
            addFloat(ret, v1, v2, vm);
            return;
        case acVT_INT64:
        case acVT_DOUBLE:
            addDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_DOUBLE:
        addDouble(ret, v1, v2, vm);
        return;
    case acVT_STRING:
        addString(ret, v1, v2, vm);
        return;
    case acVT_TABLE:
        {
            //operator "_add"
            acVariable* func = v1->toTable()->getBindFunc(acOF_ADD);
            if(func != 0)
            {
                callOpFunc(func, ret, v1, v1, v2, vm);
                return;
            }
        }
        break;
    }

    if(v2->m_valueType == acVT_STRING)
    {
        addString(ret, v1, v2, vm);
        return;
    }

    if(v2->m_valueType == acVT_TABLE)
    {
        //operator "_add"
        acVariable* func = v2->toTable()->getBindFunc(acOF_ADD);
        if(func != 0)
        {
            callOpFunc(func, ret, v2, v1, v2, vm);
            return;
        }
    }

    char msg[128];
    sprintf(msg, "Error: attempt to use op '+' on between '%s' and '%s'",
        getVarTypeStr(v1->m_valueType).c_str(),
        getVarTypeStr(v2->m_valueType).c_str());
    vm->runtimeError(msg);
}

//ret = v1 - v2
void opSubVar(acVariable* ret, acVariable* v1, acVariable* v2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    switch(v1->m_valueType)
    {
    case acVT_INT32:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
            subInt32(ret, v1, v2, vm);
            return;
        case acVT_INT64:
            subInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
            subFloat(ret, v1, v2, vm);
            return;
        case acVT_DOUBLE:
            subDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_INT64:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_INT64:
            subInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
        case acVT_DOUBLE:
            subDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_FLOAT:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_FLOAT:
            subFloat(ret, v1, v2, vm);
            return;
        case acVT_INT64:
        case acVT_DOUBLE:
            subDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_DOUBLE:
        subDouble(ret, v1, v2, vm);
        return;
    case acVT_TABLE:
        {
            //operator "_sub"
            acVariable* func = v1->toTable()->getBindFunc(acOF_SUB);
            if(func != 0)
            {
                callOpFunc(func, ret, v1, v1, v2, vm);
                return;
            }
        }
        break;
    }

    if(v2->m_valueType == acVT_TABLE)
    {
        //operator "_sub"
        acVariable* func = v2->toTable()->getBindFunc(acOF_SUB);
        if(func != 0)
        {
            callOpFunc(func, ret, v2, v1, v2, vm);
            return;
        }
    }

    char msg[128];
    sprintf(msg, "Error: attempt to use op '-' on between '%s' and '%s'",
        getVarTypeStr(v1->m_valueType).c_str(),
        getVarTypeStr(v2->m_valueType).c_str());
    vm->runtimeError(msg);
}

//ret = v1 * v2
void opMulVar(acVariable* ret, acVariable* v1, acVariable* v2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    switch(v1->m_valueType)
    {
    case acVT_INT32:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
            mulInt32(ret, v1, v2, vm);
            return;
        case acVT_INT64:
            mulInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
            mulFloat(ret, v1, v2, vm);
            return;
        case acVT_DOUBLE:
            mulDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_INT64:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_INT64:
            mulInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
        case acVT_DOUBLE:
            mulDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_FLOAT:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_FLOAT:
            mulFloat(ret, v1, v2, vm);
            return;
        case acVT_INT64:
        case acVT_DOUBLE:
            mulDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_DOUBLE:
        mulDouble(ret, v1, v2, vm);
        return;
    case acVT_TABLE:
        {
            //operator "_mul"
            acVariable* func = v1->toTable()->getBindFunc(acOF_MUL);
            if(func != 0)
            {
                callOpFunc(func, ret, v1, v1, v2, vm);
                return;
            }
        }
        break;
    }

    if(v2->m_valueType == acVT_TABLE)
    {
        //operator "_mul"
        acVariable* func = v2->toTable()->getBindFunc(acOF_MUL);
        if(func != 0)
        {
            callOpFunc(func, ret, v2, v1, v2, vm);
            return;
        }
    }

    char msg[128];
    sprintf(msg, "Error: attempt to use op '*' on between '%s' and '%s'",
        getVarTypeStr(v1->m_valueType).c_str(),
        getVarTypeStr(v2->m_valueType).c_str());
    vm->runtimeError(msg);
}

//ret = v1 / v2
void opDivVar(acVariable* ret, acVariable* v1, acVariable* v2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    switch(v1->m_valueType)
    {
    case acVT_INT32:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
            divInt32(ret, v1, v2, vm);
            return;
        case acVT_INT64:
            divInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
            divFloat(ret, v1, v2, vm);
            return;
        case acVT_DOUBLE:
            divDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_INT64:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_INT64:
            divInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
        case acVT_DOUBLE:
            divDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_FLOAT:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_FLOAT:
            divFloat(ret, v1, v2, vm);
            return;
        case acVT_INT64:
        case acVT_DOUBLE:
            divDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_DOUBLE:
        divDouble(ret, v1, v2, vm);
        return;
    case acVT_TABLE:
        {
            //operator "_div"
            acVariable* func = v1->toTable()->getBindFunc(acOF_DIV);
            if(func != 0)
            {
                callOpFunc(func, ret, v1, v1, v2, vm);
                return;
            }
        }
        break;
    }

    if(v2->m_valueType == acVT_TABLE)
    {
        //operator "_div"
        acVariable* func = v2->toTable()->getBindFunc(acOF_DIV);
        if(func != 0)
        {
            callOpFunc(func, ret, v2, v1, v2, vm);
            return;
        }
    }

    char msg[128];
    sprintf(msg, "Error: attempt to use op '/' on between '%s' and '%s'",
        getVarTypeStr(v1->m_valueType).c_str(),
        getVarTypeStr(v2->m_valueType).c_str());
    vm->runtimeError(msg);
}

//ret = v1 % v2
void opModVar(acVariable* ret, acVariable* v1, acVariable* v2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);

    switch(v1->m_valueType)
    {
    case acVT_INT32:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
            modInt32(ret, v1, v2, vm);
            return;
        case acVT_INT64:
            modInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
            modFloat(ret, v1, v2, vm);
            return;
        case acVT_DOUBLE:
            modDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_INT64:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_INT64:
            modInt64(ret, v1, v2, vm);
            return;
        case acVT_FLOAT:
        case acVT_DOUBLE:
            modDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_FLOAT:
        switch(v2->m_valueType)
        {
        case acVT_INT32:
        case acVT_FLOAT:
            modFloat(ret, v1, v2, vm);
            return;
        case acVT_INT64:
        case acVT_DOUBLE:
            modDouble(ret, v1, v2, vm);
            return;
        }
        break;
    case acVT_DOUBLE:
        modDouble(ret, v1, v2, vm);
        return;
    case acVT_TABLE:
        {
            //operator "_mod"
            acVariable* func = v1->toTable()->getBindFunc(acOF_MOD);
            if(func != 0)
            {
                callOpFunc(func, ret, v1, v1, v2, vm);
                return;
            }
        }
        break;
    }

    if(v2->m_valueType == acVT_TABLE)
    {
        //operator "_mod"
        acVariable* func = v2->toTable()->getBindFunc(acOF_MOD);
        if(func != 0)
        {
            callOpFunc(func, ret, v2, v1, v2, vm);
            return;
        }
    }

    char msg[128];
    sprintf(msg, "Error: attempt to use op '%%' on between '%s' and '%s'",
        getVarTypeStr(v1->m_valueType).c_str(),
        getVarTypeStr(v2->m_valueType).c_str());
    vm->runtimeError(msg);
}

//v1(args); ret = args[0]
void opCallFunc(acVariable* var, acVariable* thisVar, acArray* argArray, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    callFunction(var, thisVar, argArray, vm);
}

//return 1 for true; 0 for false
int opEqualVar(acVariable* lhs, acVariable* rhs, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    return lhs->compare(rhs, vm) == 0;
}
//return 1 for true; 0 for false
int opNotEqualVar(acVariable* lhs, acVariable* rhs, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    return lhs->compare(rhs, vm) != 0;
}
//return 1 for true; 0 for false
int opCompareVar(acVariable* lhs, acVariable* rhs, int tok_cmp, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    int cmp = lhs->compare(rhs, vm);
    switch(tok_cmp)
    {
    case TOK_LT:
        return cmp < 0;

    case TOK_LE:
        return cmp <= 0;

    case TOK_GT:
        return cmp > 0;

    //case TOK_GE:
    }
    return cmp >= 0;
}

void opPostfixIncVar(acVariable* ret, acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ret->setValue(var->m_int32);
        ++var->m_int32;
        break;
    case acVT_INT64:
        ret->setValue(var->m_int64);
        ++var->m_int64;
        break;
    case acVT_FLOAT:
        ret->setValue(var->m_float);
        ++var->m_float;
        break;
    case acVT_DOUBLE:
        ret->setValue(var->m_double);
        ++var->m_double;
        break;
    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to use postfix op '++' on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return;
    }
}

void opPostfixDecVar(acVariable* ret, acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ret->setValue(var->m_int32);
        --var->m_int32;
        break;
    case acVT_INT64:
        ret->setValue(var->m_int64);
        --var->m_int64;
        break;
    case acVT_FLOAT:
        ret->setValue(var->m_float);
        --var->m_float;
        break;
    case acVT_DOUBLE:
        ret->setValue(var->m_double);
        --var->m_double;
        break;
    default:
    {
        vm->setDebugInfo(debugInfo);
        char msg[128];
        sprintf(msg, "Error: attempt to use postfix op '--' on '%s'", getVarTypeStr(var->m_valueType).c_str());
        vm->runtimeError(msg);
    }
        return;
    }
}

void opPrefixIncVar(acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ++var->m_int32;
        break;
    case acVT_INT64:
        ++var->m_int64;
        break;
    case acVT_FLOAT:
        ++var->m_float;
        break;
    case acVT_DOUBLE:
        ++var->m_double;
        break;
    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to use prefix op '++' on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return;
    }
}

void opPrefixDecVar(acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        --var->m_int32;
        break;
    case acVT_INT64:
        --var->m_int64;
        break;
    case acVT_FLOAT:
        --var->m_float;
        break;
    case acVT_DOUBLE:
        --var->m_double;
        break;
    default:
    {
        vm->setDebugInfo(debugInfo);
        char msg[128];
        sprintf(msg, "Error: attempt to use prefix op '--' on '%s'", getVarTypeStr(var->m_valueType).c_str());
        vm->runtimeError(msg);
    }
        return;
    }
}

void opUnaryPlusVar(acVariable* ret, acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ret->setValue(var->m_int32 < 0 ? -var->m_int32 : var->m_int32);
        break;
    case acVT_INT64:
        ret->setValue(var->m_int64 < 0 ? -var->m_int64 : var->m_int64);
        break;
    case acVT_FLOAT:
        ret->setValue(var->m_float < 0 ? -var->m_float : var->m_float);
        break;
    case acVT_DOUBLE:
        ret->setValue(var->m_double < 0 ? -var->m_double : var->m_double);
        break;
    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to use unary op '+' on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return;
    }
}

void opUnaryMinusVar(acVariable* ret, acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ret->setValue(-var->m_int32);
        break;
    case acVT_INT64:
        ret->setValue(-var->m_int64);
        break;
    case acVT_FLOAT:
        ret->setValue(-var->m_float);
        break;
    case acVT_DOUBLE:
        ret->setValue(-var->m_double);
        break;
    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to use unary op '-' on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return;
    }
}

void opLogicalNotVar(acVariable* ret, acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    ret->setValue(!toBool(var, vm));
}

void opLogicalAndVar(acVariable* ret, acVariable* var1, acVariable* var2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    ret->setValue(toBool(var1, vm) && toBool(var2, vm));
}

void opLogicalOrVar(acVariable* ret, acVariable* var1, acVariable* var2, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    ret->setValue(toBool(var1, vm) || toBool(var2, vm));
}

void opBitwiseNotVar(acVariable* ret, acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ret->setValue(~var->m_int32);
        break;
    case acVT_INT64:
        ret->setValue(~var->m_int64);
        break;
    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to use bitwise op '~' on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return;
    }
}

void opBitwiseAndVar(acVariable* ret, acVariable* var1, acVariable* var2, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var1->m_valueType)
    {
    case acVT_INT32:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            ret->setValue(var1->m_int32 & var2->m_int32);
            return;
        case acVT_INT64:
            ret->setValue(acInt64(var1->m_int32) & var2->m_int64);
            return;
        }
        break;
    case acVT_INT64:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            ret->setValue(var1->m_int64 & acInt64(var2->m_int32));
            return;
        case acVT_INT64:
            ret->setValue(var1->m_int64 & var2->m_int64);
            return;
        }
        break;
    }

    vm->setDebugInfo(debugInfo);
    char msg[128];
    sprintf(msg, "Error: attempt to use bitwise op '&' on between '%s' and '%s'",
        getVarTypeStr(var1->m_valueType).c_str(),
        getVarTypeStr(var2->m_valueType).c_str());
    vm->runtimeError(msg);
}

void opBitwiseOrVar(acVariable* ret, acVariable* var1, acVariable* var2, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var1->m_valueType)
    {
    case acVT_INT32:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            ret->setValue(var1->m_int32 | var2->m_int32);
            return;
        case acVT_INT64:
            ret->setValue(acInt64(var1->m_int32) | var2->m_int64);
            return;
        }
        break;
    case acVT_INT64:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            ret->setValue(var1->m_int64 | acInt64(var2->m_int32));
            return;
        case acVT_INT64:
            ret->setValue(var1->m_int64 | var2->m_int64);
            return;
        }
        break;
    }

    vm->setDebugInfo(debugInfo);
    char msg[128];
    sprintf(msg, "Error: attempt to use bitwise op '|' on between '%s' and '%s'",
        getVarTypeStr(var1->m_valueType).c_str(),
        getVarTypeStr(var2->m_valueType).c_str());
    vm->runtimeError(msg);
}

void opBitwiseXorVar(acVariable* ret, acVariable* var1, acVariable* var2, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var1->m_valueType)
    {
    case acVT_INT32:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            ret->setValue(var1->m_int32 ^ var2->m_int32);
            return;
        case acVT_INT64:
            ret->setValue(acInt64(var1->m_int32) ^ var2->m_int64);
            return;
        }
        break;
    case acVT_INT64:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            ret->setValue(var1->m_int64 ^ acInt64(var2->m_int32));
            return;
        case acVT_INT64:
            ret->setValue(var1->m_int64 ^ var2->m_int64);
            return;
        }
        break;
    }

    vm->setDebugInfo(debugInfo);
    char msg[128];
    sprintf(msg, "Error: attempt to use bitwise op '^' on between '%s' and '%s'",
        getVarTypeStr(var1->m_valueType).c_str(),
        getVarTypeStr(var2->m_valueType).c_str());
    vm->runtimeError(msg);
}

int opToBoolVar(acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    vm->setDebugInfo(debugInfo);
    return toBool(var, vm);
}

void opInitIter(acVariable* var, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_STRING:
        ((acString*)var->m_gcobj)->initIter();
        break;
    case acVT_ARRAY:
        ((acArray*)var->m_gcobj)->initIter();
        break;
    case acVT_TABLE:
        ((acTable*)var->m_gcobj)->initIter();
        break;
    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to iterate on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        return;
    }
}

int opIterateVar(acVariable* var, acVariable* key, acVariable* value, acDebugInfo* debugInfo, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_STRING:
        return ((acString*)var->m_gcobj)->iterate(key, value);

    case acVT_ARRAY:
        return ((acArray*)var->m_gcobj)->iterate(key, value);

    case acVT_TABLE:
        return ((acTable*)var->m_gcobj)->iterate(key, value);

    default:
        {
            vm->setDebugInfo(debugInfo);
            char msg[128];
            sprintf(msg, "Error: attempt to iterate on '%s'", getVarTypeStr(var->m_valueType).c_str());
            vm->runtimeError(msg);
        }
        break;
    }

    return 0;
}

void* opNew(acVariable* thisVar, acArray* argArray, acDebugInfo* debugInfo, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* newVar = (acVariable*)gc->createObject(acVT_NULL);

    thisVar->cloneTo(newVar, vm);

    if(newVar->m_valueType == acVT_TABLE)
    {
        acVariable* newFunc = newVar->toTable()->getBindFunc(acOF_NEW);
        if(newFunc != 0)
        {
            vm->setDebugInfo(debugInfo);
            callFunction(newFunc, newVar, argArray, vm);
        }
    }

    return newVar;
}

//delete parent.key or var parent[key]
void opDelete(acVariable* parent, acVariable* key, int findInGlobal, acDebugInfo* debugInfo, acVM* vm)
{
    if(parent->m_valueType != acVT_TABLE)
    {
        vm->setDebugInfo(debugInfo);
        char s1[64];
        s1[snprintf(s1, 63, "%s", toString(key, vm).c_str())] = 0;
        char msg[256];
        sprintf(msg, "Error: attempt to delete element '%s' from '%s'",
            s1,
            getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(key);
    if(value != 0)
    {
        table->remove(key);
        return;
    }

    if(findInGlobal != 0)
    {
        acCodeGenerator* cg = vm->getCodeGenerator();
        value = cg->getRootTable()->get(key);
        if(value != 0)
        {
            cg->getRootTable()->remove(key);
            return;
        }
    }

    vm->setDebugInfo(debugInfo);
    char s1[64];
    s1[snprintf(s1, 63, "%s", toString(key, vm).c_str())] = 0;
    char msg[128];
    sprintf(msg, "Error: delete element '%s' not found", s1);
    vm->runtimeError(msg);
}
void opDelete_int32(acVariable* parent, acInt32 key, int findInGlobal, acDebugInfo* debugInfo, acVM* vm)
{
    if(parent->m_valueType != acVT_TABLE)
    {
        vm->setDebugInfo(debugInfo);
        char msg[128];
        sprintf(msg, "Error: attempt to delete element '%d' from '%s'", key, getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(key);
    if(value != 0)
    {
        table->remove(key);
        return;
    }

    if(findInGlobal != 0)
    {
        acCodeGenerator* cg = vm->getCodeGenerator();
        value = cg->getRootTable()->get(key);
        if(value != 0)
        {
            cg->getRootTable()->remove(key);
            return;
        }
    }

    vm->setDebugInfo(debugInfo);
    char msg[128];
    sprintf(msg, "Error: delete element '%d' not found", key);
    vm->runtimeError(msg);
}
void opDelete_int64(acVariable* parent, acInt64 key, int findInGlobal, acDebugInfo* debugInfo, acVM* vm)
{
    if(parent->m_valueType != acVT_TABLE)
    {
        vm->setDebugInfo(debugInfo);
        char msg[128];
        sprintf(msg, "Error: attempt to delete element '%ld' from '%s'", key, getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(key);
    if(value != 0)
    {
        table->remove(key);
        return;
    }

    if(findInGlobal != 0)
    {
        acCodeGenerator* cg = vm->getCodeGenerator();
        value = cg->getRootTable()->get(key);
        if(value != 0)
        {
            cg->getRootTable()->remove(key);
            return;
        }
    }

    vm->setDebugInfo(debugInfo);
    char msg[128];
    sprintf(msg, "Error: delete element '%ld' not found", key);
    vm->runtimeError(msg);
}
void opDelete_str(acVariable* parent, char* key, int findInGlobal, acDebugInfo* debugInfo, acVM* vm)
{
    if(parent->m_valueType != acVT_TABLE)
    {
        vm->setDebugInfo(debugInfo);
        char s1[64];
        s1[snprintf(s1, 63, "%s", key)] = 0;
        char msg[256];
        sprintf(msg, "Error: attempt to delete element '%s' from '%s'", s1, getVarTypeStr(parent->m_valueType).c_str());
        vm->runtimeError(msg);
        return;
    }

    acTable* table = parent->toTable();
    acVariable* value = table->get(key);
    if(value != 0)
    {
        table->remove(key);
        return;
    }

    if(findInGlobal != 0)
    {
        acCodeGenerator* cg = vm->getCodeGenerator();
        value = cg->getRootTable()->get(key);
        if(value != 0)
        {
            cg->getRootTable()->remove(key);
            return;
        }
    }

    vm->setDebugInfo(debugInfo);
    char s1[64];
    s1[snprintf(s1, 63, "%s", key)] = 0;
    char msg[128];
    sprintf(msg, "Error: delete element '%s' not found", s1);
    vm->runtimeError(msg);
}

}//extern"C"
}//namespace

void acCodeGenerator::createGlobalValues()
{
    Module* mod = getModule();
    ExecutionEngine *ee = m_vm->getCurrentExecutionEngine();
    LLVMContext& context = getLLVMContext();

    Type* int8Ty = Type::getInt8Ty(context);
    //PointerType* voidPtrTy = PointerType::get(Type::getInt8Ty(context), 0);
    //voidPtrTy->dump();

    //!!!global variable in llvm is PointerType

    m_gv_vm = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_vm", int8Ty));
    addGlobalSymbal(ee, m_gv_vm, getVM());

    m_gv_cg = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_cg", int8Ty));
    addGlobalSymbal(ee, m_gv_cg, this);

    m_gv_gc = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_gc", int8Ty));
    addGlobalSymbal(ee, m_gv_gc, getGarbageCollector());

    m_gv_errorJmpBuf = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_errorJmpBuf", int8Ty));
    addGlobalSymbal(ee, m_gv_errorJmpBuf, m_errorJmpBuf);
    //printf("%p %p\n", m_errorJmpBuf, &m_errorJmpBuf);
    //m_gv_errorJmpBuf->getType()->dump();

    m_gv_rootTableVar = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_rootTableVar", int8Ty));
    addGlobalSymbal(ee, m_gv_rootTableVar, m_rootTableVar);

    m_gv_rootArgArray = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_rootArgArray", int8Ty));
    addGlobalSymbal(ee, m_gv_rootArgArray, m_rootArgArray);

    m_gv_rootTmpArray = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_rootTmpArray", int8Ty));
    addGlobalSymbal(ee, m_gv_rootTmpArray, m_rootTmpArray);
}

void acCodeGenerator::createGlobalFunctions()
{
    Module* mod = getModule();
    ExecutionEngine *ee = m_vm->getCurrentExecutionEngine();
    LLVMContext& context = getLLVMContext();

    Type* voidTy = Type::getVoidTy(context);
    PointerType* voidPtrTy = Type::getInt8PtrTy(context);
    PointerType* charPtrTy = Type::getInt8PtrTy(context);
    IntegerType* int32Ty = Type::getInt32Ty(context);
    IntegerType* int64Ty = Type::getInt64Ty(context);
    Type* floatTy = Type::getFloatTy(context);
    Type* doubleTy = Type::getDoubleTy(context);

    //error handling
    m_gf_setJmp = cast<Function>(mod->getOrInsertFunction("setJmp",
                                int32Ty,//ret
                                voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_setJmp, (void*)_setjmp);

    m_gf_longJmp = cast<Function>(mod->getOrInsertFunction("myLongJmp",
                                voidTy,//ret
                                voidPtrTy, int32Ty,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_longJmp, (void*)myLongJmp);

    //general functions for acVM
    m_gf_newArrayVar = cast<Function>(mod->getOrInsertFunction("newArrayVar",
                                voidPtrTy,//ret
                                voidPtrTy, int32Ty, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_newArrayVar, (void*)newArrayVar);

    m_gf_setArrayVar = cast<Function>(mod->getOrInsertFunction("setArrayVar",
                                voidTy,//ret
                                voidPtrTy, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_setArrayVar, (void*)setArrayVar);

    m_gf_getArrayVar = cast<Function>(mod->getOrInsertFunction("getArrayVar",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_getArrayVar, (void*)getArrayVar);

    m_gf_getArrayVar_int = cast<Function>(mod->getOrInsertFunction("getArrayVar_int",
                                voidPtrTy,//ret
                                voidPtrTy, int32Ty, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_getArrayVar_int, (void*)getArrayVar_int);

    m_gf_addTableKeyValue = cast<Function>(mod->getOrInsertFunction("addTableKeyValue",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_addTableKeyValue, (void*)addTableKeyValue);

    m_gf_addTableKeyValue_str = cast<Function>(mod->getOrInsertFunction("addTableKeyValue_str",
                                voidTy,//ret
                                voidPtrTy, charPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_addTableKeyValue_str, (void*)addTableKeyValue_str);

    m_gf_addTableVar = cast<Function>(mod->getOrInsertFunction("addTableVar",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_addTableVar, (void*)addTableVar);

    m_gf_addTableVar_str = cast<Function>(mod->getOrInsertFunction("addTableVar_str",
                                voidPtrTy,//ret
                                voidPtrTy, charPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_addTableVar_str, (void*)addTableVar_str);

    m_gf_getTableVar = cast<Function>(mod->getOrInsertFunction("getTableVar",
                                voidPtrTy,//ret
                                voidPtrTy, charPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_getTableVar, (void*)getTableVar);

    m_gf_createUpValueTable = cast<Function>(mod->getOrInsertFunction("createUpValueTable",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_createUpValueTable, (void*)createUpValueTable);

    m_gf_createFunc = cast<Function>(mod->getOrInsertFunction("createFunc",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_createFunc, (void*)createFunc);

    m_gf_assignFunc = cast<Function>(mod->getOrInsertFunction("assignFunc",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_assignFunc, (void*)assignFunc);

    m_gf_setFuncPtr = cast<Function>(mod->getOrInsertFunction("setFuncPtr",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_setFuncPtr, (void*)setFuncPtr);

    m_gf_setFuncMiscData = cast<Function>(mod->getOrInsertFunction("setFuncMiscData",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_setFuncMiscData, (void*)setFuncMiscData);

    m_gf_createTmpArray = cast<Function>(mod->getOrInsertFunction("createTmpArray",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_createTmpArray, (void*)createTmpArray);

    m_gf_createTable = cast<Function>(mod->getOrInsertFunction("createTable",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_createTable, (void*)createTable);

    m_gf_createArray = cast<Function>(mod->getOrInsertFunction("createArray",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_createArray, (void*)createArray);

    //
    m_gf_opGetVar = cast<Function>(mod->getOrInsertFunction("opGetVar",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy, int32Ty, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opGetVar, (void*)opGetVar);

    m_gf_opGetVar_int32 = cast<Function>(mod->getOrInsertFunction("opGetVar_int32",
                                voidPtrTy,//ret
                                voidPtrTy, int32Ty, int32Ty, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opGetVar_int32, (void*)opGetVar_int32);

    m_gf_opGetVar_int64 = cast<Function>(mod->getOrInsertFunction("opGetVar_int64",
                                voidPtrTy,//ret
                                voidPtrTy, int64Ty, int32Ty, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opGetVar_int64, (void*)opGetVar_int64);

    m_gf_opGetVar_str = cast<Function>(mod->getOrInsertFunction("opGetVar_str",
                                voidPtrTy,//ret
                                voidPtrTy, charPtrTy, int32Ty, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opGetVar_str, (void*)opGetVar_str);

    m_gf_opNewVar = cast<Function>(mod->getOrInsertFunction("opNewVar",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opNewVar, (void*)opNewVar);

    m_gf_opNewVar_int32 = cast<Function>(mod->getOrInsertFunction("opNewVar_int32",
                                voidPtrTy,//ret
                                voidPtrTy, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opNewVar_int32, (void*)opNewVar_int32);

    m_gf_opNewVar_int64 = cast<Function>(mod->getOrInsertFunction("opNewVar_int64",
                                voidPtrTy,//ret
                                voidPtrTy, int64Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opNewVar_int64, (void*)opNewVar_int64);

    m_gf_opNewVar_str = cast<Function>(mod->getOrInsertFunction("opNewVar_str",
                                voidPtrTy,//ret
                                voidPtrTy, charPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opNewVar_str, (void*)opNewVar_str);

    //
    m_gf_opAssignVar = cast<Function>(mod->getOrInsertFunction("opAssignVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar, (void*)opAssignVar);

    m_gf_opAssignVar_null = cast<Function>(mod->getOrInsertFunction("opAssignVar_null",
                                voidTy,//ret
                                voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_null, (void*)opAssignVar_null);

    m_gf_opAssignVar_bool = cast<Function>(mod->getOrInsertFunction("opAssignVar_bool",
                                voidTy,//ret
                                voidPtrTy, int32Ty,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_bool, (void*)opAssignVar_bool);

    m_gf_opAssignVar_int32 = cast<Function>(mod->getOrInsertFunction("opAssignVar_int32",
                                voidTy,//ret
                                voidPtrTy, int32Ty,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_int32, (void*)opAssignVar_int32);

    m_gf_opAssignVar_int64 = cast<Function>(mod->getOrInsertFunction("opAssignVar_int64",
                                voidTy,//ret
                                voidPtrTy, int64Ty,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_int64, (void*)opAssignVar_int64);

    m_gf_opAssignVar_float = cast<Function>(mod->getOrInsertFunction("opAssignVar_float",
                                voidTy,//ret
                                voidPtrTy, floatTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_float, (void*)opAssignVar_float);

    m_gf_opAssignVar_double = cast<Function>(mod->getOrInsertFunction("opAssignVar_double",
                                voidTy,//ret
                                voidPtrTy, doubleTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_double, (void*)opAssignVar_double);

    m_gf_opAssignVar_str = cast<Function>(mod->getOrInsertFunction("opAssignVar_str",
                                voidTy,//ret
                                voidPtrTy, charPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAssignVar_str, (void*)opAssignVar_str);

    m_gf_opAddVar = cast<Function>(mod->getOrInsertFunction("opAddVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opAddVar, (void*)opAddVar);

    m_gf_opSubVar = cast<Function>(mod->getOrInsertFunction("opSubVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opSubVar, (void*)opSubVar);

    m_gf_opMulVar = cast<Function>(mod->getOrInsertFunction("opMulVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opMulVar, (void*)opMulVar);

    m_gf_opDivVar = cast<Function>(mod->getOrInsertFunction("opDivVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opDivVar, (void*)opDivVar);

    m_gf_opModVar = cast<Function>(mod->getOrInsertFunction("opModVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opModVar, (void*)opModVar);

    m_gf_opCallFunc = cast<Function>(mod->getOrInsertFunction("opCallFunc",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opCallFunc, (void*)opCallFunc);

    m_gf_opEqualVar = cast<Function>(mod->getOrInsertFunction("opEqualVar",
                                int32Ty,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opEqualVar, (void*)opEqualVar);

    m_gf_opNotEqualVar = cast<Function>(mod->getOrInsertFunction("opNotEqualVar",
                                int32Ty,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opNotEqualVar, (void*)opNotEqualVar);

    m_gf_opCompareVar = cast<Function>(mod->getOrInsertFunction("opCompareVar",
                                int32Ty,//ret
                                voidPtrTy, voidPtrTy, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opCompareVar, (void*)opCompareVar);

    m_gf_opPostfixIncVar = cast<Function>(mod->getOrInsertFunction("opPostfixIncVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opPostfixIncVar, (void*)opPostfixIncVar);

    m_gf_opPostfixDecVar = cast<Function>(mod->getOrInsertFunction("opPostfixDecVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opPostfixDecVar, (void*)opPostfixDecVar);

    m_gf_opPrefixIncVar = cast<Function>(mod->getOrInsertFunction("opPrefixIncVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opPrefixIncVar, (void*)opPrefixIncVar);

    m_gf_opPrefixDecVar = cast<Function>(mod->getOrInsertFunction("opPrefixDecVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opPrefixDecVar, (void*)opPrefixDecVar);

    m_gf_opUnaryPlusVar = cast<Function>(mod->getOrInsertFunction("opUnaryPlusVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opUnaryPlusVar, (void*)opUnaryPlusVar);

    m_gf_opUnaryMinusVar = cast<Function>(mod->getOrInsertFunction("opUnaryMinusVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opUnaryMinusVar, (void*)opUnaryMinusVar);

    m_gf_opLogicalNotVar = cast<Function>(mod->getOrInsertFunction("opLogicalNotVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opLogicalNotVar, (void*)opLogicalNotVar);

    m_gf_opLogicalAndVar = cast<Function>(mod->getOrInsertFunction("opLogicalAndVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opLogicalAndVar, (void*)opLogicalAndVar);

    m_gf_opLogicalOrVar = cast<Function>(mod->getOrInsertFunction("opLogicalOrVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opLogicalOrVar, (void*)opLogicalOrVar);

    m_gf_opBitwiseNotVar = cast<Function>(mod->getOrInsertFunction("opBitwiseNotVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opBitwiseNotVar, (void*)opBitwiseNotVar);

    m_gf_opBitwiseAndVar = cast<Function>(mod->getOrInsertFunction("opBitwiseAndVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opBitwiseAndVar, (void*)opBitwiseAndVar);

    m_gf_opBitwiseOrVar = cast<Function>(mod->getOrInsertFunction("opBitwiseOrVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opBitwiseOrVar, (void*)opBitwiseOrVar);

    m_gf_opBitwiseXorVar = cast<Function>(mod->getOrInsertFunction("opBitwiseXorVar",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opBitwiseXorVar, (void*)opBitwiseXorVar);

    m_gf_opToBoolVar = cast<Function>(mod->getOrInsertFunction("opToBoolVar",
                                int32Ty,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opToBoolVar, (void*)opToBoolVar);

    m_gf_opInitIter = cast<Function>(mod->getOrInsertFunction("opInitIter",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opInitIter, (void*)opInitIter);

    m_gf_opIterateVar = cast<Function>(mod->getOrInsertFunction("opIterateVar",
                                int32Ty,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opIterateVar, (void*)opIterateVar);

    m_gf_opNew = cast<Function>(mod->getOrInsertFunction("opNew",
                                voidPtrTy,//ret
                                voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opNew, (void*)opNew);

    m_gf_opDelete = cast<Function>(mod->getOrInsertFunction("opDelete",
                                voidTy,//ret
                                voidPtrTy, voidPtrTy, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opDelete, (void*)opDelete);

    m_gf_opDelete_int32 = cast<Function>(mod->getOrInsertFunction("opDelete_int32",
                                voidTy,//ret
                                voidPtrTy, int32Ty, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opDelete_int32, (void*)opDelete_int32);

    m_gf_opDelete_int64 = cast<Function>(mod->getOrInsertFunction("opDelete_int64",
                                voidTy,//ret
                                voidPtrTy, int64Ty, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opDelete_int64, (void*)opDelete_int64);

    m_gf_opDelete_str = cast<Function>(mod->getOrInsertFunction("opDelete_str",
                                voidTy,//ret
                                voidPtrTy, charPtrTy, int32Ty, voidPtrTy, voidPtrTy,//args
                                NULL) );
    addGlobalSymbal(ee, m_gf_opDelete_str, (void*)opDelete_str);
}

void acCodeGenerator::addGlobalSymbal(ExecutionEngine *ee, const GlobalValue *gv, void *addr)
{
    //ee->addGlobalMapping(gv, addr);
    m_globalSymbalMap.insert(std::make_pair(gv->getName(), addr));
}

void* acCodeGenerator::getGlobalSymbolAddress(const std::string &name)
{
    StringMap<void*>::iterator it = m_globalSymbalMap.find(name);
    if(it == m_globalSymbalMap.end())
    {
        return NULL;
    }
    return it->second;
}

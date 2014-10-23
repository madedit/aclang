/* see copyright notice in aclang.h */

#include "ac_ast.h"
#include "ac_codegen.h"
#include "ac_gc.h"
#include "ac_vm.h"
#include <llvm/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include <sstream>
#include <setjmp.h>

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

    createCoreFunctions();
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
    return m_vm->getModule();
}

void acCodeGenerator::generateCode()
{
    if(m_programBlockAST == 0)
    {
        m_vm->getMsgHandler()->error("ProgramBlock is NULL, ignore...\n");
        m_mainFunction = 0;
        return;
    }

    m_isCompileError = false;

    LLVMContext& context = m_vm->getLLVMContext();
    Module* module = m_vm->getModule();

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
              retVar, m_gv_rootTableVar, m_gv_rootArgArray, m_gv_rootTmpArray, 0);


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
        PassManager pm;
        pm.add(createPrintModulePass(outs()));
        pm.run(*module);
    }
}


GenericValue acCodeGenerator::runCode()
{
    if(m_mainFunction != 0)
    {
        //m_vm->getMsgHandler()->error("Running code...\n");
        ExecutionEngine* ee = m_vm->getExecutionEngine();
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

        m_rootArgArray->m_data.clear();
        m_rootTmpArray->m_data.clear();
        return v;
    }

    return GenericValue();
}

void acCodeGenerator::pushBlock(BasicBlock* bblock, BasicBlock* leave, NodeAST* ast, acCodeGenBlock::BlockType type,
                                Value* retVar, Value* thisVar, Value* argArray, Value* tmpArray, int tmpArraySize)
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

void* addTableVar_int(acTable* tab, int idx, acVM* vm)
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

void* createFunc(acVariable* funcVar, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acFunction* func = (acFunction*)gc->createObject(acVT_FUNCTION);
    funcVar->setValue(func);
    return func;
}

void setFuncPtr(acVariable* funcVar, void* funcPtr)
{
    acFunction* func = (acFunction*)funcVar->m_gcobj;
    func->m_funcPtr = funcPtr;
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
void* opGetVar(acVariable* parent, acVariable* key, int findInGlobal, int isFuncCall, acVM* vm)
{
    if(parent->m_valueType == acVT_ARRAY)
    {
        int idx = 0;
        switch(key->m_valueType)
        {
        case acVT_INT32:
            idx = key->m_int32;
            break;
        case acVT_INT64:
            idx = (int)key->m_int64;
            break;
        default:
            vm->runtimeError(std::string("Error: attempt to index array by '")+getVarTypeStr(key->m_valueType)+"'");
            return 0;
        }

        acArray* arr = (acArray*)parent->m_gcobj;
        if(idx < 0 || idx >= arr->size())
        {
            std::stringstream ss;
            ss << idx;
            vm->runtimeError(std::string("Error: array index out of bounds: ") + ss.str());
            return 0;
        }

        return arr->m_data[idx];
    }

    if(parent->m_valueType == acVT_STRING)
    {
        int idx = 0;
        switch(key->m_valueType)
        {
        case acVT_INT32:
            idx = key->m_int32;
            break;
        case acVT_INT64:
            idx = (int)key->m_int64;
            break;
        default:
            vm->runtimeError(std::string("Error: attempt to index string by '") + getVarTypeStr(key->m_valueType) + "'");
            return 0;
        }

        acString* str = (acString*)parent->m_gcobj;
        if(idx < 0 || idx >= str->m_data.size())
        {
            std::stringstream ss;
            ss << idx;
            vm->runtimeError(std::string("Error: string index out of bounds: ") + ss.str());
            return 0;
        }

        acGarbageCollector* gc = vm->getGarbageCollector();
        return gc->createVarWithData((acInt32)str->m_data[idx]);
    }

    if(parent->m_valueType != acVT_TABLE)
    {
        vm->runtimeError(std::string("Error: attempt to get element '")+toString(key, vm)+"' on '"+getVarTypeStr(parent->m_valueType)+"'");
        return 0;
    }

    acTable* table = (acTable*)parent->m_gcobj;
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
            vm->runtimeError(std::string("Error: element '") + toString(key, vm) + "' not found");
            return 0;
        }
    }

    return value;
}
void* opGetVar_int(acVariable* parent, int idx, int findInGlobal, int isFuncCall, acVM* vm)
{
    if(parent->m_valueType == acVT_ARRAY)
    {
        acArray* arr = (acArray*)parent->m_gcobj;
        if(idx < 0 || idx >= arr->size())
        {
            std::stringstream ss;
            ss << idx;
            vm->runtimeError(std::string("Error: array index out of bounds: ") + ss.str());
            return 0;
        }

        return arr->m_data[idx];
    }

    if(parent->m_valueType == acVT_STRING)
    {
        acString* str = (acString*)parent->m_gcobj;
        if(idx < 0 || idx >= (int)str->m_data.size())
        {
            std::stringstream ss;
            ss << idx;
            vm->runtimeError(std::string("Error: string index out of bounds: ") + ss.str());
            return 0;
        }

        acGarbageCollector* gc = vm->getGarbageCollector();
        return gc->createVarWithData((acInt32)str->m_data[idx]);
    }

    if(parent->m_valueType != acVT_TABLE)
    {
        std::stringstream ss;
        ss << idx;
        vm->runtimeError(std::string("Error: attempt to get element '")+ss.str()+"' on '"+getVarTypeStr(parent->m_valueType)+"'");
        return 0;
    }

    acTable* table = (acTable*)parent->m_gcobj;
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
            std::stringstream ss;
            ss << idx;
            vm->runtimeError(std::string("Error: element '") + ss.str() + "' not found");
            return 0;
        }
    }

    return value;
}
void* opGetVar_str(acVariable* parent, char* name, int findInGlobal, int isFuncCall, acVM* vm)
{
    if(parent->m_valueType != acVT_TABLE)
    {
        vm->runtimeError(std::string("Error: attempt to get element '")+name+"' on '"+getVarTypeStr(parent->m_valueType)+"'");
        return 0;
    }

    acTable* table = (acTable*)parent->m_gcobj;
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
            vm->runtimeError(std::string("Error: element '") + name + "' not found");
            return 0;
        }
    }

    return value;
}

//var parent.key or var parent[key]
void* opNewVar(acVariable* parent, acVariable* key, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_ARRAY:
        {
            int idx = 0;
            switch(key->m_valueType)
            {
            case acVT_INT32:
                idx = key->m_int32;
                break;
            case acVT_INT64:
                idx = (int)key->m_int64;
                break;
            default:
                vm->runtimeError(std::string("Error: attempt to index array by '")+getVarTypeStr(key->m_valueType)+"'");
                return 0;
            }

            acArray* arr = (acArray*)parent->m_gcobj;
            if(idx < 0 || idx >= arr->size())
            {
                std::stringstream ss;
                ss << idx;
                vm->runtimeError(std::string("Error: array index out of bounds: ") + ss.str());
                return 0;
            }

            var = (acVariable*)gc->createObject(acVT_NULL);
            arr->m_data[idx] = var;
        }
        break;
    case acVT_TABLE:
        {
            acTable* tab = (acTable*)parent->m_gcobj;
            var = (acVariable*)gc->createObject(acVT_NULL);
            tab->add(key, var);
        }
        break;
    default:
        vm->runtimeError(std::string("Error: attempt to create new var on '")+getVarTypeStr(parent->m_valueType)+"'");
        break;
    }

    return var;
}
void* opNewVar_int(acVariable* parent, int key, acVM* vm)
{
    acGarbageCollector* gc = vm->getGarbageCollector();
    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_ARRAY:
        {
            acArray* arr = (acArray*)parent->m_gcobj;
            if(key < 0 || key >= arr->size())
            {
                std::stringstream ss;
                ss << key;
                vm->runtimeError(std::string("Error: array index out of bounds: ") + ss.str());
                return 0;
            }

            var = (acVariable*)gc->createObject(acVT_NULL);
            arr->m_data[key] = var;
        }
        break;
    case acVT_TABLE:
        {
            var = (acVariable*)addTableVar_int((acTable*)parent->m_gcobj, key, vm);
        }
        break;
    default:
        vm->runtimeError(std::string("Error: attempt to create new var on '")+getVarTypeStr(parent->m_valueType)+"'");
        break;
    }

    return var;
}
void* opNewVar_str(acVariable* parent, char* key, acVM* vm)
{
    acVariable* var = 0;
    switch(parent->m_valueType)
    {
    case acVT_TABLE:
        {
            var = (acVariable*)addTableVar_str((acTable*)parent->m_gcobj, key, vm);
        }
        break;
    default:
        vm->runtimeError(std::string("Error: attempt to create new var on '")+getVarTypeStr(parent->m_valueType)+"'");
        break;
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
void opAddVar(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm)
{
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

    vm->runtimeError(std::string("Error: attempt to use op '+' on berween '")+
        getVarTypeStr(v1->m_valueType)+"' and '"+
        getVarTypeStr(v2->m_valueType)+"'");
}

//ret = v1 - v2
void opSubVar(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm)
{
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

    vm->runtimeError(std::string("Error: attempt to use op '-' on berween '")+
        getVarTypeStr(v1->m_valueType)+"' and '"+
        getVarTypeStr(v2->m_valueType)+"'");
}

//ret = v1 * v2
void opMulVar(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm)
{
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

    vm->runtimeError(std::string("Error: attempt to use op '*' on berween '")+
        getVarTypeStr(v1->m_valueType)+"' and '"+
        getVarTypeStr(v2->m_valueType)+"'");
}

//ret = v1 / v2
void opDivVar(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm)
{
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

    vm->runtimeError(std::string("Error: attempt to use op '/' on berween '")+
        getVarTypeStr(v1->m_valueType)+"' and '"+
        getVarTypeStr(v2->m_valueType)+"'");
}

//ret = v1 % v2
void opModVar(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm)
{
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

    vm->runtimeError(std::string("Error: attempt to use op '%' on berween '")+
        getVarTypeStr(v1->m_valueType)+"' and '"+
        getVarTypeStr(v2->m_valueType)+"'");
}

//v1(args); ret = args[0]
void opCallFunc(acVariable* var, acVariable* thisVar, acArray* argArray, acVM* vm)
{
    callFunction(var, thisVar, argArray, vm);
}

//return 1 for true; 0 for false
int opEqualVar(acVariable* lhs, acVariable* rhs, acVM* vm)
{
    return lhs->compare(rhs, vm) == 0;
}
//return 1 for true; 0 for false
int opNotEqualVar(acVariable* lhs, acVariable* rhs, acVM* vm)
{
    return lhs->compare(rhs, vm) != 0;
}
//return 1 for true; 0 for false
int opCompareVar(acVariable* lhs, acVariable* rhs, int tok_cmp, acVM* vm)
{
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

void opPostfixIncDecVar(acVariable* ret, acVariable* var, int tok, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        ret->setValue(var->m_int32);
        if(tok == TOK_PLUSPLUS) ++var->m_int32;
        else --var->m_int32;
        break;
    case acVT_INT64:
        ret->setValue(var->m_int64);
        if(tok == TOK_PLUSPLUS) ++var->m_int64;
        else --var->m_int64;
        break;
    case acVT_FLOAT:
        ret->setValue(var->m_float);
        if(tok == TOK_PLUSPLUS) ++var->m_float;
        else --var->m_float;
        break;
    case acVT_DOUBLE:
        ret->setValue(var->m_double);
        if(tok == TOK_PLUSPLUS) ++var->m_double;
        else --var->m_double;
        break;
    default:
        {
            std::string tokstr;
            if(tok == TOK_PLUSPLUS) tokstr = "++";
            else tokstr = "--";
            vm->runtimeError(std::string("Error: attempt to use postfix op '")+tokstr+"' on '"+getVarTypeStr(var->m_valueType)+"'"); 
        }
        break;
    }
}

void opPrefixIncDecVar(acVariable* var, int tok, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        if(tok == TOK_PLUSPLUS) ++var->m_int32;
        else --var->m_int32;
        break;
    case acVT_INT64:
        if(tok == TOK_PLUSPLUS) ++var->m_int64;
        else --var->m_int64;
        break;
    case acVT_FLOAT:
        if(tok == TOK_PLUSPLUS) ++var->m_float;
        else --var->m_float;
        break;
    case acVT_DOUBLE:
        if(tok == TOK_PLUSPLUS) ++var->m_double;
        else --var->m_double;
        break;
    default:
        {
            std::string tokstr;
            if(tok == TOK_PLUSPLUS) tokstr = "++";
            else tokstr = "--";
            vm->runtimeError(std::string("Error: attempt to use prefix op '")+tokstr+"' on '"+getVarTypeStr(var->m_valueType)+"'"); 
        }
        break;
    }
}

void opUnaryPlusMinusVar(acVariable* ret, acVariable* var, int tok, acVM* vm)
{
    switch(var->m_valueType)
    {
    case acVT_INT32:
        if(tok == TOK_PLUS) ret->setValue(+var->m_int32);
        else ret->setValue(-var->m_int32);
        break;
    case acVT_INT64:
        if(tok == TOK_PLUS) ret->setValue(+var->m_int64);
        else ret->setValue(-var->m_int64);
        break;
    case acVT_FLOAT:
        if(tok == TOK_PLUS) ret->setValue(+var->m_float);
        else ret->setValue(-var->m_float);
        break;
    case acVT_DOUBLE:
        if(tok == TOK_PLUS) ret->setValue(+var->m_double);
        else ret->setValue(-var->m_double);
        break;
    default:
        {
            std::string tokstr;
            if(tok == TOK_PLUS) tokstr = "+";
            else tokstr = "-";
            vm->runtimeError(std::string("Error: attempt to use unary op '")+tokstr+"' on '"+getVarTypeStr(var->m_valueType)+"'"); 
        }
        break;
    }
}

void opLogicalNotVar(acVariable* ret, acVariable* var, acVM* vm)
{
    ret->setValue(!toBool(var, vm));
}

void opLogicalAndOrVar(acVariable* ret, acVariable* var1, acVariable* var2, int tok, acVM* vm)
{
    if(tok == TOK_ANDAND)
    {
        ret->setValue(toBool(var1, vm) && toBool(var2, vm));
    }
    else
    {
        ret->setValue(toBool(var1, vm) || toBool(var2, vm));
    }
}

void opBitwiseNotVar(acVariable* ret, acVariable* var, acVM* vm)
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
        vm->runtimeError(std::string("Error: attempt to use bitwise op '~' on '")+getVarTypeStr(var->m_valueType)+"'"); 
        break;
    }
}

void opBitwiseAndOrXorVar(acVariable* ret, acVariable* var1, acVariable* var2, int tok, acVM* vm)
{
    switch(var1->m_valueType)
    {
    case acVT_INT32:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            switch(tok)
            {
            case TOK_AND:
                ret->setValue(var1->m_int32 & var2->m_int32);
                return;
            case TOK_OR:
                ret->setValue(var1->m_int32 | var2->m_int32);
                return;
            case TOK_XOR:
                ret->setValue(var1->m_int32 ^ var2->m_int32);
                return;
            }
            break;
        case acVT_INT64:
            switch(tok)
            {
            case TOK_AND:
                ret->setValue(acInt64(var1->m_int32) & var2->m_int64);
                return;
            case TOK_OR:
                ret->setValue(acInt64(var1->m_int32) | var2->m_int64);
                return;
            case TOK_XOR:
                ret->setValue(acInt64(var1->m_int32) ^ var2->m_int64);
                return;
            }
            break;
        }
        break;
    case acVT_INT64:
        switch(var2->m_valueType)
        {
        case acVT_INT32:
            switch(tok)
            {
            case TOK_AND:
                ret->setValue(var1->m_int64 & acInt64(var2->m_int32));
                return;
            case TOK_OR:
                ret->setValue(var1->m_int64 | acInt64(var2->m_int32));
                return;
            case TOK_XOR:
                ret->setValue(var1->m_int64 ^ acInt64(var2->m_int32));
                return;
            }
            break;
        case acVT_INT64:
            switch(tok)
            {
            case TOK_AND:
                ret->setValue(var1->m_int64 & var2->m_int64);
                return;
            case TOK_OR:
                ret->setValue(var1->m_int64 | var2->m_int64);
                return;
            case TOK_XOR:
                ret->setValue(var1->m_int64 ^ var2->m_int64);
                return;
            }
            break;
        }
        break;
    }

    std::string tokstr;
    switch(tok)
    {
    case TOK_AND:
        tokstr = "&";
        break;
    case TOK_OR:
        tokstr = "|";
        break;
    case TOK_XOR:
        tokstr = "^";
        break;
    }

    vm->runtimeError(std::string("Error: attempt to use bitwise op '")+tokstr+"' on between '"+
        getVarTypeStr(var1->m_valueType)+"' and '"+
        getVarTypeStr(var2->m_valueType)+"'" ); 
 
}

int opToBoolVar(acVariable* var, acVM* vm)
{
    return toBool(var, vm);
}

void opInitIter(acVariable* var, acVM* vm)
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
        vm->runtimeError(std::string("Error: attempt to iterate on '")+getVarTypeStr(var->m_valueType)+"'"); 
        break;
    }
}

int opIterateVar(acVariable* var, acVariable* key, acVariable* value, acVM* vm)
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
        vm->runtimeError(std::string("Error: attempt to iterate on '")+getVarTypeStr(var->m_valueType)+"'"); 
        break;
    }
    return false;
}

}//extern"C"
}//namespace

void acCodeGenerator::createGlobalValues()
{
    Module* mod = getModule();
    ExecutionEngine *ee = m_vm->getExecutionEngine();
    LLVMContext& context = getLLVMContext();

    //bind gc
    Type* int8Ty = Type::getInt8Ty(context);
    //PointerType* voidPtrTy = PointerType::get(Type::getInt8Ty(context), 0);
    //voidPtrTy->dump();

    //!!!global variable in llvm is PointerType
    
    m_gv_vm = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_vm", int8Ty));
    ee->addGlobalMapping(m_gv_vm, getVM());

    m_gv_cg = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_cg", int8Ty));
    ee->addGlobalMapping(m_gv_cg, this);

    m_gv_gc = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_gc", int8Ty));
    ee->addGlobalMapping(m_gv_gc, getGarbageCollector());

    m_gv_errorJmpBuf = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_errorJmpBuf", int8Ty));
    ee->addGlobalMapping(m_gv_errorJmpBuf, m_errorJmpBuf);
    //printf("%p %p\n", m_errorJmpBuf, &m_errorJmpBuf);
    //m_gv_errorJmpBuf->getType()->dump();

    m_gv_rootTableVar = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_rootTableVar", int8Ty));
    ee->addGlobalMapping(m_gv_rootTableVar, m_rootTableVar);

    m_gv_rootArgArray = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_rootArgArray", int8Ty));
    ee->addGlobalMapping(m_gv_rootArgArray, m_rootArgArray);

    m_gv_rootTmpArray = cast<GlobalVariable>(mod->getOrInsertGlobal("ac_rootTmpArray", int8Ty));
    ee->addGlobalMapping(m_gv_rootTmpArray, m_rootTmpArray);
}

void acCodeGenerator::createGlobalFunctions()
{
    Module* mod = getModule();
    ExecutionEngine *ee = m_vm->getExecutionEngine();
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
    ee->addGlobalMapping(m_gf_setJmp, (void*)_setjmp);

    m_gf_longJmp = cast<Function>(mod->getOrInsertFunction("myLongJmp",
                                 voidTy,//ret
                                 voidPtrTy, int32Ty,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_longJmp, (void*)myLongJmp);

    //
    m_gf_newArrayVar = cast<Function>(mod->getOrInsertFunction("newArrayVar",
                                 voidPtrTy,//ret
                                 voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_newArrayVar, (void*)newArrayVar);

    m_gf_setArrayVar = cast<Function>(mod->getOrInsertFunction("setArrayVar",
                                 voidTy,//ret
                                 voidPtrTy, int32Ty, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_setArrayVar, (void*)setArrayVar);

    m_gf_getArrayVar = cast<Function>(mod->getOrInsertFunction("getArrayVar",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_getArrayVar, (void*)getArrayVar);

    m_gf_getArrayVar_int = cast<Function>(mod->getOrInsertFunction("getArrayVar_int",
                                 voidPtrTy,//ret
                                 voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_getArrayVar_int, (void*)getArrayVar_int);

    m_gf_addTableKeyValue = cast<Function>(mod->getOrInsertFunction("addTableKeyValue",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_addTableKeyValue, (void*)addTableKeyValue);

    m_gf_addTableKeyValue_str = cast<Function>(mod->getOrInsertFunction("addTableKeyValue_str",
                                 voidTy,//ret
                                 voidPtrTy, charPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_addTableKeyValue_str, (void*)addTableKeyValue_str);

    m_gf_addTableVar = cast<Function>(mod->getOrInsertFunction("addTableVar",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_addTableVar, (void*)addTableVar);

    m_gf_addTableVar_str = cast<Function>(mod->getOrInsertFunction("addTableVar_str",
                                 voidPtrTy,//ret
                                 voidPtrTy, charPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_addTableVar_str, (void*)addTableVar_str);

    m_gf_getTableVar = cast<Function>(mod->getOrInsertFunction("getTableVar",
                                 voidPtrTy,//ret
                                 voidPtrTy, charPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_getTableVar, (void*)getTableVar);

    m_gf_createUpValueTable = cast<Function>(mod->getOrInsertFunction("createUpValueTable",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_createUpValueTable, (void*)createUpValueTable);

    m_gf_createFunc = cast<Function>(mod->getOrInsertFunction("createFunc",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_createFunc, (void*)createFunc);

    m_gf_setFuncPtr = cast<Function>(mod->getOrInsertFunction("setFuncPtr",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_setFuncPtr, (void*)setFuncPtr);

    m_gf_createTmpArray = cast<Function>(mod->getOrInsertFunction("createTmpArray",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_createTmpArray, (void*)createTmpArray);

    m_gf_createTable = cast<Function>(mod->getOrInsertFunction("createTable",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_createTable, (void*)createTable);

    m_gf_createArray = cast<Function>(mod->getOrInsertFunction("createArray",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_createArray, (void*)createArray);

    //
    m_gf_opGetVar = cast<Function>(mod->getOrInsertFunction("opGetVar",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy, int32Ty, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opGetVar, (void*)opGetVar);

    m_gf_opGetVar_int = cast<Function>(mod->getOrInsertFunction("opGetVar_int",
                                 voidPtrTy,//ret
                                 voidPtrTy, int32Ty, int32Ty, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opGetVar_int, (void*)opGetVar_int);

    m_gf_opGetVar_str = cast<Function>(mod->getOrInsertFunction("opGetVar_str",
                                 voidPtrTy,//ret
                                 voidPtrTy, charPtrTy, int32Ty, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opGetVar_str, (void*)opGetVar_str);

    m_gf_opNewVar = cast<Function>(mod->getOrInsertFunction("opNewVar",
                                 voidPtrTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opNewVar, (void*)opNewVar);

    m_gf_opNewVar_int = cast<Function>(mod->getOrInsertFunction("opNewVar_int",
                                 voidPtrTy,//ret
                                 voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opNewVar_int, (void*)opNewVar_int);

    m_gf_opNewVar_str = cast<Function>(mod->getOrInsertFunction("opNewVar_str",
                                 voidPtrTy,//ret
                                 voidPtrTy, charPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opNewVar_str, (void*)opNewVar_str);

    //
    m_gf_opAssignVar = cast<Function>(mod->getOrInsertFunction("opAssignVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar, (void*)opAssignVar);

    m_gf_opAssignVar_null = cast<Function>(mod->getOrInsertFunction("opAssignVar_null",
                                 voidTy,//ret
                                 voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_null, (void*)opAssignVar_null);

    m_gf_opAssignVar_bool = cast<Function>(mod->getOrInsertFunction("opAssignVar_bool",
                                 voidTy,//ret
                                 voidPtrTy, int32Ty,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_bool, (void*)opAssignVar_bool);

    m_gf_opAssignVar_int32 = cast<Function>(mod->getOrInsertFunction("opAssignVar_int32",
                                 voidTy,//ret
                                 voidPtrTy, int32Ty,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_int32, (void*)opAssignVar_int32);

    m_gf_opAssignVar_int64 = cast<Function>(mod->getOrInsertFunction("opAssignVar_int64",
                                 voidTy,//ret
                                 voidPtrTy, int64Ty,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_int64, (void*)opAssignVar_int64);

    m_gf_opAssignVar_float = cast<Function>(mod->getOrInsertFunction("opAssignVar_float",
                                 voidTy,//ret
                                 voidPtrTy, floatTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_float, (void*)opAssignVar_float);

    m_gf_opAssignVar_double = cast<Function>(mod->getOrInsertFunction("opAssignVar_double",
                                 voidTy,//ret
                                 voidPtrTy, doubleTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_double, (void*)opAssignVar_double);

    m_gf_opAssignVar_str = cast<Function>(mod->getOrInsertFunction("opAssignVar_str",
                                 voidTy,//ret
                                 voidPtrTy, charPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAssignVar_str, (void*)opAssignVar_str);

    m_gf_opAddVar = cast<Function>(mod->getOrInsertFunction("opAddVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opAddVar, (void*)opAddVar);

    m_gf_opSubVar = cast<Function>(mod->getOrInsertFunction("opSubVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opSubVar, (void*)opSubVar);

    m_gf_opMulVar = cast<Function>(mod->getOrInsertFunction("opMulVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opMulVar, (void*)opMulVar);

    m_gf_opDivVar = cast<Function>(mod->getOrInsertFunction("opDivVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opDivVar, (void*)opDivVar);

    m_gf_opModVar = cast<Function>(mod->getOrInsertFunction("opModVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opModVar, (void*)opModVar);

    m_gf_opCallFunc = cast<Function>(mod->getOrInsertFunction("opCallFunc",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opCallFunc, (void*)opCallFunc);

    m_gf_opEqualVar = cast<Function>(mod->getOrInsertFunction("opEqualVar",
                                 int32Ty,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opEqualVar, (void*)opEqualVar);

    m_gf_opNotEqualVar = cast<Function>(mod->getOrInsertFunction("opNotEqualVar",
                                 int32Ty,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opNotEqualVar, (void*)opNotEqualVar);

    m_gf_opCompareVar = cast<Function>(mod->getOrInsertFunction("opCompareVar",
                                 int32Ty,//ret
                                 voidPtrTy, voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opCompareVar, (void*)opCompareVar);

    m_gf_opPostfixIncDecVar = cast<Function>(mod->getOrInsertFunction("opPostfixIncDecVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opPostfixIncDecVar, (void*)opPostfixIncDecVar);

    m_gf_opPrefixIncDecVar = cast<Function>(mod->getOrInsertFunction("opPrefixIncDecVar",
                                 voidTy,//ret
                                 voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opPrefixIncDecVar, (void*)opPrefixIncDecVar);

    m_gf_opUnaryPlusMinusVar = cast<Function>(mod->getOrInsertFunction("opUnaryPlusMinusVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opUnaryPlusMinusVar, (void*)opUnaryPlusMinusVar);

    m_gf_opLogicalNotVar = cast<Function>(mod->getOrInsertFunction("opLogicalNotVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opLogicalNotVar, (void*)opLogicalNotVar);

    m_gf_opLogicalAndOrVar = cast<Function>(mod->getOrInsertFunction("opLogicalAndOrVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opLogicalAndOrVar, (void*)opLogicalAndOrVar);

    m_gf_opBitwiseNotVar = cast<Function>(mod->getOrInsertFunction("opBitwiseNotVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opBitwiseNotVar, (void*)opBitwiseNotVar);

    m_gf_opBitwiseAndOrXorVar = cast<Function>(mod->getOrInsertFunction("opBitwiseAndOrXorVar",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, int32Ty, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opBitwiseAndOrXorVar, (void*)opBitwiseAndOrXorVar);

    m_gf_opToBoolVar = cast<Function>(mod->getOrInsertFunction("opToBoolVar",
                                 int32Ty,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opToBoolVar, (void*)opToBoolVar);

    m_gf_opInitIter = cast<Function>(mod->getOrInsertFunction("opInitIter",
                                 voidTy,//ret
                                 voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opInitIter, (void*)opInitIter);

    m_gf_opIterateVar = cast<Function>(mod->getOrInsertFunction("opIterateVar",
                                 int32Ty,//ret
                                 voidPtrTy, voidPtrTy, voidPtrTy, voidPtrTy,//args
                                 NULL) );
    ee->addGlobalMapping(m_gf_opIterateVar, (void*)opIterateVar);
}

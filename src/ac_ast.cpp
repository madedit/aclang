/* see copyright notice in aclang.h */

#include "ac_ast.h"
#include "ac_codegen.h"
#include "ac_msghandler.h"
#include "ac_variable.h"
#include "ac_vm.h"
#include "yyparser.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <iostream>

using namespace llvm;

void NodeASTList::add_case_ast(CaseAST* node)
{
    if(node->m_expr == 0)
    {
        NodeASTVec::iterator it = m_nodeASTVec.begin();
        NodeASTVec::iterator itend = m_nodeASTVec.end();
        for(; it != itend; ++it)
        {
            CaseAST* ast = (CaseAST*)*it;
            if(ast->m_expr == 0)
            {
                m_hasMultipleDefaultStmt = true;
            }
        }
    }

    m_nodeASTVec.push_back(node);
}


Value* NullAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall(cg->m_gf_opAssignVar_null, val);
    return val;
}

Value* BooleanAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_bool, val, builder.getInt32(m_val));
    return val;
}

Value* Int32AST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_int32, val, builder.getInt32(m_val));
    return val;
}

Value* Int64AST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_int64, val, builder.getInt64(m_val));
    return val;
}

Value* FloatAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_float, val, ConstantFP::get(builder.getFloatTy(), m_val));
    return val;
}

Value* DoubleAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_double, val, ConstantFP::get(builder.getDoubleTy(), m_val));
    return val;
}

Value* StringAST::codeGen(acCodeGenerator* cg)
{
    //std::cout << "Creating string: " << m_val << std::endl;
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall3(cg->m_gf_opAssignVar_str, val, cg->createStringPtr(m_val, block, builder), cg->m_gv_vm);
    return val;
}

Value* TableAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);

    Value* table = builder.CreateCall2(cg->m_gf_createTable, val, cg->m_gv_vm);

    //create contents in table
    if(m_keyValueList != 0)
    {
        Twine kvName("kv");
        NodeASTVec::iterator it = m_keyValueList->m_nodeASTVec.begin();
        NodeASTVec::iterator itend = m_keyValueList->m_nodeASTVec.end();
        while(it != itend)
        {
            KeyValueAST* kv = (KeyValueAST*)(*it);
            
            if(kv->m_key.length() > 0)
            {
                if(kv->m_value == 0)
                {
                    builder.CreateCall3(cg->m_gf_addTableVar_str, table, cg->createStringPtr(kv->m_key, block, builder), cg->m_gv_vm, kvName);
                }
                else
                {
                    Value* v = kv->m_value->codeGen(cg);
                    builder.CreateCall4(cg->m_gf_addTableKeyValue_str, table, cg->createStringPtr(kv->m_key, block, builder), v, cg->m_gv_vm);
                }
            }
            else
            {
                Value* k = kv->m_keyExpr->codeGen(cg);
                if(kv->m_value == 0)
                {
                    builder.CreateCall3(cg->m_gf_addTableVar, table, k, cg->m_gv_vm, kvName);
                }
                else
                {
                    Value* v = kv->m_value->codeGen(cg);
                    builder.CreateCall4(cg->m_gf_addTableKeyValue, table, k, v, cg->m_gv_vm);
                }
            }

            ++it;
        };
    }

    return val;
}

inline void codeGenAssignment(IRBuilder<>& builder, Value* val, NodeAST* assExpr, acCodeGenerator* cg)
{
    switch(assExpr->m_type)
    {
    case NodeAST::tNullAST:
        {
            builder.CreateCall(cg->m_gf_opAssignVar_null, val);
        }
        break;
    case NodeAST::tBooleanAST:
        {
            BooleanAST* ast = (BooleanAST*)assExpr;
            builder.CreateCall2(cg->m_gf_opAssignVar_bool, val, builder.getInt32(ast->m_val));
        }
        break;
    case NodeAST::tInt32AST:
        {
            Int32AST* ast = (Int32AST*)assExpr;
            builder.CreateCall2(cg->m_gf_opAssignVar_int32, val, builder.getInt32(ast->m_val));
        }
        break;
    case NodeAST::tInt64AST:
        {
            Int64AST* ast = (Int64AST*)assExpr;
            builder.CreateCall2(cg->m_gf_opAssignVar_int64, val, builder.getInt64(ast->m_val));
        }
        break;
    case NodeAST::tFloatAST:
        {
            FloatAST* ast = (FloatAST*)assExpr;
            builder.CreateCall2(cg->m_gf_opAssignVar_float, val, ConstantFP::get(builder.getFloatTy(), ast->m_val));
        }
        break;
    case NodeAST::tDoubleAST:
        {
            DoubleAST* ast = (DoubleAST*)assExpr;
            builder.CreateCall2(cg->m_gf_opAssignVar_double, val, ConstantFP::get(builder.getDoubleTy(), ast->m_val));
        }
        break;
    case NodeAST::tStringAST:
        {
            StringAST* ast = (StringAST*)assExpr;
            builder.CreateCall3(cg->m_gf_opAssignVar_str, val, cg->createStringPtr(ast->m_val, cg->currentBlock(), builder), cg->m_gv_vm);
        }
        break;
    default:
        {
            Value* rhs = assExpr->codeGen(cg);
            builder.CreateCall2(cg->m_gf_opAssignVar, val, rhs);
        }
    }
}

Value* ArrayAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);

    Value* array = builder.CreateCall2(cg->m_gf_createArray, val, cg->m_gv_vm);

    //create contents in array
    if(m_elementList != 0)
    {
        ConstantInt* const_idx = builder.getInt32(-1);

        NodeASTVec::iterator it = m_elementList->m_nodeASTVec.begin();
        NodeASTVec::iterator itend = m_elementList->m_nodeASTVec.end();
        while(it != itend)
        {
            Value* var = builder.CreateCall3(cg->m_gf_newArrayVar, array, const_idx, cg->m_gv_vm);
            NodeAST* ele = (NodeAST*)(*it);
            codeGenAssignment(builder, var, ele, cg);

            ++it;
        }
    }

    return val;
}

inline CallInst *CreateCall6(IRBuilder<>& builder, Value *Callee, Value *Arg1, Value *Arg2, Value *Arg3,
    Value *Arg4, Value *Arg5, Value *Arg6)
{
    Value *Args[] = { Arg1, Arg2, Arg3, Arg4, Arg5, Arg6 };
    return builder.Insert(CallInst::Create(Callee, Args));
}

inline Value* codeGenGetVar(IRBuilder<>& builder, Value* parent, NodeAST* keyExpr, int findInGlobal, int isFuncCall, Value* debugInfo, acCodeGenerator* cg)
{
    switch(keyExpr->m_type)
    {
    case NodeAST::tInt32AST:
        {
            Int32AST* ast = (Int32AST*)keyExpr;
            return builder.CreateCall5(cg->m_gf_opGetVar_int32, parent, builder.getInt32(ast->m_val), builder.getInt32(findInGlobal), builder.getInt32(isFuncCall), cg->m_gv_vm);
        }
        break;
    case NodeAST::tInt64AST:
        {
            Int64AST* ast = (Int64AST*)keyExpr;
            return builder.CreateCall5(cg->m_gf_opGetVar_int64, parent, builder.getInt64(ast->m_val), builder.getInt32(findInGlobal), builder.getInt32(isFuncCall), cg->m_gv_vm);
        }
        break;
    case NodeAST::tStringAST:
        {
            StringAST* ast = (StringAST*)keyExpr;
            return builder.CreateCall5(cg->m_gf_opGetVar_str,
                parent,
                cg->createStringPtr(ast->m_val, cg->currentBlock(), builder),
                builder.getInt32(findInGlobal),
                builder.getInt32(isFuncCall),
                cg->m_gv_vm,
                Twine(isFuncCall?"f_":"v_").concat(ast->m_val));
        }
        break;
    }

    Value* key = keyExpr->codeGen(cg);
    return CreateCall6(builder, cg->m_gf_opGetVar, parent, key, builder.getInt32(findInGlobal), builder.getInt32(isFuncCall), debugInfo, cg->m_gv_vm);
}

Value* GetVarAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = 0;

    ConstantInt* zero = builder.getInt32(0);
    ConstantInt* const_isFuncCall = builder.getInt32(m_isFuncCall);

    if(m_parentExpr != 0)
    {
        m_parent = m_parentExpr->codeGen(cg);

        if(m_keyExpr != 0)
        {
            val = codeGenGetVar(builder, m_parent, m_keyExpr, 0, m_isFuncCall, cg->createDebugInfoPtr(m_line, block, builder), cg);
        }
        else
        {
            val = builder.CreateCall5(cg->m_gf_opGetVar_str,
                m_parent,
                cg->createStringPtr(m_keyIdentifier, block, builder),
                zero,
                const_isFuncCall,
                cg->m_gv_vm,
                Twine(m_isFuncCall?"f_":"v_").concat(m_keyIdentifier));
        }
    }
    else
    {
        switch(m_scope)
        {
        case NONE:
            if(m_keyExpr != 0)
            {
                val = codeGenGetVar(builder, block->m_thisVar, m_keyExpr, 1, m_isFuncCall, cg->createDebugInfoPtr(m_line, block, builder), cg);
            }
            else
            {
                //find in localvar first
                val = cg->findLocalVar(m_keyIdentifier);

                //then find in this & global table
                if(val == 0)
                {
                    val = builder.CreateCall5(cg->m_gf_opGetVar_str,
                        block->m_thisVar,
                        cg->createStringPtr(m_keyIdentifier, block, builder),
                        builder.getInt32(1),
                        const_isFuncCall,
                        cg->m_gv_vm,
                        Twine(m_isFuncCall?"f_":"v_").concat(m_keyIdentifier));
                }
            }
            break;
        case THIS:
            if(m_keyExpr != 0)
            {
                val = codeGenGetVar(builder, block->m_thisVar, m_keyExpr, 0, m_isFuncCall, cg->createDebugInfoPtr(m_line, block, builder), cg);
            }
            else
            {
                val = builder.CreateCall5(cg->m_gf_opGetVar_str,
                    block->m_thisVar,
                    cg->createStringPtr(m_keyIdentifier, block, builder),
                    zero,
                    const_isFuncCall,
                    cg->m_gv_vm,
                    Twine(m_isFuncCall?"f_":"v_").concat(m_keyIdentifier));
            }
            break;
        case GLOBAL:
            if(m_keyExpr != 0)
            {
                val = codeGenGetVar(builder, cg->m_gv_rootTableVar, m_keyExpr, 0, m_isFuncCall, cg->createDebugInfoPtr(m_line, block, builder), cg);
            }
            else
            {
                val = builder.CreateCall5(cg->m_gf_opGetVar_str,
                    cg->m_gv_rootTableVar,
                    cg->createStringPtr(m_keyIdentifier, block, builder),
                    zero,
                    const_isFuncCall,
                    cg->m_gv_vm,
                    Twine(m_isFuncCall?"f_":"v_").concat(m_keyIdentifier));
            }
            break;
        }
    }

    return val;
}

inline Value* codeGenNewVar(IRBuilder<>& builder, Value* parent, NodeAST* keyExpr, acCodeGenerator* cg)
{
    switch(keyExpr->m_type)
    {
    case NodeAST::tInt32AST:
        {
            Int32AST* ast = (Int32AST*)keyExpr;
            return builder.CreateCall3(cg->m_gf_opNewVar_int32, parent, builder.getInt32(ast->m_val), cg->m_gv_vm);
        }
        break;
    case NodeAST::tInt64AST:
        {
            Int64AST* ast = (Int64AST*)keyExpr;
            return builder.CreateCall3(cg->m_gf_opNewVar_int64, parent, builder.getInt64(ast->m_val), cg->m_gv_vm);
        }
        break;
    case NodeAST::tStringAST:
        {
            StringAST* ast = (StringAST*)keyExpr;
            return builder.CreateCall3(cg->m_gf_opNewVar_str, parent, cg->createStringPtr(ast->m_val, cg->currentBlock(), builder), cg->m_gv_vm);
        }
        break;
    }
    Value* key = keyExpr->codeGen(cg);
    return builder.CreateCall3(cg->m_gf_opNewVar, parent, key, cg->m_gv_vm);
}

Value* codeGenVarDecl(IRBuilder<>& builder, GetVarAST* varExpr, bool isLocal, acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();

    Value* val = 0;
    if(isLocal)
    {
        if(varExpr->m_parentExpr != 0 || varExpr->m_scope != GetVarAST::NONE)
        {
            cg->getMsgHandler()->error("Error: cannot declare a local variable with parent scope.");
            cg->setCompileError(true);
            return 0;
        }

        val = builder.CreateCall3(cg->m_gf_newArrayVar, block->m_argArray, builder.getInt32(-1), cg->m_gv_vm, Twine("v_").concat(varExpr->m_keyIdentifier));
    }
    else
    {
        Value* parent = 0;
        if(varExpr->m_parentExpr != 0)
        {
            parent = varExpr->m_parentExpr->codeGen(cg);
        }
        else
        {
            switch(varExpr->m_scope)
            {
            case GetVarAST::NONE:
            case GetVarAST::THIS:
                parent = block->m_thisVar;
                break;
            case GetVarAST::GLOBAL:
                parent = cg->m_gv_rootTableVar;
                break;
            }
        }
        
        if(varExpr->m_keyExpr != 0)
        {
            val = codeGenNewVar(builder, parent, varExpr->m_keyExpr, cg);
        }
        else
        {
            val = builder.CreateCall3(cg->m_gf_opNewVar_str, parent, cg->createStringPtr(varExpr->m_keyIdentifier, block, builder), cg->m_gv_vm, Twine("v_").concat(varExpr->m_keyIdentifier));
        }
    }

    return val;
}

Value* VariableDeclarationAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val = codeGenVarDecl(builder, m_varExpr, m_isLocal, cg);

    if(m_assignmentExpr != 0)
    {
        codeGenAssignment(builder, val, m_assignmentExpr, cg);
    }

    //delay adding to localvars
    if(m_isLocal)
    {
        block->m_localVars.push_back(std::make_pair(m_varExpr->m_keyIdentifier, val));
    }

    return val;
}

Value* VariableDeclarationListAST::codeGen(acCodeGenerator* cg)
{
    NodeASTVec::iterator it = m_varDeclList->m_nodeASTVec.begin();
    NodeASTVec::iterator itend = m_varDeclList->m_nodeASTVec.end();

    acCodeGenBlock* block = cg->currentBlock();
    int tmpSize = block->m_tmpArraySize;
    while(it != itend)
    {
        //restore tmpSize
        block->m_tmpArraySize = tmpSize;
        (*it)->codeGen(cg);

        if(cg->isCompileError()) return 0;
        ++it;
    }
    
    return 0;
}

Value* FunctionAST::codeGen(acCodeGenerator* cg)
{
    if(m_isLocal && (m_nameExpr->m_parentExpr != 0 || m_nameExpr->m_scope != GetVarAST::NONE))
    {
        cg->getMsgHandler()->error("Error: cannot declare a local function with parent scope.");
        cg->setCompileError(true);
        return 0;
    }

    m_upblock = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    LLVMContext& context = cg->getLLVMContext();
    Type* voidTy = Type::getVoidTy(context);
    PointerType* voidPtrTy = PointerType::get(Type::getInt8Ty(context), 0);

    std::vector<Type*> argTypes;
    argTypes.push_back(voidPtrTy);//thisVar
    argTypes.push_back(voidPtrTy);//argArray
    argTypes.push_back(voidPtrTy);//upValueTable
    FunctionType* funcType = FunctionType::get(voidTy, makeArrayRef(argTypes), false);

    std::string name("func");
    static int count = 0;
    name += Twine(count++).str();
    std::string funcName;
    if(m_nameExpr != 0)
    {
        if(m_nameExpr->m_keyIdentifier.length() > 0)
        {
            funcName = "_";
            funcName += m_nameExpr->m_keyIdentifier;
        }
    }
    else
    {
        funcName = ".anony";
    }
    Twine name2 = Twine(name).concat(funcName);

    llvm::Function* llvmFunc = Function::Create(funcType, GlobalValue::InternalLinkage, name2, cg->getModule());
    acFunctionData* acFuncData = (acFunctionData*)cg->getGarbageCollector()->createObject(acVT_FUNCTIONDATA);
    acFuncData->m_llvmFunc = llvmFunc;
    m_upblock->m_funcDataList->push_back(acFuncData);

    m_funcVar = 0;
    if(m_isLocal)
    {
        m_funcVar = builder.CreateCall3(cg->m_gf_newArrayVar, m_upblock->m_argArray, builder.getInt32(-1), cg->m_gv_vm, Twine("f_").concat(m_nameExpr->m_keyIdentifier));
        m_upblock->m_localVars.push_back(std::make_pair(m_nameExpr->m_keyIdentifier, m_funcVar));
    }
    else if(m_nameExpr == 0)//anonymous function
    {
        m_funcVar = builder.CreateCall3(cg->m_gf_getArrayVar_int,
            m_upblock->m_tmpArray, builder.getInt32(m_upblock->m_tmpArraySize++), cg->m_gv_vm);
    }
    else
    {
        Value* parent = 0;
        
        if(m_nameExpr->m_parentExpr != 0)
        {
            parent = m_nameExpr->m_parentExpr->codeGen(cg);
        }
        else
        {
            switch(m_nameExpr->m_scope)
            {
            case GetVarAST::NONE:
            case GetVarAST::THIS:
                parent = m_upblock->m_thisVar;
                break;
            case GetVarAST::GLOBAL:
                parent = cg->m_gv_rootTableVar;
                break;
            }
        }

        if(m_nameExpr->m_keyExpr != 0)
        {
            m_funcVar = codeGenNewVar(builder, parent, m_nameExpr->m_keyExpr, cg);
        }
        else
        {
            m_funcVar = builder.CreateCall3(cg->m_gf_opNewVar_str, parent, cg->createStringPtr(m_nameExpr->m_keyIdentifier, m_upblock, builder), cg->m_gv_vm, Twine("f_").concat(m_nameExpr->m_keyIdentifier));
        }
    }

    //build function
    builder.CreateCall2(cg->m_gf_createFunc, m_funcVar, cg->m_gv_vm);

    Value* acFuncDataToPtr;
    if(sizeof(void*) == sizeof(uint64_t))
    {
        acFuncDataToPtr = builder.CreateIntToPtr(builder.getInt64(uintptr_t(acFuncData)), voidPtrTy);
    }
    else
    {
        acFuncDataToPtr = builder.CreateIntToPtr(builder.getInt32(uintptr_t(acFuncData)), voidPtrTy);
    }

    //store function values
    m_buildUpValueTableInsertPoint = builder.CreateCall2(cg->m_gf_setFuncPtr, m_funcVar, acFuncDataToPtr);

    //function init
    BasicBlock* entry = BasicBlock::Create(context, "entry", llvmFunc, 0);
    BasicBlock* leave = BasicBlock::Create(context, "leave", llvmFunc, 0);
    builder.SetInsertPoint(entry);

    //used strings & debugInfos in the function
    std::list<std::string>* strList = new std::list<std::string>();
    std::list<acDebugInfo>* debugInfoList = new std::list<acDebugInfo>();
    acFuncData->m_stringList = strList;
    acFuncData->m_debugInfoList = debugInfoList;

    std::list<acGCObject*>* funcDataList = new std::list<acGCObject*>();
    cg->pushBlock(entry, leave, this, acCodeGenBlock::FUNCTION, 0, 0, 0, 0, 0, strList, funcDataList, debugInfoList);
    m_localblock = cg->currentBlock();

    //this, args, upvalues
    Function::arg_iterator argsValues = llvmFunc->arg_begin();
    Value* thisVar = argsValues++;
    thisVar->setName("thisVar");
    Value* argArray = argsValues++;
    argArray->setName("argArray");
    m_localUpValueTable = argsValues++;
    m_localUpValueTable->setName("upValueTable");

    m_localblock->m_thisVar = thisVar;
    m_localblock->m_argArray = argArray;

    //create local args
    std::list<std::pair<std::string, Value*> >& localVars = m_localblock->m_localVars;

    localVars.push_back(std::make_pair("this", thisVar));

    if(m_args != 0)
    {
        int argIndex = 0;
        StringVec::iterator it = m_args->m_stringVec.begin();
        StringVec::iterator itend = m_args->m_stringVec.end();
        for(; it != itend; ++it)
        {
            CallInst* localVar = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                argArray, builder.getInt32(argIndex++), cg->m_gv_vm, *it);

            localVars.push_back(std::make_pair(*it, localVar));
        }
    }

    //retVar
    m_localblock->m_retVar = builder.CreateCall3(cg->m_gf_newArrayVar, argArray, builder.getInt32(-1), cg->m_gv_vm, "retVar");

    //tmpArray
    m_localblock->m_tmpArray = builder.CreateCall2(cg->m_gf_createTmpArray, argArray, cg->m_gv_vm, Twine("tmpArray"));
    m_localUpValueInsertPoint = (Instruction*)m_localblock->m_tmpArray;
    
    //function body codegen
    m_body->codeGen(cg);

    if(builder.GetInsertBlock()->getTerminator() == 0)
        builder.CreateBr(leave);

    builder.SetInsertPoint(leave);
    //set retVar
    builder.CreateCall4(cg->m_gf_setArrayVar, argArray, builder.getInt32(0), m_localblock->m_retVar, cg->m_gv_vm);
    //leave block return
    builder.CreateRetVoid();

    cg->popBlock();

    //setFuncMiscData
    Value* funcDataListToPtr;
    bool setMiscData = false;

    if(funcDataList->size() > 0)
    {
        if(sizeof(void*) == sizeof(uint64_t))
        {
            funcDataListToPtr = builder.CreateIntToPtr(builder.getInt64(uintptr_t(funcDataList)), voidPtrTy);
        }
        else
        {
            funcDataListToPtr = builder.CreateIntToPtr(builder.getInt32(uintptr_t(funcDataList)), voidPtrTy);
        }
        setMiscData = true;
    }
    else
    {
        if(sizeof(void*) == sizeof(uint64_t))
        {
            funcDataListToPtr = builder.CreateIntToPtr(builder.getInt64(0), voidPtrTy);
        }
        else
        {
            funcDataListToPtr = builder.CreateIntToPtr(builder.getInt32(0), voidPtrTy);
        }
        delete funcDataList;
    }
    
    if(setMiscData)
    {
        builder.SetInsertPoint(m_buildUpValueTableInsertPoint);
        builder.CreateCall2(cg->m_gf_setFuncMiscData, m_funcVar, funcDataListToPtr);
    }

    //restore InsertPoint
    builder.SetInsertPoint(cg->currentBlock()->m_bblock);

    return m_funcVar;
}

Value* FunctionAST::codeGenForUpValue(acCodeGenerator* cg, const std::string& name, Value* upValue)
{
    Value* val = 0;
    
    //add upValue to upValueTable in upblock
    IRBuilder<> upbuilder(m_upblock->m_bblock);
    upbuilder.SetInsertPoint(m_buildUpValueTableInsertPoint);

    if(m_upValueTable == 0)
    {
        m_upValueTable = upbuilder.CreateCall2(cg->m_gf_createUpValueTable, m_funcVar, cg->m_gv_vm, Twine("UpValTab"));
    }

    Value* namePtr = cg->createStringPtr(name, m_upblock, upbuilder);
    upbuilder.CreateCall4(cg->m_gf_addTableKeyValue_str, m_upValueTable, namePtr, upValue, cg->m_gv_vm);

    //get upValue from upValueTable in localblock
    IRBuilder<> builder(m_localblock->m_bblock);
    builder.SetInsertPoint(m_localUpValueInsertPoint);

    Value* localNamePtr = cg->createStringPtr(name, m_localblock, builder);
    val = builder.CreateCall3(cg->m_gf_getTableVar, m_localUpValueTable, localNamePtr, cg->m_gv_vm, Twine("v_").concat(name));
    
    //add upvalue to localvars
    m_localblock->m_localVars.push_back(std::make_pair(name, val));

    return val;
}

Value* CallAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    if(m_callee->m_type == tGetVarAST)
    {
        ((GetVarAST*)m_callee)->m_isFuncCall = 1;
    }

    Value* funcVar = m_callee->codeGen(cg);

    Value* tmpVar = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    Value* argArray = builder.CreateCall2(cg->m_gf_createArray, tmpVar, cg->m_gv_vm, Twine("v_argArray"));

    //push args
    if(m_args != 0)
    {
        NodeASTVec::iterator it = m_args->m_nodeASTVec.begin();
        NodeASTVec::iterator itend = m_args->m_nodeASTVec.end();
        for(; it != itend; ++it)
        {
            Value* arg = builder.CreateCall3(cg->m_gf_newArrayVar, argArray, builder.getInt32(-1), cg->m_gv_vm);
            codeGenAssignment(builder, arg, *it, cg);
        }
    }

    //this
    Value* thisVar = 0;
    if(m_callee->m_type == tGetVarAST)
    {
        thisVar = ((GetVarAST*)m_callee)->m_parent;
    }
    if(thisVar == 0)
    {
        thisVar = block->m_thisVar;
    }

    //call function
    builder.CreateCall4(cg->m_gf_opCallFunc, funcVar, thisVar, argArray, cg->m_gv_vm);

    //get return value
    return builder.CreateCall3(cg->m_gf_getArrayVar_int, argArray, builder.getInt32(0), cg->m_gv_vm, Twine("v_func_ret"));
}

Value* ReturnAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    if(m_expr != 0)
    {
        codeGenAssignment(builder, block->m_retVar, m_expr, cg);
        if(cg->isCompileError()) return 0;
    }

    block->m_isBlockEnd = true;

    builder.CreateBr(&block->m_bblock->getParent()->getBasicBlockList().back());
    //BranchInst* val = builder.CreateBr(block->m_leave);

    return 0;
}

Value* BlockAST::codeGen(acCodeGenerator* cg)
{
    NodeASTVec::const_iterator it;
    Value* last = NULL;
    acCodeGenBlock* block = cg->currentBlock();

    int localVarSize = block->m_localVars.size();
    int tmpSize = block->m_tmpArraySize;

    for (it = m_statements.begin(); it != m_statements.end(); it++)
    {
        //restore tmpSize
        block->m_tmpArraySize = tmpSize;
        last = (*it)->codeGen(cg);

        if(cg->isCompileError()) return 0;

        //isReturn: ignore the following stmts
        if(block->m_isBlockEnd) break;
    }

    block->m_isBlockEnd = false;
    //restore localvars size
    block->m_localVars.resize(localVarSize);

    return last;
}

Value* PostfixIncrementAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* org = m_expr->codeGen(cg);
    Value* op = builder.getInt32(m_op);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);

    builder.CreateCall4(cg->m_gf_opPostfixIncDecVar, val, org, op, cg->m_gv_vm);

    return val;
}

Value* UnaryAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val = 0;
    switch(m_op)
    {
    case TOK_PLUSPLUS:
    case TOK_MINUSMINUS:
        {
            Value* org = m_expr->codeGen(cg);
            Value* op = builder.getInt32(m_op);
            builder.CreateCall3(cg->m_gf_opPrefixIncDecVar, org, op, cg->m_gv_vm);
            val = org;
        }
        break;
    case TOK_PLUS:
        {
            val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
            switch(m_expr->m_type)
            {
            case NodeAST::tInt32AST:
                {
                    Int32AST* ast = (Int32AST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_int32, val, builder.getInt32(ast->m_val));
                }
                break;
            case NodeAST::tInt64AST:
                {
                    Int64AST* ast = (Int64AST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_int64, val, builder.getInt64(ast->m_val));
                }
                break;
            case NodeAST::tFloatAST:
                {
                    FloatAST* ast = (FloatAST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_float, val, ConstantFP::get(builder.getFloatTy(), ast->m_val));
                }
                break;
            case NodeAST::tDoubleAST:
                {
                    DoubleAST* ast = (DoubleAST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_double, val, ConstantFP::get(builder.getDoubleTy(), ast->m_val));
                }
                break;
            default:
                {
                    Value* org = m_expr->codeGen(cg);
                    Value* op = builder.getInt32(m_op);
                    val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
                    builder.CreateCall4(cg->m_gf_opUnaryPlusMinusVar, val, org, op, cg->m_gv_vm);
                }
                break;
            }
        }
        break;
    case TOK_MINUS:
        {
            val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
            switch(m_expr->m_type)
            {
            case NodeAST::tInt32AST:
                {
                    Int32AST* ast = (Int32AST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_int32, val, builder.getInt32(-ast->m_val));
                }
                break;
            case NodeAST::tInt64AST:
                {
                    Int64AST* ast = (Int64AST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_int64, val, builder.getInt64(-ast->m_val));
                }
                break;
            case NodeAST::tFloatAST:
                {
                    FloatAST* ast = (FloatAST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_float, val, ConstantFP::get(builder.getFloatTy(), -ast->m_val));
                }
                break;
            case NodeAST::tDoubleAST:
                {
                    DoubleAST* ast = (DoubleAST*)m_expr;
                    builder.CreateCall2(cg->m_gf_opAssignVar_double, val, ConstantFP::get(builder.getDoubleTy(), -ast->m_val));
                }
                break;
            default:
                {
                    Value* org = m_expr->codeGen(cg);
                    Value* op = builder.getInt32(m_op);
                    val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
                    builder.CreateCall4(cg->m_gf_opUnaryPlusMinusVar, val, org, op, cg->m_gv_vm);
                }
                break;
            }
        }
        break;
    case TOK_CAT:
        {
            Value* org = m_expr->codeGen(cg);
            val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
            builder.CreateCall3(cg->m_gf_opBitwiseNotVar, val, org, cg->m_gv_vm);
        }
        break;
    case TOK_NOT:
        {
            Value* org = m_expr->codeGen(cg);
            val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
            builder.CreateCall3(cg->m_gf_opLogicalNotVar, val, org, cg->m_gv_vm);
        }
        break;
    }

    return val;
}

Value* MultiplicativeAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* lhs = m_expr1->codeGen(cg);
    Value* rhs = m_expr2->codeGen(cg);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);

    switch(m_op)
    {
    case TOK_MUL:
        builder.CreateCall4(cg->m_gf_opMulVar, val, lhs, rhs, cg->m_gv_vm);
        break;
    case TOK_DIV:
        builder.CreateCall4(cg->m_gf_opDivVar, val, lhs, rhs, cg->m_gv_vm);
        break;
    case TOK_MOD:
        builder.CreateCall4(cg->m_gf_opModVar, val, lhs, rhs, cg->m_gv_vm);
        break;
    }

    return val;
}

Value* AdditiveAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* lhs = m_expr1->codeGen(cg);
    Value* rhs = m_expr2->codeGen(cg);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);

    switch(m_op)
    {
    case TOK_PLUS:
        builder.CreateCall4(cg->m_gf_opAddVar, val, lhs, rhs, cg->m_gv_vm);
        break;
    case TOK_MINUS:
        builder.CreateCall4(cg->m_gf_opSubVar, val, lhs, rhs, cg->m_gv_vm);
        break;
    }

    return val;
}

Value* ShiftAST::codeGen(acCodeGenerator* cg)
{
    cg->getMsgHandler()->error("Error: ShiftAST not implemented yet QQ");
    cg->setCompileError(true);
    return 0;
}

Value* RelationalAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* lhs = m_expr1->codeGen(cg);
    Value* rhs = m_expr2->codeGen(cg);

    Value* cmp = builder.getInt32(m_op);
    Value* ret = builder.CreateCall4(cg->m_gf_opCompareVar, lhs, rhs, cmp, cg->m_gv_vm);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_bool, val, ret);

    return val;
}

Value* EqualityAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* lhs = m_expr1->codeGen(cg);
    Value* rhs = m_expr2->codeGen(cg);
    Value* ret = 0;
    if(m_op == TOK_EQUAL)
    {
        ret = builder.CreateCall3(cg->m_gf_opEqualVar, lhs, rhs, cg->m_gv_vm);
    }
    else
    {
        ret = builder.CreateCall3(cg->m_gf_opNotEqualVar, lhs, rhs, cg->m_gv_vm);
    }

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall2(cg->m_gf_opAssignVar_bool, val, ret);

    return val;
}

Value* AndAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val1 = m_expr1->codeGen(cg);
    Value* val2 = m_expr2->codeGen(cg);
    Value* op = builder.getInt32(TOK_AND);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall5(cg->m_gf_opBitwiseAndOrXorVar, val, val1, val2, op, cg->m_gv_vm);

    return val;
}

Value* ExclusiveOrAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val1 = m_expr1->codeGen(cg);
    Value* val2 = m_expr2->codeGen(cg);
    Value* op = builder.getInt32(TOK_XOR);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall5(cg->m_gf_opBitwiseAndOrXorVar, val, val1, val2, op, cg->m_gv_vm);

    return val;
}

Value* InclusiveOrAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val1 = m_expr1->codeGen(cg);
    Value* val2 = m_expr2->codeGen(cg);
    Value* op = builder.getInt32(TOK_OR);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall5(cg->m_gf_opBitwiseAndOrXorVar, val, val1, val2, op, cg->m_gv_vm);

    return val;
}

Value* LogicalAndAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val1 = m_expr1->codeGen(cg);
    Value* val2 = m_expr2->codeGen(cg);
    Value* op = builder.getInt32(TOK_ANDAND);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall5(cg->m_gf_opLogicalAndOrVar, val, val1, val2, op, cg->m_gv_vm);

    return val;
}

Value* LogicalOrAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val1 = m_expr1->codeGen(cg);
    Value* val2 = m_expr2->codeGen(cg);
    Value* op = builder.getInt32(TOK_OROR);

    Value* val = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    builder.CreateCall5(cg->m_gf_opLogicalAndOrVar, val, val1, val2, op, cg->m_gv_vm);

    return val;
}

Value* ConditionalAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* condVar = m_operand1->codeGen(cg);
    Value* boolValue = builder.CreateCall2(cg->m_gf_opToBoolVar, condVar, cg->m_gv_vm);
    Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");

    Value* trueVar = m_operand2->codeGen(cg);
    Value* falseVar = m_operand3->codeGen(cg);

    return builder.CreateSelect(cond, trueVar, falseVar);
}

Value* AssignmentAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* val = m_expr1->codeGen(cg);

    if(m_op == TOK_ASSIGN)
    {
        codeGenAssignment(builder, val, m_expr2, cg);
        return val;
    }

    Value* rhs = m_expr2->codeGen(cg);
    switch(m_op)
    {
    case TOK_DIVASS:
        builder.CreateCall4(cg->m_gf_opDivVar, val, val, rhs, cg->m_gv_vm);
        break;
    case TOK_ANDASS:
        cg->getMsgHandler()->error("Error: TOK_ANDASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    case TOK_ORASS:
        cg->getMsgHandler()->error("Error: TOK_ORASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    case TOK_MINUSASS:
        builder.CreateCall4(cg->m_gf_opSubVar, val, val, rhs, cg->m_gv_vm);
        break;
    case TOK_PLUSASS:
        builder.CreateCall4(cg->m_gf_opAddVar, val, val, rhs, cg->m_gv_vm);
        break;
    case TOK_SHLASS:
        cg->getMsgHandler()->error("Error: TOK_SHLASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    case TOK_SHRASS:
        cg->getMsgHandler()->error("Error: TOK_SHRASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    case TOK_USHRASS:
        cg->getMsgHandler()->error("Error: TOK_USHRASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    case TOK_MULASS:
        builder.CreateCall4(cg->m_gf_opMulVar, val, val, rhs, cg->m_gv_vm);
        break;
    case TOK_MODASS:
        builder.CreateCall4(cg->m_gf_opModVar, val, val, rhs, cg->m_gv_vm);
        break;
    case TOK_XORASS:
        cg->getMsgHandler()->error("Error: TOK_XORASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    case TOK_CATASS:
        cg->getMsgHandler()->error("Error: TOK_CATASS not implemented yet QQ");
        cg->setCompileError(true);
        return 0;
    }

    return val;
}

Value* IfElseAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    LLVMContext& context = cg->getLLVMContext();
    Function* function = block->m_bblock->getParent();

    Value* condVar = m_cond->codeGen(cg);
    Value* boolValue = builder.CreateCall2(cg->m_gf_opToBoolVar, condVar, cg->m_gv_vm);
    Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");

    BasicBlock* label_if_then = BasicBlock::Create(context, "if.then", function, block->m_leave);

    if(m_elseStmt != 0)
    {
        BasicBlock* label_if_else = BasicBlock::Create(context, "if.else", function, block->m_leave);
        BasicBlock* label_if_end = BasicBlock::Create(context, "if.end", function, block->m_leave);

        builder.CreateCondBr(cond, label_if_then, label_if_else);
        builder.SetInsertPoint(label_if_then);
        
        if(m_thenStmt != 0)
        {
            cg->pushBlock(label_if_then, label_if_else, this, acCodeGenBlock::IF_THEN,
                block->m_retVar, block->m_thisVar, block->m_argArray,
                block->m_tmpArray, block->m_tmpArraySize,
                block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
            m_thenStmt->codeGen(cg);
            cg->popBlock();
        }

        if(builder.GetInsertBlock()->getTerminator() == 0)
            builder.CreateBr(label_if_end);
        builder.SetInsertPoint(label_if_else);

        cg->pushBlock(label_if_else, label_if_end, this, acCodeGenBlock::IF_ELSE,
            block->m_retVar, block->m_thisVar, block->m_argArray,
            block->m_tmpArray, block->m_tmpArraySize,
            block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
        m_elseStmt->codeGen(cg);
        cg->popBlock();

        if(builder.GetInsertBlock()->getTerminator() == 0)
            builder.CreateBr(label_if_end);
        builder.SetInsertPoint(label_if_end);
    }
    else
    {
        BasicBlock* label_if_end = BasicBlock::Create(context, "if.end", function, block->m_leave);

        builder.CreateCondBr(cond, label_if_then, label_if_end);
        builder.SetInsertPoint(label_if_then);

        if(m_thenStmt != 0)
        {
            cg->pushBlock(label_if_then, label_if_end, this, acCodeGenBlock::IF_THEN,
                block->m_retVar, block->m_thisVar, block->m_argArray,
                block->m_tmpArray, block->m_tmpArraySize,
                block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
            m_thenStmt->codeGen(cg);
            cg->popBlock();
        }

        if(builder.GetInsertBlock()->getTerminator() == 0)
            builder.CreateBr(label_if_end);
        builder.SetInsertPoint(label_if_end);
    }

    return 0;
}

Value* SwitchAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    LLVMContext& context = cg->getLLVMContext();
    Function* function = block->m_bblock->getParent();

    BasicBlock* label_switch_begin = BasicBlock::Create(context, "switch.begin", function, block->m_leave);
    BasicBlock* label_switch_default = BasicBlock::Create(context, "switch.case.default", function, block->m_leave);
    BasicBlock* label_switch_end = BasicBlock::Create(context, "switch.end", function, block->m_leave);

    CaseAST* defaultAst = 0;
    BasicBlock* label_default_block = 0;

    //create label
    NodeASTVec::iterator it = m_labeledStmts->m_nodeASTVec.begin();
    int count = m_labeledStmts->m_nodeASTVec.size();
    for(int idx = 0; idx < count; ++idx, ++it)
    {
        CaseAST* ast = (CaseAST*)*it;
        Twine caseidx = Twine(idx).concat("_");
        if(ast->m_expr != 0)//case
        {
            ast->m_swcase = BasicBlock::Create(context, Twine("sw.case.").concat(caseidx), function, label_switch_default);
            ast->m_swblock = BasicBlock::Create(context, Twine("sw.block.").concat(caseidx), function, label_switch_end);
        }
        else//default
        {
            defaultAst = ast;
            ast->m_swcase = label_switch_default;
            ast->m_swblock = BasicBlock::Create(context, Twine("sw.block.default"), function, label_switch_end);
            label_default_block = ast->m_swblock;
        }
    }
    if(defaultAst == 0)//no default
    {
        label_default_block = BasicBlock::Create(context, Twine("sw.block.default"), function, label_switch_end);
    }
    
    builder.CreateBr(label_switch_begin);
    builder.SetInsertPoint(label_switch_begin);

    //codegen
    Value* condVar = m_cond->codeGen(cg);

    cg->pushBlock(label_switch_begin, label_switch_end, this, acCodeGenBlock::SWITCH, 
        block->m_retVar, block->m_thisVar, block->m_argArray,
        block->m_tmpArray, block->m_tmpArraySize,
        block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
    block = cg->currentBlock();

    it = m_labeledStmts->m_nodeASTVec.begin();
    for(int idx = 0; idx < count; ++idx, ++it)
    {
        CaseAST* ast = (CaseAST*)*it;
        BasicBlock* swblock = 0;

        if(idx == 0)
        {
            builder.CreateBr(ast->m_swcase);
        }
        builder.SetInsertPoint(ast->m_swcase);

        if(ast->m_expr != 0)//case
        {
            //codegen for case-label
            Value* caseVar = builder.CreateCall3(cg->m_gf_getArrayVar_int,
                block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
            codeGenAssignment(builder, caseVar, ast->m_expr, cg);

            Value* boolValue = builder.CreateCall3(cg->m_gf_opEqualVar, condVar, caseVar, cg->m_gv_vm);
            Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");

            builder.CreateCondBr(cond, ast->m_swblock, ast->m_swcase->getNextNode());

            //codegen for case-block
            builder.SetInsertPoint(ast->m_swblock);
            swblock = ast->m_swblock;
        }
        else//default
        {
            builder.CreateBr(label_default_block);

            //codegen for default-block
            builder.SetInsertPoint(label_default_block);
            swblock = label_default_block;
        }

        BasicBlock* nextBlock = swblock->getNextNode();
        //codegen for stmts
        if(ast->m_stmts != 0)
        {
            cg->pushBlock(swblock, nextBlock, this, acCodeGenBlock::CODE, 
                block->m_retVar, block->m_thisVar, block->m_argArray,
                block->m_tmpArray, block->m_tmpArraySize,
                block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
            ast->m_stmts->codeGen(cg);
            cg->popBlock();
        }

        if(builder.GetInsertBlock()->getTerminator() == 0)
            builder.CreateBr(nextBlock);
    }

    if(defaultAst == 0)//no default
    {
        builder.SetInsertPoint(label_switch_default);
        builder.CreateBr(label_default_block);

        builder.SetInsertPoint(label_default_block);
        builder.CreateBr(label_switch_end);
    }

    cg->popBlock();
    builder.SetInsertPoint(label_switch_end);

    return 0;
}

Value* CaseAST::codeGen(acCodeGenerator* cg)
{
    return 0;
}

Value* BreakAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->findWhereIsBreak();

    if(block == 0)
    {
        cg->getMsgHandler()->error("Error: 'break' statement not in loop or switch statement");
        cg->setCompileError(true);
        return 0;
    }
    
    IRBuilder<>& builder = cg->getIRBuilder();
    builder.CreateBr(block->m_leave);

    cg->currentBlock()->m_isBlockEnd = true;

    return 0;
}

Value* ContinueAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->findWhereIsContinue();

    if(block == 0)
    {
        cg->getMsgHandler()->error("Error: 'continue' statement not in loop statement");
        cg->setCompileError(true);
        return 0;
    }

    IRBuilder<>& builder = cg->getIRBuilder();

    switch(block->m_type)
    {
    case acCodeGenBlock::WHILE:
        {
            WhileAST* ast = (WhileAST*)block->m_ast;
            builder.CreateBr(ast->m_condblock);
        }
        break;
    case acCodeGenBlock::DOWHILE:
        {
            DoWhileAST* ast = (DoWhileAST*)block->m_ast;
            builder.CreateBr(ast->m_condblock);
        }
        break;
    case acCodeGenBlock::FOR:
        {
            ForAST* ast = (ForAST*)block->m_ast;
            builder.CreateBr(ast->m_incblock);
        }
        break;
    case acCodeGenBlock::FOREACH:
        {
            ForeachAST* ast = (ForeachAST*)block->m_ast;
            builder.CreateBr(ast->m_condblock);
        }
        break;
    }

    return 0;
}

Value* WhileAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    LLVMContext& context = cg->getLLVMContext();
    Function* function = block->m_bblock->getParent();

    BasicBlock* label_while_cond = BasicBlock::Create(context, "while.cond", function, block->m_leave);
    BasicBlock* label_while_loop = BasicBlock::Create(context, "while.loop", function, block->m_leave);
    BasicBlock* label_while_end = BasicBlock::Create(context, "while.end", function, block->m_leave);

    m_condblock = label_while_cond;

    builder.CreateBr(label_while_cond);
    builder.SetInsertPoint(label_while_cond);

    //codegen for condition
    Value* condVar = m_cond->codeGen(cg);
    Value* boolValue = builder.CreateCall2(cg->m_gf_opToBoolVar, condVar, cg->m_gv_vm);
    Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");

    builder.CreateCondBr(cond, label_while_loop, label_while_end);
    builder.SetInsertPoint(label_while_loop);

    if(m_stmt != 0)
    {
        cg->pushBlock(label_while_loop, label_while_end, this, acCodeGenBlock::WHILE,
            block->m_retVar, block->m_thisVar, block->m_argArray,
            block->m_tmpArray, block->m_tmpArraySize,
            block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
        m_stmt->codeGen(cg);
        cg->popBlock();
    }

    if(builder.GetInsertBlock()->getTerminator() == 0)
        builder.CreateBr(label_while_cond);

    builder.SetInsertPoint(label_while_end);

    return 0;
}

Value* DoWhileAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    LLVMContext& context = cg->getLLVMContext();
    Function* function = block->m_bblock->getParent();

    BasicBlock* label_dowhile_loop = BasicBlock::Create(context, "dowhile.loop", function, block->m_leave);
    BasicBlock* label_dowhile_cond = BasicBlock::Create(context, "dowhile.cond", function, block->m_leave);
    BasicBlock* label_dowhile_end = BasicBlock::Create(context, "dowhile.end", function, block->m_leave);

    m_condblock = label_dowhile_cond;

    builder.CreateBr(label_dowhile_loop);
    builder.SetInsertPoint(label_dowhile_loop);

    if(m_stmt != 0)
    {
        cg->pushBlock(label_dowhile_loop, label_dowhile_end, this, acCodeGenBlock::WHILE,
            block->m_retVar, block->m_thisVar, block->m_argArray,
            block->m_tmpArray, block->m_tmpArraySize,
            block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
        m_stmt->codeGen(cg);
        cg->popBlock();
    }

    if(builder.GetInsertBlock()->getTerminator() == 0)
        builder.CreateBr(label_dowhile_cond);

    builder.SetInsertPoint(label_dowhile_cond);

    //codegen for condition
    Value* condVar = m_cond->codeGen(cg);
    Value* boolValue = builder.CreateCall2(cg->m_gf_opToBoolVar, condVar, cg->m_gv_vm);
    Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");

    builder.CreateCondBr(cond, label_dowhile_loop, label_dowhile_end);
    builder.SetInsertPoint(label_dowhile_end);

    return 0;
}

Value* ForAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    LLVMContext& context = cg->getLLVMContext();
    Function* function = block->m_bblock->getParent();

    BasicBlock* label_for_init = BasicBlock::Create(context, "for.init", function, block->m_leave);
    BasicBlock* label_for_cond = BasicBlock::Create(context, "for.cond", function, block->m_leave);
    BasicBlock* label_for_loop = BasicBlock::Create(context, "for.loop", function, block->m_leave);
    BasicBlock* label_for_inc = BasicBlock::Create(context, "for.inc", function, block->m_leave);
    BasicBlock* label_for_end = BasicBlock::Create(context, "for.end", function, block->m_leave);

    m_incblock = label_for_inc;

    cg->pushBlock(label_for_init, label_for_end, this, acCodeGenBlock::FOR,
        block->m_retVar, block->m_thisVar, block->m_argArray,
        block->m_tmpArray, block->m_tmpArraySize,
        block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
    block = cg->currentBlock();

    //init
    builder.CreateBr(label_for_init);
    builder.SetInsertPoint(label_for_init);
    if(m_init != 0)
    {
        m_init->codeGen(cg);
    }

    //cond
    builder.CreateBr(label_for_cond);
    builder.SetInsertPoint(label_for_cond);

    if(m_cond != 0)
    {
        Value* condVar = m_cond->codeGen(cg);
        Value* boolValue = builder.CreateCall2(cg->m_gf_opToBoolVar, condVar, cg->m_gv_vm);
        Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");

        builder.CreateCondBr(cond, label_for_loop, label_for_end);
    }
    else
    {
        builder.CreateBr(label_for_loop);
    }

    builder.SetInsertPoint(label_for_loop);

    //loop
    if(m_stmt != 0)
    {
        cg->pushBlock(label_for_loop, label_for_inc, this, acCodeGenBlock::CODE,
            block->m_retVar, block->m_thisVar, block->m_argArray,
            block->m_tmpArray, block->m_tmpArraySize,
            block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
        m_stmt->codeGen(cg);
        cg->popBlock();
    }

    if(builder.GetInsertBlock()->getTerminator() == 0)
        builder.CreateBr(label_for_inc);

    builder.SetInsertPoint(label_for_inc);
    if(m_inc != 0)
        m_inc->codeGen(cg);
    builder.CreateBr(label_for_cond);

    builder.SetInsertPoint(label_for_end);

    cg->popBlock();

    return 0;
}

Value* ForeachAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    LLVMContext& context = cg->getLLVMContext();
    Function* function = block->m_bblock->getParent();

    BasicBlock* label_foreach_init = BasicBlock::Create(context, "foreach.init", function, block->m_leave);
    BasicBlock* label_foreach_cond = BasicBlock::Create(context, "foreach.cond", function, block->m_leave);
    BasicBlock* label_foreach_loop = BasicBlock::Create(context, "foreach.loop", function, block->m_leave);
    BasicBlock* label_foreach_end = BasicBlock::Create(context, "foreach.end", function, block->m_leave);

    m_condblock = label_foreach_cond;

    cg->pushBlock(label_foreach_init, label_foreach_end, this, acCodeGenBlock::FOREACH,
        block->m_retVar, block->m_thisVar, block->m_argArray,
        block->m_tmpArray, block->m_tmpArraySize,
        block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
    block = cg->currentBlock();

    //init
    builder.CreateBr(label_foreach_init);
    builder.SetInsertPoint(label_foreach_init);

    Value* keyVal = 0;
    Value* valueVal = 0;
    Value* containerVal = 0;

    if(m_var1 == 0)
    {
        keyVal = ConstantPointerNull::get(builder.getInt8PtrTy());
    }
    switch(m_declTok)
    {
    case TOK_VAR:
        {
            if(m_var1 != 0)
            {
                keyVal = codeGenVarDecl(builder, m_var1, false, cg);
            }
            valueVal = codeGenVarDecl(builder, m_var2, false, cg);
        }
        break;
    case TOK_LOCAL:
        {
            if(m_var1 != 0)
            {
                keyVal = codeGenVarDecl(builder, m_var1, true, cg);
                block->m_localVars.push_back(std::make_pair(m_var1->m_keyIdentifier, keyVal));
            }
            valueVal = codeGenVarDecl(builder, m_var2, true, cg);
            block->m_localVars.push_back(std::make_pair(m_var2->m_keyIdentifier, valueVal));
        }
        break;
    default:
        {
            if(m_var1 != 0)
            {
                keyVal = m_var1->codeGen(cg);
            }
            valueVal = m_var2->codeGen(cg);
        }
        break;
    }

    containerVal = m_container->codeGen(cg);
    builder.CreateCall2(cg->m_gf_opInitIter, containerVal, cg->m_gv_vm);

    //cond
    builder.CreateBr(label_foreach_cond);
    builder.SetInsertPoint(label_foreach_cond);

    Value* boolValue = builder.CreateCall4(cg->m_gf_opIterateVar, containerVal, keyVal, valueVal, cg->m_gv_vm);
    Value* cond = builder.CreateCast(Instruction::Trunc, boolValue, builder.getInt1Ty(), "IsNotZero");
    builder.CreateCondBr(cond, label_foreach_loop, label_foreach_end);

    builder.SetInsertPoint(label_foreach_loop);

    //loop
    if(m_stmt != 0)
    {
        cg->pushBlock(label_foreach_loop, label_foreach_end, this, acCodeGenBlock::CODE,
            block->m_retVar, block->m_thisVar, block->m_argArray,
            block->m_tmpArray, block->m_tmpArraySize,
            block->m_stringList, block->m_funcDataList, block->m_debugInfoList);
        m_stmt->codeGen(cg);
        cg->popBlock();
    }

    if(builder.GetInsertBlock()->getTerminator() == 0)
        builder.CreateBr(label_foreach_cond);

    //end
    builder.SetInsertPoint(label_foreach_end);

    cg->popBlock();

    return 0;
}

Value* NamespaceAST::codeGen(acCodeGenerator* cg)
{
    return 0;
}

Value* NewAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();

    Value* orgVar = m_varExpr->codeGen(cg);

    Value* tmpVar = builder.CreateCall3(cg->m_gf_getArrayVar_int,
        block->m_tmpArray, builder.getInt32(block->m_tmpArraySize++), cg->m_gv_vm);
    Value* argArray = builder.CreateCall2(cg->m_gf_createArray, tmpVar, cg->m_gv_vm, Twine("v_argArray"));

    //push args
    if(m_args != 0)
    {
        NodeASTVec::iterator it = m_args->m_nodeASTVec.begin();
        NodeASTVec::iterator itend = m_args->m_nodeASTVec.end();
        for(; it != itend; ++it)
        {
            Value* arg = builder.CreateCall3(cg->m_gf_newArrayVar, argArray, builder.getInt32(-1), cg->m_gv_vm);
            codeGenAssignment(builder, arg, *it, cg);
        }
    }

    //call opNew
    return builder.CreateCall3(cg->m_gf_opNew, orgVar, argArray, cg->m_gv_vm, Twine("v_new_var"));
}

inline Value* codeGenDelete(IRBuilder<>& builder, Value* parent, NodeAST* keyExpr, int findInGlobal, acCodeGenerator* cg)
{
    switch(keyExpr->m_type)
    {
    case NodeAST::tInt32AST:
        {
            Int32AST* ast = (Int32AST*)keyExpr;
            return builder.CreateCall4(cg->m_gf_opDelete_int32, parent, builder.getInt32(ast->m_val), builder.getInt32(findInGlobal), cg->m_gv_vm);
        }
        break;
    case NodeAST::tInt64AST:
        {
            Int64AST* ast = (Int64AST*)keyExpr;
            return builder.CreateCall4(cg->m_gf_opDelete_int64, parent, builder.getInt64(ast->m_val), builder.getInt32(findInGlobal), cg->m_gv_vm);
        }
        break;
    case NodeAST::tStringAST:
        {
            StringAST* ast = (StringAST*)keyExpr;
            return builder.CreateCall4(cg->m_gf_opDelete_str,
                parent,
                cg->createStringPtr(ast->m_val, cg->currentBlock(), builder),
                builder.getInt32(findInGlobal),
                cg->m_gv_vm);
        }
        break;
    }

    Value* key = keyExpr->codeGen(cg);
    return builder.CreateCall4(cg->m_gf_opDelete, parent, key, builder.getInt32(findInGlobal), cg->m_gv_vm);
}

Value* DeleteAST::codeGen(acCodeGenerator* cg)
{
    acCodeGenBlock* block = cg->currentBlock();
    IRBuilder<>& builder = cg->getIRBuilder();
    Value* val = 0;

    ConstantInt* zero = builder.getInt32(0);

    if(m_varExpr->m_parentExpr != 0)
    {
        m_varExpr->m_parent = m_varExpr->m_parentExpr->codeGen(cg);

        if(m_varExpr->m_keyExpr != 0)
        {
            val = codeGenDelete(builder, m_varExpr->m_parent, m_varExpr->m_keyExpr, 0, cg);
        }
        else
        {
            val = builder.CreateCall4(cg->m_gf_opDelete_str,
                m_varExpr->m_parent,
                cg->createStringPtr(m_varExpr->m_keyIdentifier, block, builder),
                zero,
                cg->m_gv_vm);
        }
    }
    else
    {
        switch(m_varExpr->m_scope)
        {
        case GetVarAST::NONE:
            if(m_varExpr->m_keyExpr != 0)
            {
                val = codeGenDelete(builder, block->m_thisVar, m_varExpr->m_keyExpr, 1, cg);
            }
            else
            {
                //find in localvar first
                val = cg->findLocalVar(m_varExpr->m_keyIdentifier);

                if(val != 0)
                {
                    cg->getMsgHandler()->error("Error: cannot delete a local variable");
                    cg->setCompileError(true);
                    return 0;
                }

                //then find in this & global table
                val = builder.CreateCall4(cg->m_gf_opDelete_str,
                    block->m_thisVar,
                    cg->createStringPtr(m_varExpr->m_keyIdentifier, block, builder),
                    builder.getInt32(1),
                    cg->m_gv_vm);
            }
            break;
        case GetVarAST::THIS:
            if(m_varExpr->m_keyExpr != 0)
            {
                val = codeGenDelete(builder, block->m_thisVar, m_varExpr->m_keyExpr, 0, cg);
            }
            else
            {
                val = builder.CreateCall4(cg->m_gf_opGetVar_str,
                    block->m_thisVar,
                    cg->createStringPtr(m_varExpr->m_keyIdentifier, block, builder),
                    zero,
                    cg->m_gv_vm);
            }
            break;
        case GetVarAST::GLOBAL:
            if(m_varExpr->m_keyExpr != 0)
            {
                val = codeGenDelete(builder, cg->m_gv_rootTableVar, m_varExpr->m_keyExpr, 0, cg);
            }
            else
            {
                val = builder.CreateCall4(cg->m_gf_opGetVar_str,
                    cg->m_gv_rootTableVar,
                    cg->createStringPtr(m_varExpr->m_keyIdentifier, block, builder),
                    zero,
                    cg->m_gv_vm);
            }
            break;
        }
    }

    return val;
}

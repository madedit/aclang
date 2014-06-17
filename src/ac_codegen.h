/* see copyright notice in aclang.h */

#ifndef AC_CODEGEN_H
#define AC_CODEGEN_H

#include "ac_config.h"
#include "ac_ast.h"
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <list>
#include <setjmp.h>

using namespace llvm;
class acVM;
class acMsgHandler;
class acGarbageCollector;
struct acArray;
struct acTable;
struct acVariable;

struct acCodeGenBlock
{
    BasicBlock* m_bblock;
    BasicBlock* m_leave;
    NodeAST* m_ast;
    enum BlockType
    {
        CODE,
        IF_THEN,
        IF_ELSE,
        SWITCH,
        WHILE,
        DOWHILE,
        FOR,
        FOREACH,
        FUNCTION,
        TABLE,
        NAMESPACE,
    };
    BlockType m_type;
    Value* m_retVar;
    Value* m_thisVar;
    Value* m_argArray;
    Value* m_tmpArray;
    int m_tmpArraySize;
    std::list<std::pair<std::string, Value*> > m_localVars;
    bool m_isBlockEnd;
};

class acCodeGenerator
{
    friend class acVM;
protected:
    acVM* m_vm;
    acMsgHandler* m_msgHandler;
    acGarbageCollector* m_gc;
    BlockAST* m_programBlockAST;
    llvm::Function* m_mainFunction;
    IRBuilder<> m_irBuilder;

    //for error handling at runtime
    jmp_buf m_errorJmpBuf;

    //root variables
    acTable* m_rootTable;
    acVariable* m_rootTableVar;
    acArray* m_rootArgArray;
    acArray* m_rootTmpArray;
    acVariable* m_userFuncRetVar;

    std::list<acCodeGenBlock*> m_blocks;

    //for error handling at compile-time
    bool m_isCompileError;

public:
    //global values in vm
    GlobalVariable* m_gv_vm;
    GlobalVariable* m_gv_cg;
    GlobalVariable* m_gv_gc;
    GlobalVariable* m_gv_errorJmpBuf;
    GlobalVariable* m_gv_rootTableVar;
    GlobalVariable* m_gv_rootArgArray;
    GlobalVariable* m_gv_rootTmpArray;
    //global functions in vm
    Function* m_gf_setJmp;
    Function* m_gf_longJmp;
    Function* m_gf_newArrayVar;
    Function* m_gf_setArrayVar;
    Function* m_gf_getArrayVar;
    Function* m_gf_getArrayVar_int;
    Function* m_gf_addTableKeyValue;
    Function* m_gf_addTableKeyValue_str;
    Function* m_gf_addTableVar;
    Function* m_gf_addTableVar_str;
    Function* m_gf_getTableVar;
    Function* m_gf_createUpValueTable;
    Function* m_gf_createFunc;
    Function* m_gf_setFuncPtr;
    Function* m_gf_createTmpArray;
    Function* m_gf_createTable;
    Function* m_gf_createArray;
    Function* m_gf_opGetVar;
    Function* m_gf_opGetVar_int;
    Function* m_gf_opGetVar_str;
    Function* m_gf_opNewVar;
    Function* m_gf_opNewVar_int;
    Function* m_gf_opNewVar_str;
    Function* m_gf_opAssignVar;
    Function* m_gf_opAssignVar_null;
    Function* m_gf_opAssignVar_bool;
    Function* m_gf_opAssignVar_int32;
    Function* m_gf_opAssignVar_int64;
    Function* m_gf_opAssignVar_float;
    Function* m_gf_opAssignVar_double;
    Function* m_gf_opAssignVar_str;
    Function* m_gf_opAddVar;
    Function* m_gf_opSubVar;
    Function* m_gf_opMulVar;
    Function* m_gf_opDivVar;
    Function* m_gf_opModVar;
    Function* m_gf_opCallFunc;
    Function* m_gf_opEqualVar;
    Function* m_gf_opNotEqualVar;
    Function* m_gf_opCompareVar;
    Function* m_gf_opPostfixIncDecVar;
    Function* m_gf_opPrefixIncDecVar;
    Function* m_gf_opUnaryPlusMinusVar;
    Function* m_gf_opLogicalNotVar;
    Function* m_gf_opLogicalAndOrVar;
    Function* m_gf_opBitwiseNotVar;
    Function* m_gf_opBitwiseAndOrXorVar;
    Function* m_gf_opToBoolVar;
    Function* m_gf_opInitIter;
    Function* m_gf_opIterateVar;

public:
    acCodeGenerator(acVM* vm);
    ~acCodeGenerator();

    acVM* getVM() { return m_vm; }
    acMsgHandler* getMsgHandler() { return m_msgHandler; }
    acGarbageCollector* getGarbageCollector();
    llvm::LLVMContext& getLLVMContext();
    llvm::Module* getModule();
    IRBuilder<>& getIRBuilder() { return m_irBuilder; }

    acTable* getRootTable() { return m_rootTable; }

    void setProgramBlockAST(BlockAST* block) { m_programBlockAST = block; }
    BlockAST* getProgramBlockAST() { return m_programBlockAST; }

    void generateCode();
    llvm::GenericValue runCode();

    acCodeGenBlock* currentBlock() { return m_blocks.front(); }
    void pushBlock(BasicBlock* bblock, BasicBlock* leave, NodeAST* ast, acCodeGenBlock::BlockType type,
                   Value* retVar, Value* thisVar, Value* argArray, Value* tmpArray, int tmpArraySize);
    void popBlock();
    Value* findLocalVar(const std::string& name);
    acCodeGenBlock* findWhereIsBreak();
    acCodeGenBlock* findWhereIsContinue();

    void setCompileError(bool v) { m_isCompileError = v; }
    bool isCompileError() { return m_isCompileError; }
    jmp_buf* getErrorJmpBuf() { return &m_errorJmpBuf; }

protected:
    void llvm_fatal_error_handler(void *user_data, const std::string &reason, bool gen_crash_diag);
    void createCoreFunctions();
    void createGlobalValues();
    void createGlobalFunctions();
};


#endif //AC_CODEGEN_H

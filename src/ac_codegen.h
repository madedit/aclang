/* see copyright notice in aclang.h */

#ifndef AC_CODEGEN_H
#define AC_CODEGEN_H

#include "ac_config.h"
#include "ac_ast.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <list>
#include <vector>
#include <setjmp.h>

using namespace llvm;
class acVM;
class acMsgHandler;
class acGarbageCollector;
struct acGCObject;
struct acArray;
struct acTable;
struct acVariable;

struct acDebugInfo
{
    const char* file;
    int line;
};

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
    std::list<std::string>* m_stringList;
    std::list<acGCObject*>* m_funcDataList;
    std::list<acDebugInfo>* m_debugInfoList;
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
    std::list<std::string> m_stringList;
    std::list<acGCObject*> m_funcDataList;
    std::list<acDebugInfo> m_debugInfoList;

    std::list<acCodeGenBlock*> m_blocks;

    StringMap<void*> m_globalSymbalMap;

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
    Function* m_gf_assignFunc;
    Function* m_gf_setFuncPtr;
    Function* m_gf_setFuncMiscData;
    Function* m_gf_createTmpArray;
    Function* m_gf_createTable;
    Function* m_gf_createArray;
    Function* m_gf_opGetVar;
    Function* m_gf_opGetVar_int32;
    Function* m_gf_opGetVar_int64;
    Function* m_gf_opGetVar_str;
    Function* m_gf_opNewVar;
    Function* m_gf_opNewVar_int32;
    Function* m_gf_opNewVar_int64;
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
    Function* m_gf_opPostfixIncVar;
    Function* m_gf_opPostfixDecVar;
    Function* m_gf_opPrefixIncVar;
    Function* m_gf_opPrefixDecVar;
    Function* m_gf_opUnaryPlusVar;
    Function* m_gf_opUnaryMinusVar;
    Function* m_gf_opLogicalNotVar;
    Function* m_gf_opLogicalAndVar;
    Function* m_gf_opLogicalOrVar;
    Function* m_gf_opBitwiseNotVar;
    Function* m_gf_opBitwiseAndVar;
    Function* m_gf_opBitwiseOrVar;
    Function* m_gf_opBitwiseXorVar;
    Function* m_gf_opToBoolVar;
    Function* m_gf_opInitIter;
    Function* m_gf_opIterateVar;
    Function* m_gf_opNew;
    Function* m_gf_opDelete;
    Function* m_gf_opDelete_int32;
    Function* m_gf_opDelete_int64;
    Function* m_gf_opDelete_str;

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
    acVariable* getRootTableVar() { return m_rootTableVar; }

    void setProgramBlockAST(BlockAST* block) { m_programBlockAST = block; }
    BlockAST* getProgramBlockAST() { return m_programBlockAST; }

    void generateCode();
    llvm::GenericValue runCode();

    acCodeGenBlock* currentBlock() { return m_blocks.front(); }
    void pushBlock(BasicBlock* bblock, BasicBlock* leave,
                   NodeAST* ast, acCodeGenBlock::BlockType type,
                   Value* retVar, Value* thisVar, Value* argArray,
                   Value* tmpArray, int tmpArraySize,
                   std::list<std::string>* strList, std::list<acGCObject*>* funcList,
                   std::list<acDebugInfo>* debugInfoList);
    void popBlock();
    Value* findLocalVar(const std::string& name);
    acCodeGenBlock* findWhereIsBreak();
    acCodeGenBlock* findWhereIsContinue();

    Value* createStringPtr(const std::string& str, acCodeGenBlock* block, IRBuilder<>& builder);
    Value* createDebugInfoPtr(int line, acCodeGenBlock* block, IRBuilder<>& builder);
    Value* createDebugInfoPtr(const char* file, int line, acCodeGenBlock* block, IRBuilder<>& builder);

    void setCompileError(bool v) { m_isCompileError = v; }
    bool isCompileError() { return m_isCompileError; }
    jmp_buf* getErrorJmpBuf() { return &m_errorJmpBuf; }

    void* getGlobalSymbolAddress(const std::string &name);

    void createCoreFunctions();

protected:
    void llvm_fatal_error_handler(void *user_data, const std::string &reason, bool gen_crash_diag);
    void eraseMainFunction();
    
    void createGlobalValues();
    void createGlobalFunctions();
    void addGlobalSymbal(ExecutionEngine *ee, const GlobalValue *gv, void *addr);
};


#endif //AC_CODEGEN_H

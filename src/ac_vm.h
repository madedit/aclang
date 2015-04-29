/* see copyright notice in aclang.h */

#ifndef AC_VM_H
#define AC_VM_H

#include "ac_codegen.h"
#include "ac_gc.h"
#include "ac_msghandler.h"
#include "ac_parser.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

class acVM
{
protected:
    bool m_initOkay;

    llvm::LLVMContext m_llvmContext;

    //current module
    llvm::Module* m_module;
    llvm::ExecutionEngine* m_executionEngine;
    //finalized module
    //std::list< std::pair< llvm::ExecutionEngine*, llvm::Module* > > m_executionEngineList;
    std::map<llvm::Module*, llvm::ExecutionEngine*> m_moduleEngineMap;

    acMsgHandler m_msgHandler;
    acParser* m_parser;
    acCodeGenerator* m_codeGenerator;
    acGarbageCollector m_gc;
    bool m_isRuntimeError;
    acDebugInfo* m_debugInfo;

    //for debug
    bool m_printAST;
    bool m_printIR;

public:
    acVM();
    ~acVM();

    bool getInitOkay() { return m_initOkay; }

    llvm::LLVMContext& getLLVMContext() { return m_llvmContext; }

    llvm::Module* getCurrentModule() { return m_module; }
    llvm::ExecutionEngine* getCurrentExecutionEngine() { return m_executionEngine; }
    llvm::ExecutionEngine* getExecutionEngine(llvm::Module* mod);

    void storeCurrentModuleEngine();
    void createNewModuleEngine();

    acMsgHandler* getMsgHandler() { return &m_msgHandler; }
    acParser* getParser() { return m_parser; }
    acCodeGenerator* getCodeGenerator() { return m_codeGenerator; }
    acGarbageCollector* getGarbageCollector() { return &m_gc; }
    void setDebugInfo(acDebugInfo* debugInfo) { m_debugInfo = debugInfo; }
    void runtimeError(const char* errMsg);

    typedef void(*AC_FUNCTION)(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm);
    void bindFunction(const std::string& name, AC_FUNCTION func);
    //void callFunction(const std::string& name, std::vector<GenericValue> noargs);

    //helper function for creating acVariable objects
    acVariable* createString(const char* str);

    //for debug
    void setPrintAST(bool b) { m_printAST = b; }
    bool getPrintAST() { return m_printAST; }
    void setPrintIR(bool b) { m_printIR = b; }
    bool getPrintIR() { return m_printIR; }
    void setPrintGC(bool b) { m_gc.setPrintGC(b); }
    bool getPrintGC() { return m_gc.getPrintGC(); }

public:
    //compile & run Code
    bool runCode(const char* code, bool runGCFinally = true);

    //get roottable
    acVariable* getRootTable() { return m_codeGenerator->getRootTableVar(); }
    //key: "a.b.123"; return ::a[b][123] or NULL if there is any key that is not exist.
    acVariable* getItemInRootTable(const std::string& keys);
    //key: "a.b.123"; return var[a][b][123] or NULL if there is any key that is not exist.
    acVariable* getItemInVar(acVariable* var, const std::string& keys);

    //add a new item in table
    acVariable* addItemInTable(acVariable* tableVar, const char* key, acVarType valueType);
    //add a new item at array[idx], if sizeof(array) < idx, array will be fill up with null values
    acVariable* addItemInArray(acVariable* arrayVar, int idx, acVarType valueType);

    void setVarType(acVariable* var, acVarType type);

protected:

};



#endif //AC_VM_H

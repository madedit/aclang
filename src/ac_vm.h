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
    llvm::Module* m_module;
    llvm::ExecutionEngine* m_executionEngine;

    acMsgHandler m_msgHandler;
    acParser* m_parser;
    acCodeGenerator* m_codeGenerator;
    acGarbageCollector m_gc;
    bool m_isRuntimeError;

        //for debug
    bool m_printAST;
    bool m_printIR;

public:
    acVM();
    ~acVM();

    bool getInitOkay() { return m_initOkay; }

    llvm::LLVMContext& getLLVMContext() { return m_llvmContext; }
    llvm::Module* getModule() { return m_module; }
    llvm::ExecutionEngine* getExecutionEngine() { return m_executionEngine; }

    acMsgHandler* getMsgHandler() { return &m_msgHandler; }
    acParser* getParser() { return m_parser; }
    acCodeGenerator* getCodeGenerator() { return m_codeGenerator; }
    acGarbageCollector* getGarbageCollector() { return &m_gc; }
    void runtimeError(const std::string& errMsg);

    typedef void (*AC_FUNCTION)(acVariable* thisVar, acArray* args, acVM* vm);
    void bindFunction(const std::string& name, AC_FUNCTION func);
    //void callFunction(const std::string& name, std::vector<GenericValue> noargs);

    //user function
    void setUserFuncRetVar(bool v);
    void setUserFuncRetVar(acInt32 v);
    void setUserFuncRetVar(acInt64 v);
    void setUserFuncRetVar(acFloat v);
    void setUserFuncRetVar(acDouble v);
    void setUserFuncRetVar(const char* v);
    void setUserFuncRetVar(const std::string& v) { setUserFuncRetVar(v.c_str()); }
    void setUserFuncRetVar(acVariable* var);
    acVariable* getUserFuncRetVar();

    //helper function for creating acVariable objects
    acVariable* createString(const char* str);

    //for debug
    void setPrintAST(bool b) { m_printAST = b; }
    bool getPrintAST() { return m_printAST; }
    void setPrintIR(bool b) { m_printIR = b; }
    bool getPrintIR() { return m_printIR; }

public:
    //compile & run Code
    bool runCode(const char* code);

protected:

};



#endif //AC_VM_H

/* see copyright notice in aclang.h */

#include "ac_vm.h"
#include "ac_variable.h"
#include "ac_stdlib.h"
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ManagedStatic.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

using namespace llvm;


void llvm_fatal_error_handler(void *user_data, const std::string &reason, bool gen_crash_diag)
{
    acVM* vm = (acVM*)user_data;
    vm->getMsgHandler()->errorMessage("LLVM fatal error: %d\n", reason.c_str());
}


acVM::acVM()
    : m_initOkay(true)
    , m_llvmContext()
    , m_module(new Module("aclang jit", m_llvmContext))
    , m_msgHandler()
    , m_gc(this)
    , m_isRuntimeError(false)
    , m_printAST(true)
    , m_printIR(true)
{
    llvm::install_fatal_error_handler(&llvm_fatal_error_handler, this);
    InitializeNativeTarget();

    std::string s = m_module->getTargetTriple();
    //m_module->setTargetTriple("elf");

    std::string errStr;
    llvm::EngineBuilder factory(m_module);
    factory.setEngineKind(llvm::EngineKind::JIT);
    factory.setErrorStr(&errStr);
    factory.setUseMCJIT(true);
    m_executionEngine = factory.create();
    if(m_executionEngine == NULL)
    {
        m_msgHandler.errorMessage("Could not create ExecutionEngine: %s\n", errStr.c_str());
        m_initOkay = false;
    }

    m_parser = new acParser(this);
    m_codeGenerator = new acCodeGenerator(this);
    acStdLib::bindStdFunctions(this);
}

acVM::~acVM()
{
    delete m_codeGenerator;
    delete m_parser;
    delete m_executionEngine;
    llvm::llvm_shutdown();
}

void acVM::runtimeError(const std::string& errMsg)
{
    m_isRuntimeError = true;
    m_msgHandler.errorMessage(errMsg.c_str());
    longjmp(*m_codeGenerator->getErrorJmpBuf(), 1);
}

extern "C"
{
    void* addTableVar_str(acTable* tab, const char* name, acVM* vm);
}

void acVM::bindFunction(const std::string& name, AC_FUNCTION func)
{
    acUserFunc* uf = (acUserFunc*)getGarbageCollector()->createObject(acVT_USERFUNC);
    uf->m_funcPtr = (void*)func;

    acTable* rootTable = getCodeGenerator()->m_rootTable;
    acVariable* var = (acVariable*)addTableVar_str(rootTable, name.c_str(), this);
    var->setValue(uf);
}

void acVM::setUserFuncRetVar(bool v)
{
    m_codeGenerator->m_userFuncRetVar->setValue(v);
}

void acVM::setUserFuncRetVar(acInt32 v)
{
    m_codeGenerator->m_userFuncRetVar->setValue(v);
}

void acVM::setUserFuncRetVar(acInt64 v)
{
    m_codeGenerator->m_userFuncRetVar->setValue(v);
}

void acVM::setUserFuncRetVar(acFloat v)
{
    m_codeGenerator->m_userFuncRetVar->setValue(v);
}

void acVM::setUserFuncRetVar(acDouble v)
{
    m_codeGenerator->m_userFuncRetVar->setValue(v);
}

void acVM::setUserFuncRetVar(const char* v)
{
    acString* str = (acString*)m_gc.createObject(acVT_STRING);
    str->setData(v);
    m_codeGenerator->m_userFuncRetVar->setValue(str);
}

void acVM::setUserFuncRetVar(acVariable* var)
{
    m_codeGenerator->m_userFuncRetVar = var;
}

acVariable* acVM::getUserFuncRetVar()
{
    return m_codeGenerator->m_userFuncRetVar;
}

acVariable* acVM::createString(const char* str)
{
    return m_gc.createVarWithData(str);
}

extern int yyparse(void*);
bool acVM::runCode(const char* code, bool runGCFinally)
{
    m_isRuntimeError = false;
    m_codeGenerator->setCompileError(false);

    if(m_parser->setCode(code) == 0)
        return false;

    bool compileOk = true;

    if(yyparse(m_parser) != 0)
        compileOk = false;

    if(compileOk && m_parser->getProgramBlockAST() == 0)
        compileOk = false;

    if(compileOk && m_printAST)
    {
        printf("========AST Begin========\n");
        m_parser->getProgramBlockAST()->print(0);        
        printf("========AST End========\n");
    }

    if(compileOk)
    {
        m_codeGenerator->generateCode();
        if(m_codeGenerator->isCompileError())
            compileOk = false;

        m_codeGenerator->runCode();
    }

    m_parser->releaseNodeASTList();

    if(runGCFinally)
    {
        m_gc.completeGC();
    }

    return compileOk && !m_isRuntimeError;
}

struct KeyData
{
    std::string key;
    bool isNumber;
};
//split keys by '.'
bool splitKeys(const std::string& keysStr, std::vector<KeyData>& keys)
{
    KeyData kd;
    kd.key.clear();
    kd.isNumber = true;

    int count = (int)keysStr.size();
    for(int i = 0; i < count; ++i)
    {
        char ch = keysStr[i];
        if(ch == '.')
        {
            if(kd.key.empty())
                return false;

            //add a keydata
            keys.push_back(kd);
            //clear keydata
            kd.key.clear();
            kd.isNumber = true;
        }
        else if(kd.isNumber && ch <= '9' && ch >= '0')
        {
            kd.key.push_back(ch);
        }
        else
        {
            kd.key.push_back(ch);
            kd.isNumber = false;
        }
    }

    if(kd.key.empty())
        return false;

    //add a keydata
    keys.push_back(kd);

    return true;
}

acVariable* acVM::getItemInRootTable(const std::string& keys)
{
    return getItemInVar(getRootTable(), keys);
}

acVariable* acVM::getItemInVar(acVariable* var, const std::string& keys)
{
    std::vector<KeyData> keyData;
    if(!splitKeys(keys, keyData))
        return 0;

    int count = (int)keyData.size();
    for(int i = 0; i < count; ++i)
    {
        if(var == 0)
            return 0;

        const KeyData& kd = keyData[i];
        if(kd.isNumber)
        {
            int idx = atoi(kd.key.c_str());
            var =var->get(idx);
        }
        else
        {
            var = var->get(kd.key.c_str());
        }
    }

    return var;
}

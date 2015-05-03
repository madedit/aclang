/* see copyright notice in aclang.h */

#include "ac_vm.h"
#include "ac_variable.h"
#include "ac_stdlib.h"
#include <llvm/ExecutionEngine/MCJIT.h>
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ManagedStatic.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <memory>

using namespace llvm;


void llvm_fatal_error_handler(void *user_data, const std::string &reason, bool gen_crash_diag)
{
    acVM* vm = (acVM*)user_data;
    vm->getMsgHandler()->error("LLVM fatal error: %d\n", reason.c_str());
}

class HelpingMemoryManager : public SectionMemoryManager {
    HelpingMemoryManager(const HelpingMemoryManager &) = delete;
    void operator=(const HelpingMemoryManager &) = delete;

public:
    HelpingMemoryManager(acVM* vm) : m_vm(vm) {}
    virtual ~HelpingMemoryManager() {}

    /// This method returns the address of the specified symbol.
    /// Our implementation will attempt to find symbols in other
    /// modules associated with the MCJITHelper to cross link symbols
    /// from one generated module to another.
    virtual uint64_t getSymbolAddress(const std::string &name) override;

private:
    acVM* m_vm;
};

uint64_t HelpingMemoryManager::getSymbolAddress(const std::string &name) {
    uint64_t fnAddr = SectionMemoryManager::getSymbolAddress(name);
    if(fnAddr)
        return fnAddr;

    return (uint64_t)m_vm->getCodeGenerator()->getGlobalSymbolAddress(name);

    //uint64_t helperFun = m_vm->getCurrentExecutionEngine()->getFunctionAddress(name);
    //if(!helperFun)
    //{
    //    report_fatal_error("Program used extern function '" + Name +
    //        "' which could not be resolved!");
    //}
    //return helperFun;
}


acVM::acVM()
    : m_initOkay(true)
    , m_llvmContext()
    , m_module(0)
    , m_msgHandler()
    , m_gc(this)
    , m_isRuntimeError(false)
    , m_debugInfo(0)
    , m_printAST(false)
    , m_printIR(false)
{
    llvm::install_fatal_error_handler(&llvm_fatal_error_handler, this);
    
    //LLVMInitializeAllTargets();
    //LLVMInitializeAllTargetMCs();
    //LLVMInitializeAllTargetInfos();
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    //InitializeNativeTargetDisassembler();

    m_parser = new acParser(this);
    m_codeGenerator = new acCodeGenerator(this);

    createNewModuleEngine();
    
    acStdLib::bindStdFunctions(this);
}

acVM::~acVM()
{
    delete m_codeGenerator;
    delete m_parser;
    delete m_executionEngine;
    llvm::llvm_shutdown();
}

ExecutionEngine* acVM::getExecutionEngine(Module* mod)
{
    if(mod == m_module)
        return m_executionEngine;

    auto it = m_moduleEngineMap.find(mod);
    if(it == m_moduleEngineMap.end())
        return 0;

    return it->second;
}

void acVM::releaseCurrentModuleEngine()
{
    if(m_module != 0)
    {
        delete m_executionEngine;

        m_module = 0;
        m_executionEngine = 0;
        m_functionCount = 0;
    }
}

void acVM::storeCurrentModuleEngine()
{
    if(m_module != 0)
    {
        m_moduleEngineMap[m_module] = m_executionEngine;
        m_moduleFunctionCountMap[m_module] = m_functionCount;

        m_module = 0;
        m_executionEngine = 0;
        m_functionCount = 0;
    }
}

void acVM::decFunctionCount(llvm::Module* mod)
{
    if(mod == m_module)
    {
        if(m_functionCount > 0)
        {
            --m_functionCount;
        }
        else
        {
            //error!!!
        }
    }
    else
    {
        int count = m_moduleFunctionCountMap[mod];
        if(count > 0)
        {
            if(--count == 0)
            {
                ExecutionEngine* ee = m_moduleEngineMap[mod];
                m_moduleEngineMap.erase(mod);
                m_moduleFunctionCountMap.erase(mod);

                delete ee;
            }
            else
            {
                m_moduleFunctionCountMap[mod] = count;
            }
        }
        else
        {
            //error!!!
        }
    }
}

void acVM::createNewModuleEngine()
{
    storeCurrentModuleEngine();

    static int count = 0;
    char buf[16];
    sprintf(buf, "aclang jit %d", count++);
    std::unique_ptr<Module> mod(new Module(buf, m_llvmContext));
    m_module = mod.get();

#ifdef _WIN32
    std::string s = llvm::sys::getDefaultTargetTriple();
    //s = llvm::sys::getProcessTriple();
    //m_module->setTargetTriple("x86_64-pc-windows-msvc");
    m_module->setTargetTriple(s + "-elf");
#endif

    std::string errStr;
    llvm::EngineBuilder factory(std::move(mod));
    factory.setEngineKind(llvm::EngineKind::JIT);
    factory.setErrorStr(&errStr);

    HelpingMemoryManager* memMgr = new HelpingMemoryManager(this);
    factory.setMCJITMemoryManager(std::unique_ptr<RTDyldMemoryManager>(memMgr));

    m_executionEngine = factory.create();
    if(m_executionEngine == NULL)
    {
        m_msgHandler.error("Could not create ExecutionEngine: %s\n", errStr.c_str());
        m_initOkay = false;
    }
    else
    {
        m_codeGenerator->createCoreFunctions();
    }

    m_functionCount = 0;
}

void acVM::runtimeError(const char* errMsg)
{
    m_isRuntimeError = true;
    if(m_debugInfo != 0)
    {
        m_msgHandler.error(m_debugInfo->file, m_debugInfo->line, errMsg);
        m_debugInfo = 0;
    }
    else
    {
        m_msgHandler.error(errMsg);
    }
    m_gc.clearTempObj();
    longjmp(*m_codeGenerator->getErrorJmpBuf(), 1);
}

extern "C"
{
    void* addTableVar_str(acTable* tab, const char* name, acVM* vm);
}

void acVM::bindFunction(const std::string& name, AC_FUNCTION func)
{
    acUserFunc* uf = (acUserFunc*)m_gc.createObject(acVT_USERFUNC);
    uf->m_funcPtr = (void*)func;

    acTable* rootTable = m_codeGenerator->m_rootTable;
    acVariable* var = (acVariable*)addTableVar_str(rootTable, name.c_str(), this);
    var->setValue(uf);
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
    m_gc.clearTempObj();

    if(m_parser->setCode(code) == 0)
        return false;

    if(m_module == NULL)
    {
        createNewModuleEngine();
    }

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
        else
            m_codeGenerator->runCode();
    }

    if(m_functionCount == 0)
    {
        releaseCurrentModuleEngine();
    }
    else
    {
        storeCurrentModuleEngine();
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

acVariable* acVM::addItemInTable(acVariable* tableVar, const char* key, acVarType valueType)
{
    acGarbageCollector* gc = getGarbageCollector();
    acVariable* keyVar = gc->createVarWithData(key);
    acVariable* valVar = (acVariable*)gc->createObject(valueType);
    tableVar->toTable()->add(keyVar, valVar);
    return valVar;
}

acVariable* acVM::addItemInArray(acVariable* arrayVar, int idx, acVarType valueType)
{
    acGarbageCollector* gc = getGarbageCollector();
    acVariable* valVar = (acVariable*)gc->createObject(valueType);
    arrayVar->toArray()->fillAndSet(idx, valVar, this);
    return valVar;
}

void acVM::setVarType(acVariable* var, acVarType valueType)
{
    if(var->m_valueType != valueType)
    {
        switch(valueType)
        {
        case acVT_NULL:
            var->setNull();
            break;
        case acVT_BOOL:
            var->setValue(false);
            break;
        case acVT_INT32:
            var->setValue(acInt32(0));
            break;
        case acVT_INT64:
            var->setValue(acInt64(0));
            break;
        case acVT_FLOAT:
            var->setValue(acFloat(0));
            break;
        case acVT_DOUBLE:
            var->setValue(acDouble(0));
            break;
        case acVT_STRING:
            var->setValue("", this);
            break;
        case acVT_ARRAY:
            {
                acGCObject* obj = getGarbageCollector()->createObject(acVT_ARRAY);
                var->setValue(obj);
            }
            break;
        case acVT_TABLE:
            {
                acGCObject* obj = getGarbageCollector()->createObject(acVT_TABLE);
                var->setValue(obj);
            }
            break;
        case acVT_FUNCTION:
            {
                acGCObject* obj = getGarbageCollector()->createObject(acVT_FUNCTION);
                var->setValue(obj);
            }
            break;
        case acVT_DELEGATE:
            {
                acGCObject* obj = getGarbageCollector()->createObject(acVT_DELEGATE);
                var->setValue(obj);
            }
            break;
        case acVT_USERDATA:
            //TODO
            break;
        case acVT_USERFUNC:
            {
                acGCObject* obj = getGarbageCollector()->createObject(acVT_USERFUNC);
                var->setValue(obj);
            }
            break;
        }
    }
}

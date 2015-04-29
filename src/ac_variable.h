/* see copyright notice in aclang.h */

#ifndef AC_VARIABLE_H
#define AC_VARIABLE_H

#include "ac_config.h"
#include "ac_codegen.h"
#include "ac_hashvalue.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/Constants.h>
#include <list>
#include <map>
#include <string>
#include <vector>

class acVM;
class acGarbageCollector;
struct acGCObject;
struct acString;
struct acArray;
struct acTable;
struct acFunction;
struct acFuncBinder;
struct acFunctionData;

enum acVarType
{
    acVT_NULL = 0,
    //primitive data
    acVT_BOOL,
    acVT_INT32,
    acVT_INT64,
    acVT_FLOAT,
    acVT_DOUBLE,
    //gc object
    acVT_VAR,
    acVT_STRING,
    acVT_ARRAY,
    acVT_TABLE,
    acVT_FUNCTION,
    acVT_DELEGATE,
    //user data
    acVT_USERDATA,
    acVT_USERFUNC,
    //helper data, internal use only
    acVT_FUNCBINDER,
    acVT_FUNCTIONDATA,
};

enum acBaseFunc
{
    acBF_TOBOOL,
    acBF_TOINT32,
    acBF_TOINT64,
    acBF_TOFLOAT,
    acBF_TODOUBLE,
    acBF_TOSTR,
    acBF_CALL,
    acBF_MAX
};

enum acOperatorFunc
{
    acOF_NEW,// new "_new"
    acOF_ADD,// + "_add"
    acOF_SUB,// - "_sub"
    acOF_MUL,// * "_mul"
    acOF_DIV,// / "_div"
    acOF_MOD,// % "_mod"
    acOF_MAX,
};

#pragma pack(1)
struct acGCObject
{
    acVarType m_objType : 8;
    acUInt8 m_gcColor;

    acGCObject()
    {
    }

    acGCObject(acVarType type)
        : m_objType(type)
    {
    }
};
#pragma pack()

#pragma pack(1)
struct acVariable : acGCObject
{
    acVarType m_valueType : 8;

    union //value
    {
        acInt32 m_int32;
        acInt64 m_int64;
        acFloat m_float;
        acDouble m_double;
        acGCObject* m_gcobj;
    };

    acHashValue m_hash;
    void**      m_baseFuncPtrs;

    acVariable()
    {
        setNull();
    }

    void setNull()
    {
        memset(this, 0, sizeof(acVariable));
        m_objType = acVT_VAR;
        setBaseFuncPtrs(this);
    }
    void setValue(bool v)
    {
        m_valueType = acVT_BOOL;
        m_int64 = 0;
        m_int32 = v;
        setBaseFuncPtrs(this);
    }
    void setValue(acInt32 v)
    {
        m_valueType = acVT_INT32;
        m_int64 = 0;
        m_int32 = v;
        setBaseFuncPtrs(this);
    }
    void setValue(acInt64 v)
    {
        m_valueType = acVT_INT64;
        m_int64 = v;
        setBaseFuncPtrs(this);
    }
    void setValue(acFloat v)
    {
        m_valueType = acVT_FLOAT;
        m_int64 = 0;
        m_float = v;
        setBaseFuncPtrs(this);
    }
    void setValue(acDouble v)
    {
        m_valueType = acVT_DOUBLE;
        m_double = v;
        setBaseFuncPtrs(this);
    }
    void setValue(acVariable* v)
    {
        assignFrom(v);
    }
    void setValue(acGCObject* v)
    {
        m_valueType = v->m_objType;
        m_gcobj = v;
        setBaseFuncPtrs(this);
    }
    void setValue(const char* str, acVM* vm);
    
    void assignFrom(acVariable* v);
    void cloneTo(acVariable* v, acVM* vm);

    acHashValue& getHash();
    static void getHash(acInt32 value, acHashValue& hash);
    static void getHash(acInt64 value, acHashValue& hash);
    static void getHash(const char* str, acHashValue& hash);
    static void setBaseFuncPtrs(acVariable* var);

    //return >0, =0, <0
    int compare(acVariable* v, acVM* vm);

    //get child var by index/key. for array & table.
    acVariable* get(acInt32 idx);
    acVariable* get(acInt64 idx);
    acVariable* get(const char* key);
    acVariable* get(acVariable* key);

    acString* toString() { return (acString*)m_gcobj; }
    acArray* toArray() { return (acArray*)m_gcobj; }
    acTable* toTable() { return (acTable*)m_gcobj; }
};
#pragma pack()

struct acString : acGCObject
{
    acUInt32 m_hash;
    acUInt32 m_sum;
    std::string m_data;
    int m_iteratorIndex;//for foreach()

    acString()
        : acGCObject(acVT_STRING)
        , m_hash(0)
    {
    }

    acString(acChar* begin, acChar* end)
        : acGCObject(acVT_STRING)
        , m_data(begin, end)
    {
        hash();
    }

    void setData(const std::string& data)
    {
        m_data = data;
        hash();
    }

    const char* c_str() const
    {
        return m_data.c_str();
    }

    void hash();

    void initIter() { m_iteratorIndex = 0; }
    bool iterate(acVariable* idx, acVariable* value)
    {
        if(m_iteratorIndex < 0 || m_iteratorIndex >= (int)m_data.size())
            return false;

        if(idx != 0)
            idx->setValue(m_iteratorIndex);
        if(value != 0)
            value->setValue((int)m_data[m_iteratorIndex]);

        ++m_iteratorIndex;
        return true;
    }
};

struct acArray : acGCObject
{
    std::vector<acVariable*> m_data;
    typedef std::vector<acVariable*>::iterator DataIterator;
    int m_iteratorIndex;//for foreach()

    acArray()
        : acGCObject(acVT_ARRAY)
        , m_iteratorIndex(-1)
    {
    }

    int size() { return m_data.size(); }
    void add(acVariable* var) { m_data.push_back(var); }
    acVariable* get(int idx) { return m_data[idx]; }
    void set(int idx, acVariable* var) { m_data[idx] = var; }
    void fillAndSet(int idx, acVariable* var, acVM* vm);
    acVariable* fillAndGet(int idx, acVM* vm);

    void initIter() { m_iteratorIndex = 0; }
    bool iterate(acVariable* idx, acVariable* value)
    {
        if(m_iteratorIndex < 0 || m_iteratorIndex >= size())
            return false;

        if(idx != 0)
            idx->setValue(m_iteratorIndex);
        if(value != 0)
            value->setValue(m_data[m_iteratorIndex]);

        ++m_iteratorIndex;
        return true;
    }

    void cloneTo(acArray* other, acVM* vm);
};

struct acTable : acGCObject
{
    struct KeyValue
    {
        acVariable* key;
        acVariable* value;
        KeyValue(acVariable* k, acVariable* v)
            : key(k)
            , value(v)
        {
        }
    };

    std::map<acHashValue, KeyValue> m_data;
    typedef std::map<acHashValue, KeyValue>::iterator DataIterator;
    DataIterator m_iterator;//for foreach()

    acFuncBinder* m_funcBinder;

    acTable()
        : acGCObject(acVT_TABLE)
        , m_iterator(m_data.end())
        , m_funcBinder(0)
    {
    }

    void add(acVariable* key, acVariable* var)
    {
        acHashValue& hash = key->getHash();
        DataIterator it = m_data.find(hash);
        if(it == m_data.end())
        {
            m_data.insert(std::make_pair(hash, KeyValue(key, var)));
        }
        else
        {
            it->second = KeyValue(key, var);
        }
    }
    //helper functions for add kv
    void add(const char* key, const char* value, acVM* vm);
    void add(const char* key, int value, acVM* vm);
    void add(int key, const char* value, acVM* vm);
    void add(int key, int value, acVM* vm);

    void remove(acInt32 idx)
    {
        acHashValue hash;
        acVariable::getHash(idx, hash);
        m_data.erase(hash);
    }
    void remove(acInt64 idx)
    {
        acHashValue hash;
        acVariable::getHash(idx, hash);
        m_data.erase(hash);
    }
    void remove(const char* key)
    {
        acHashValue hash;
        acVariable::getHash(key, hash);
        m_data.erase(hash);
    }
    void remove(acVariable* key)
    {
        m_data.erase(key->getHash());
    }
    //get value by int32
    acVariable* get(acInt32 idx)
    {
        acHashValue hash;
        acVariable::getHash(idx, hash);
        DataIterator it = m_data.find(hash);
        if(it == m_data.end()) return 0;
        return it->second.value;
    }
    //get value by int64
    acVariable* get(acInt64 idx)
    {
        acHashValue hash;
        acVariable::getHash(idx, hash);
        DataIterator it = m_data.find(hash);
        if(it == m_data.end()) return 0;
        return it->second.value;
    }
    //get value by string
    acVariable* get(const char* key)
    {
        acHashValue hash;
        acVariable::getHash(key, hash);
        DataIterator it = m_data.find(hash);
        if(it == m_data.end()) return 0;
        return it->second.value;
    }
    //get value by var
    acVariable* get(acVariable* key)
    {
        acHashValue& hash = key->getHash();
        DataIterator it = m_data.find(hash);
        if(it == m_data.end()) return 0;
        return it->second.value;
    }

    void initIter() { m_iterator = m_data.begin(); }
    bool iterate(acVariable* key, acVariable* value)
    {
        if(m_iterator == m_data.end())
            return false;

        KeyValue& kv = m_iterator->second;

        if(key != 0)
            key->setValue(kv.key);
        if(value != 0)
            value->setValue(kv.value);

        ++m_iterator;
        return true;
    }

    void cloneTo(acTable* other, acVM* vm);
    void copyDataTo(acTable* other, acVM* vm);

    void bindFunc(char* name, acVariable* func);
    void bindFunc(acVariable* key, acVariable* func, acVM* vm);
    void bindFunc(acTable* table, acVM* vm);
    acVariable* getBindFunc(acOperatorFunc func);
    acVariable* getBindFunc(const char* name);
    acVariable* getBindFunc(acVariable* key);
};

struct acFunction : acGCObject
{
    acFunctionData* m_funcData;
    acTable* m_upValueTable;
    std::list<acGCObject*>* m_createdFuncDataList;

    acFunction()
        : acGCObject(acVT_FUNCTION)
        , m_funcData(0)
        , m_upValueTable(0)
        , m_createdFuncDataList(0)
    {
    }
};

struct acDelegate : acGCObject
{
    acVariable* m_thisVar;
    acVariable* m_funcVar;

    acDelegate()
        : acGCObject(acVT_DELEGATE)
        , m_thisVar(0)
        , m_funcVar(0)
    {
    }
};

struct acUserFunc : acGCObject
{
    void* m_funcPtr;

    acUserFunc()
        : acGCObject(acVT_USERFUNC)
        , m_funcPtr(0)
    {
    }
};

struct acFuncBinder : acGCObject
{
    acTable* m_funcTable;
    acVariable* m_funcArray[acOF_MAX];//function or userfunc

    acFuncBinder()
        : acGCObject(acVT_FUNCBINDER)
        , m_funcTable(0)
    {
        memset(m_funcArray, 0, sizeof(m_funcArray));
    }

    void cloneTo(acFuncBinder* dest, acVM* vm);
    void bindFunc(acVariable* key, acVariable* func);
    void bindFunc(acTable* table, acVM* vm);

    acOperatorFunc getOpFunc(acVariable* var);
};

struct acFunctionData : acGCObject
{
    llvm::Function* m_llvmFunc;
    void* m_funcPtr;
    std::list<std::string>* m_stringList;
    std::list<acDebugInfo>* m_debugInfoList;

    acFunctionData()
        : acGCObject(acVT_FUNCTIONDATA)
        , m_llvmFunc(0)
        , m_funcPtr(0)
        , m_stringList(0)
        , m_debugInfoList(0)
    {
    }
};

std::string getVarTypeStr(acVarType vt);
bool toBool(acVariable* var, acVM* vm);
acInt32 toInt32(acVariable* var, acVM* vm);
acInt64 toInt64(acVariable* var, acVM* vm);
acFloat toFloat(acVariable* var, acVM* vm);
acDouble toDouble(acVariable* var, acVM* vm);
std::string toString(acVariable* var, acVM* vm);
void callFunction(acVariable* var, acVariable* thisVar, acArray* argArray, acVM* vm);
void addInt32(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void subInt32(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void mulInt32(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void divInt32(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void modInt32(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void addInt64(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void subInt64(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void mulInt64(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void divInt64(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void modInt64(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void addFloat(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void subFloat(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void mulFloat(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void divFloat(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void modFloat(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void addDouble(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void subDouble(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void mulDouble(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void divDouble(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void modDouble(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);
void addString(acVariable* ret, acVariable* v1, acVariable* v2, acVM* vm);

#endif //AC_VARIABLE_H

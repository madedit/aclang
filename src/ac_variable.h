/* see copyright notice in aclang.h */

#ifndef AC_VARIABLE_H
#define AC_VARIABLE_H

#include "ac_config.h"
#include "ac_hashvalue.h"
#include <llvm/IR/Function.h>
#include <list>
#include <map>
#include <string>
#include <vector>

class acVM;
class acGarbageCollector;
struct acString;
struct acArray;
struct acTable;
struct acFunction;

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
    acVT_USERFUNC
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

/*
enum acOperatorFunc
{
    acOF_ADD,// +
    acOF_SUB,// -
    acOF_MUL,// *
    acOF_DIV,// /
    acOF_MOD,// %
    acOF_MAX,
};
*/

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
    //acVariable* m_OperatorFuncs;

    acTable*    m_bindFuncTable;
    bool m_bftHasWritten;//copy-on-write

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

    void assignFrom(acVariable* v);
    acVariable* getBindFunc(char* name);
    acVariable* getBindFunc(acVariable* key);
    void setBindFunc(char* name, acVariable* func);
    void setBindFunc(acVariable* key, acVariable* func);

    acHashValue& getHash();
    static void getHash(int value, acHashValue& hash);
    static void getHash(const char* str, acHashValue& hash);
    static void setBaseFuncPtrs(acVariable* var);

    //return >0, =0, <0
    int compare(acVariable* v, acVM* vm);

    //get child var by index/key. for array & table.
    acVariable* operator[](int idx);
    acVariable* operator[](const char* key);
    acVariable* operator[](acVariable* key);
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

    acTable()
        : acGCObject(acVT_TABLE)
        , m_iterator(m_data.end())
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
    void remove(acVariable* key)
    {
        m_data.erase(key->getHash());
    }
    //get value by int
    acVariable* get(int idx)
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

    void copyTo(acTable* other)
    {
        other->m_data = m_data;
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
};

struct acFunction : acGCObject
{
    void* m_funcPtr;
    acTable* m_upValueTable;

    acFunction()
        : acGCObject(acVT_FUNCTION)
        , m_funcPtr(0)
        , m_upValueTable(0)
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

/* see copyright notice in aclang.h */

#ifndef AC_UTILITY_H
#define AC_UTILITY_H

#include "ac_variable.h"
//#include "ac_gc.h"
#include <list>
#include <string>
#include <vector>

typedef std::vector<acChar> acCharVector;
typedef std::vector<acDchar> acDcharVector;
typedef std::vector<acString> acStringVector;
typedef std::list<acString> acStringList;

/*
class acBuffer
{
protected:
    acGarbageCollector* m_gc;
    size_t              m_reserve_size;
    size_t              m_capacity;
    void*               m_base_address; // the base address
    size_t              m_size;

public:
    acBuffer(acGarbageCollector* gc);
    ~acBuffer();
    void resize(size_t size);

    void push_back(acInt8 v);
    void push_back(acInt16 v);
    void push_back(acInt32 v);
    void push_back(acInt64 v);
    void push_back(void* v);
    void push_back(void* p, size_t size);

};
*/

#endif //AC_UTILITY_H

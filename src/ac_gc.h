/* see copyright notice in aclang.h */

#ifndef AC_GC_H
#define AC_GC_H

#include "ac_variable.h"
#include <list>
#include <set>
#include <string>
#include <vector>
#include <time.h>

class acVM;

class acGarbageCollector
{
public:
    enum CollectionState
    {
        INIT,
        MARK,
        SWEEP,
        FINAL
    };

    enum GC_Color
    {
        GC_WHITE = 0,//unused
        GC_GRAY  = 1,//parent is used, self is not processed yet
        GC_BLACK = 2 //used
    };


private:
    acVM* m_vm;
    CollectionState m_state;
    std::list<acGCObject*> m_rootList;
    std::list<acGCObject*> m_objectList;
    std::list<acGCObject*>::iterator m_sweepIter, m_sweepLastIter;
    std::set<acGCObject*> m_grayList;

public:
    acGarbageCollector(acVM* vm)
        : m_vm(vm)
        , m_state(INIT)
    {
    }

    acGCObject* createObject(acVarType type);
    acVariable* createVarWithData(const char* data);

    acVM* getVM() { return m_vm; }
    void addRootObj(acGCObject* obj) { m_rootList.push_back(obj); }
    void incrementalCollect(clock_t clocks);
    CollectionState getGCState() { return m_state; }
    void changeGCColor(acGCObject* obj);

    size_t getObjectListCount() { return m_objectList.size(); }
    size_t getGrayListCount() { return m_grayList.size(); }

private:    
    void initGCColor(acGCObject* obj);
    bool gcInit();
    bool gcMark(clock_t clocks);
    bool gcSweep(clock_t clocks);
    bool gcFinal(clock_t clocks);

    void addChildrenToGrayList(acVariable* var);
    void addChildrenToGrayList(acArray* array);
    void addChildrenToGrayList(acTable* table);
    void addChildrenToGrayList(acFunction* func);
    void addChildrenToGrayList(acDelegate* dele);
    void addChildrenToGrayList(acUserFunc* uf);
};



#endif //AC_GC_H

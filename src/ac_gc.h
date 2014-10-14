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
    std::list<acGCObject*> m_tempList;//store temp variables to avoid being GCed
    std::list<acGCObject*> m_objectList;
    std::list<acGCObject*>::iterator m_sweepIter, m_sweepLastIter;
    std::set<acGCObject*> m_grayList;

    //for debug
    bool m_printGC;
public:
    acGarbageCollector(acVM* vm)
        : m_vm(vm)
        , m_state(INIT)
        , m_printGC(false)
    {
    }

    acGCObject* createObject(acVarType type);
    acVariable* createVarWithData(const char* data);
    acVariable* createVarWithData(acInt32 data);

    acVM* getVM() { return m_vm; }

    void addRootObj(acGCObject* obj) { m_rootList.push_back(obj); }
    void addTempObj(acGCObject* obj) { m_tempList.push_back(obj); }
    void removeTempObj(acGCObject* obj) { m_tempList.remove(obj); }
    void clearTempObj() { m_tempList.clear(); }

    void incrementalGC(clock_t clocks);//run incremental gc
    void completeGC();//run one complete gc
    CollectionState getGCState() { return m_state; }
    void changeGCColor(acGCObject* obj);

    size_t getObjectListCount() { return m_objectList.size(); }
    size_t getGrayListCount() { return m_grayList.size(); }

    void setPrintGC(bool b) { m_printGC = b; }
    bool getPrintGC() { return m_printGC; }

private:    
    void initGCColor(acGCObject* obj);
    void addToGrayList(std::list<acGCObject*>& list);
    bool gcInit();
    bool gcMark(clock_t clocks);
    bool gcSweep(clock_t clocks);
    bool gcFinal(clock_t clocks);

    void addChildrenToGrayList(acVariable* var);
    void addChildrenToGrayList(acArray* array);
    void addChildrenToGrayList(acTable* table);
    void addChildrenToGrayList(acFunction* func);
    void addChildrenToGrayList(acDelegate* dele);
    void addChildrenToGrayList(acFuncBinder* fb);
    void addChildrenToGrayList(acUserFunc* uf);
};



#endif //AC_GC_H

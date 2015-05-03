/* see copyright notice in aclang.h */

#include "ac_gc.h"
#include "ac_vm.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <stdio.h>
#include <string.h>


acGCObject* acGarbageCollector::createObject(acVarType type)
{
    acGCObject* obj;
    
    switch(type)
    {
    case acVT_NULL:
    case acVT_BOOL:
    case acVT_INT32:
    case acVT_INT64:
    case acVT_FLOAT:
    case acVT_DOUBLE:
        {
            acVariable* var = new acVariable();
            var->m_valueType = type;
            acVariable::setBaseFuncPtrs(var);
            obj = var;
        }
        break;
    case acVT_VAR:
        obj = new acVariable();
        //acVariable::setBaseFuncPtrs((acVariable*)obj);
        break;
    case acVT_STRING:
        obj = new acString();
        break;
    case acVT_ARRAY:
        obj = new acArray();
        break;
    case acVT_TABLE:
        obj = new acTable();
        break;
    case acVT_FUNCTION:
        obj = new acFunction();
        break;
    case acVT_DELEGATE:
        obj = new acDelegate();
        break;

    case acVT_USERDATA:
        //obj = new acUserData();//TODO
        break;
    case acVT_USERFUNC:
        obj = new acUserFunc();
        break;

    case acVT_FUNCBINDER:
        {
            acFuncBinder* fb = new acFuncBinder();
            fb->m_funcTable = (acTable*)createObject(acVT_TABLE);
            obj = fb;
        }
        break;

    case acVT_FUNCTIONDATA:
        obj = new acFunctionData();
        break;
    }

    m_objectList.push_back(obj);
    initGCColor(obj);
    return obj;
}

acVariable* acGarbageCollector::createVarWithData(const char* data)
{
    acString* str = (acString*)createObject(acVT_STRING);
    str->setData(data);
    acVariable* var = (acVariable*)createObject(acVT_VAR);
    var->setValue(str);
    return var;
}

acVariable* acGarbageCollector::createVarWithData(acInt32 data)
{
    acVariable* var = (acVariable*)createObject(acVT_INT32);
    var->m_int32 = data;
    return var;
}

void acGarbageCollector::incrementalGC(clock_t clocks)
{
    switch(m_state)
    {
    case INIT:
        if(gcInit())
        {
            m_state = MARK;
        }
        break;
    case MARK:
        if(gcMark(clocks))
        {
            m_state = SWEEP;
        }
        break;
    case SWEEP:
        if(gcSweep(clocks))
        {
            m_state = FINAL;
        }
        break;
    case FINAL:
        if(gcFinal(clocks))
        {
            m_state = INIT;
        }
        break;
    }
}

void acGarbageCollector::completeGC()
{
    do
    {
        incrementalGC(0x7FFFFFFF);
    }
    while(m_state != INIT);
}

void acGarbageCollector::changeGCColor(acGCObject* obj)
{
    if(m_state == MARK)
    {
        if(obj->m_gcColor == GC_WHITE)
        {
            switch(obj->m_objType)
            {
            case acVT_VAR:
            case acVT_ARRAY:
            case acVT_TABLE:
            case acVT_FUNCTION:
            case acVT_DELEGATE:
            case acVT_USERFUNC:
            case acVT_FUNCBINDER:
                obj->m_gcColor = GC_GRAY;
                m_grayList.insert(obj);
                break;
            default:
                obj->m_gcColor = GC_BLACK;
                break;
            }
        }
    }
}

void acGarbageCollector::initGCColor(acGCObject* obj)
{
    if(m_state == MARK)
    {
        obj->m_gcColor = GC_BLACK;
    }
    else
    {
        obj->m_gcColor = GC_WHITE;
    }
}

void acGarbageCollector::addToGrayList(std::list<acGCObject*>& list)
{
    std::list<acGCObject*>::iterator it = list.begin();
    std::list<acGCObject*>::iterator itEnd = list.end();
    while(it != itEnd)
    {
        acGCObject* obj = *it;
        obj->m_gcColor = GC_BLACK;
        switch(obj->m_objType)
        {
        case acVT_VAR:
            addChildrenToGrayList((acVariable*)obj);
            break;
        case acVT_ARRAY:
            addChildrenToGrayList((acArray*)obj);
            break;
        case acVT_TABLE:
            addChildrenToGrayList((acTable*)obj);
            break;
        case acVT_FUNCTION:
            addChildrenToGrayList((acFunction*)obj);
            break;
        case acVT_DELEGATE:
            addChildrenToGrayList((acDelegate*)obj);
            break;
        case acVT_USERFUNC:
            addChildrenToGrayList((acUserFunc*)obj);
            break;
        case acVT_FUNCBINDER:
            addChildrenToGrayList((acFuncBinder*)obj);
            break;
        }
        ++it;
    }
}

bool acGarbageCollector::gcInit()
{
    if(m_objectList.size() == 0) return false;

    //all objects are white, add children in roottable to grayList
    addToGrayList(m_rootList);
    addToGrayList(m_tempList);

    m_sweepIter = m_objectList.begin();
    m_sweepLastIter = m_objectList.end();
    //point to last object, not end-iterator
    --m_sweepLastIter;

    return true;
}

bool acGarbageCollector::gcMark(clock_t clocks)
{
    clock_t beginClock = clock();

    if(m_grayList.size() != 0)
    {
        do
        {
            std::set<acGCObject*>::iterator it = m_grayList.begin();
            acGCObject* obj = *it;

            obj->m_gcColor = GC_BLACK;

            switch(obj->m_objType)
            {
            case acVT_VAR:
                addChildrenToGrayList((acVariable*)obj);
                break;
            case acVT_ARRAY:
                addChildrenToGrayList((acArray*)obj);
                break;
            case acVT_TABLE:
                addChildrenToGrayList((acTable*)obj);
                break;
            case acVT_FUNCTION:
                addChildrenToGrayList((acFunction*)obj);
                break;
            case acVT_DELEGATE:
                addChildrenToGrayList((acDelegate*)obj);
                break;
            case acVT_USERFUNC:
                addChildrenToGrayList((acUserFunc*)obj);
                break;
            case acVT_FUNCBINDER:
                addChildrenToGrayList((acFuncBinder*)obj);
                break;
            }

            m_grayList.erase(it);
        }
        while((m_grayList.size() != 0) && (clock() - beginClock < clocks));
    }

    return m_grayList.size() == 0;
}

bool acGarbageCollector::gcSweep(clock_t clocks)
{
    clock_t beginClock = clock();

    bool isLast = false;
    do
    {
        isLast = (m_sweepIter == m_sweepLastIter);
        acGCObject* obj = *m_sweepIter;

        if(obj->m_gcColor == GC_WHITE)
        {
            //delete variable
            switch(obj->m_objType)
            {
            case acVT_VAR:
                if(m_printGC)
                    printf("gc: delete var: %p\n", obj);

                delete (acVariable*)obj;
                break;

            case acVT_STRING:
                if(m_printGC)
                    printf("gc: delete string: %p\n", obj);

                ((acString*)obj)->m_data.clear();
                delete (acString*)obj;
                break;

            case acVT_ARRAY:
                if(m_printGC)
                    printf("gc: delete array: %p\n", obj);

                ((acArray*)obj)->m_data.clear();
                delete (acArray*)obj;
                break;

            case acVT_TABLE:
                if(m_printGC)
                    printf("gc: delete table: %p\n", obj);

                ((acTable*)obj)->m_data.clear();
                delete (acTable*)obj;
                break;

            case acVT_FUNCTION:
                if(m_printGC)
                    printf("gc: delete function: %p\n", obj);

                {
                    acFunction* func = (acFunction*)obj;
                    delete func->m_createdFuncDataList;
                    delete func;
                }
                break;

            case acVT_DELEGATE:
                if(m_printGC)
                    printf("gc: delete delegate: %p\n", obj);

                //TODO
                delete (acDelegate*)obj;
                break;

            case acVT_USERFUNC:
                if(m_printGC)
                    printf("gc: delete userfunc: %p\n", obj);

                //TODO
                delete (acUserFunc*)obj;
                break;

            case acVT_FUNCBINDER:
                if(m_printGC)
                    printf("gc: delete funcbinder: %p\n", obj);

                delete (acFuncBinder*)obj;
                break;

            case acVT_FUNCTIONDATA:
                if(m_printGC)
                    printf("gc: delete funcdata: %p\n", obj);

                {
                    acFunctionData* funcData = (acFunctionData*)obj;
                    //ExecutionEngine* ee = m_vm->getExecutionEngine();
                    //ee->freeMachineCodeForFunction(funcData->m_llvmFunc);
                    //funcData->m_llvmFunc->replaceAllUsesWith(UndefValue::get(funcData->m_llvmFunc->getType()));
                    //funcData->m_llvmFunc->deleteBody();
                    //funcData->m_llvmFunc->eraseFromParent();
                    Module* mod = funcData->m_llvmFunc->getParent();
                    m_vm->decFunctionCount(mod);

                    delete funcData->m_stringList;
                    delete funcData->m_debugInfoList;
                    delete funcData;
                }
                break;

            default:
                break;
            }

            m_sweepIter = m_objectList.erase(m_sweepIter);
        }
        else
        {
            obj->m_gcColor = GC_WHITE;
            ++m_sweepIter;
        }
    }
    while((!isLast) && (clock() - beginClock < clocks));

    return isLast;
}

bool acGarbageCollector::gcFinal(clock_t clocks)
{
    clock_t beginClock = clock();
    std::list<acGCObject*>::iterator endIter = m_objectList.end();

    //mark new created objects between GC cycle as white
    if(m_sweepIter != endIter)
    {
        do
        {
            (*m_sweepIter)->m_gcColor = GC_WHITE;

            if(++m_sweepIter == endIter)
            {
                return true;
            }
        }
        while(clock() - beginClock < clocks);

        return false;
    }

    return true;
}

void acGarbageCollector::addChildrenToGrayList(acVariable* var)
{
    switch(var->m_valueType)
    {
    case acVT_STRING:
    case acVT_FUNCTIONDATA:
        var->m_gcobj->m_gcColor = GC_BLACK;
        break;
    case acVT_VAR:
    case acVT_ARRAY:
    case acVT_TABLE:
    case acVT_FUNCTION:
    case acVT_DELEGATE:
    case acVT_USERFUNC:
    case acVT_FUNCBINDER:
        {
            acGCObject* obj = var->m_gcobj;
            if(obj->m_gcColor == GC_WHITE)
            {
                obj->m_gcColor = GC_GRAY;
                m_grayList.insert(obj);
            }
        }
        break;
    default:
        break;
    }
}

void acGarbageCollector::addChildrenToGrayList(acArray* array)
{
    std::vector<acVariable*>::iterator it = array->m_data.begin();
    std::vector<acVariable*>::iterator itend = array->m_data.end();

    while(it != itend)
    {
        acVariable* var = *it;
        var->m_gcColor = GC_BLACK;

        switch(var->m_valueType)
        {
        case acVT_STRING:
        case acVT_FUNCTIONDATA:
            var->m_gcobj->m_gcColor = GC_BLACK;
            break;
        case acVT_VAR:
        case acVT_ARRAY:
        case acVT_TABLE:
        case acVT_FUNCTION:
        case acVT_DELEGATE:
        case acVT_USERFUNC:
        case acVT_FUNCBINDER:
            {
                acGCObject* obj = var->m_gcobj;
                if(obj->m_gcColor == GC_WHITE)
                {
                    obj->m_gcColor = GC_GRAY;
                    m_grayList.insert(obj);
                }
            }
            break;
        default:
            break;
        }
        ++it;
    }
}

void acGarbageCollector::addChildrenToGrayList(acTable* table)
{
    acTable::DataIterator it = table->m_data.begin();
    acTable::DataIterator itend = table->m_data.end();

    while(it != itend)
    {
        acTable::KeyValue kv = it->second;

        acVariable* key = kv.key;
        key->m_gcColor = GC_BLACK;
        switch(key->m_valueType)
        {
        case acVT_STRING:
        case acVT_FUNCTIONDATA:
            key->m_gcobj->m_gcColor = GC_BLACK;
            break;
        case acVT_VAR:
        case acVT_ARRAY:
        case acVT_TABLE:
        case acVT_FUNCTION:
        case acVT_DELEGATE:
        case acVT_USERFUNC:
        case acVT_FUNCBINDER:
            {
                acGCObject* obj = key->m_gcobj;
                if(obj->m_gcColor == GC_WHITE)
                {
                    obj->m_gcColor = GC_GRAY;
                    m_grayList.insert(obj);
                }
            }
            break;
        default:
            break;
        }

        acVariable* var = kv.value;
        var->m_gcColor = GC_BLACK;
        switch(var->m_valueType)
        {
        case acVT_STRING:
        case acVT_FUNCTIONDATA:
            var->m_gcobj->m_gcColor = GC_BLACK;
            break;
        case acVT_VAR:
        case acVT_ARRAY:
        case acVT_TABLE:
        case acVT_FUNCTION:
        case acVT_DELEGATE:
        case acVT_USERFUNC:
        case acVT_FUNCBINDER:
            {
                acGCObject* obj = var->m_gcobj;
                if(obj->m_gcColor == GC_WHITE)
                {
                    obj->m_gcColor = GC_GRAY;
                    m_grayList.insert(obj);
                }
            }
            break;
        default:
            break;
        }
        ++it;
    }

    if(table->m_funcBinder != 0)
    {
        table->m_funcBinder->m_gcColor = GC_BLACK;
        addChildrenToGrayList(table->m_funcBinder);
    }
}

void acGarbageCollector::addChildrenToGrayList(acFunction* func)
{
    func->m_funcData->m_gcColor = GC_BLACK;

    if(func->m_upValueTable != 0)
    {
        func->m_upValueTable->m_gcColor = GC_BLACK;
        addChildrenToGrayList(func->m_upValueTable);
    }

    if(func->m_createdFuncDataList != 0)
    {
        addToGrayList(*(func->m_createdFuncDataList));
    }
}

void acGarbageCollector::addChildrenToGrayList(acDelegate* dele)
{
    if(dele->m_funcVar != 0)
    {
        dele->m_funcVar->m_gcColor = GC_BLACK;
        addChildrenToGrayList(dele->m_funcVar);
    }
}

void acGarbageCollector::addChildrenToGrayList(acFuncBinder* fb)
{
    if(fb->m_funcTable != 0)
    {
        fb->m_funcTable->m_gcColor = GC_BLACK;
        addChildrenToGrayList(fb->m_funcTable);
    }

    //all functions are in funcTable
    //for(int i = 0; i < acOF_MAX; ++i)
    //{
    //    acGCObject* func = fb->m_funcArray[i];
    //    if(func != 0)
    //    {
    //    }
    //}
}

void acGarbageCollector::addChildrenToGrayList(acUserFunc* uf)
{
}

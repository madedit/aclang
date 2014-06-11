#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ac_gc.h>

void test_gc()
{
    acGarbageCollector gc(0);
    acTable* root = (acTable*)gc.createObject(acVT_TABLE);
    acVariable* rootTableVar = (acVariable*)gc.createObject(acVT_VAR);
    rootTableVar->setValue(root);
    gc.addRootObj(rootTableVar);
    printf("\ncreate root table=%p\n", root);

    acTable* t1 = (acTable*)gc.createObject(acVT_TABLE);
    printf("create table=%p\n", t1);

    acVariable* key = (acVariable*)gc.createObject(acVT_VAR);
    printf("create key=%p\n", key);
    key->setValue(1);

    acVariable* var = (acVariable*)gc.createObject(acVT_VAR);
    printf("create var=%p\n", var);
    var->setValue(t1);

    root->add(key, var);

    for(int i=0;i<10;++i)
    {
        acTable* t2 = (acTable*)gc.createObject(acVT_TABLE);
        printf("create table=%p\n", t2);

        acVariable* var = (acVariable*)gc.createObject(acVT_VAR);
        printf("create var=%p\n", var);
        var->setValue(t2);

        acVariable* key = (acVariable*)gc.createObject(acVT_VAR);
        printf("create key=%p\n", key);
        key->setValue(i);
        t1->add(key, var);
    }

    
    //root->remove(1);

    printf("root size=%d, objectCount=%d\n", root->m_data.size(), gc.getObjectListCount());
    getchar();

    for(int i = 0; i<100;++i)
    {
        if(i==15)
        {
            root->remove(key);
            printf("root size=%d, objectCount=%d\n", root->m_data.size(), gc.getObjectListCount());
            getchar();
            //gc.changeGCColor(t1);
        }

        gc.incrementalGC(1);
        printf("i=%d\n", i);
    }
    printf("root size=%d, objectCount=%d\n", root->m_data.size(), gc.getObjectListCount());
}

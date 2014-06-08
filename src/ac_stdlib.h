/* see copyright notice in aclang.h */

#ifndef AC_STDLIB_H
#define AC_STDLIB_H

#include "ac_config.h"

class acVM;

class acStdLib
{
public:
    acStdLib() {}
    ~acStdLib() {}
    
    static void bindStdFunctions(acVM* vm);
};

#endif // AC_STDLIB_H

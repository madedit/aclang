/* see copyright notice in aclang.h */

#include "ac_stdlib.h"
#include "ac_vm.h"
#include <iostream>

void ac_stdlib_showAST(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() > 0)
    {
        vm->setPrintAST(toBool(args->get(0), vm));
    }
}
void ac_stdlib_showIR(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() > 0)
    {
        vm->setPrintIR(toBool(args->get(0), vm));
    }
}
void ac_stdlib_showGC(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() > 0)
    {
        vm->setPrintGC(toBool(args->get(0), vm));
    }
}

void ac_stdlib_typeof(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: typeof() has no argument");

    vm->setUserFuncRetVar(getVarTypeStr(args->get(0)->m_valueType));
}

void ac_stdlib_print(acVariable* thisVar, acArray* args, acVM* vm)
{
    std::string str;
    std::string s;
    int count = args->size();
    for(int i = 0; i < count; ++i)
    {
        s = toString(args->get(i), vm);
        if(i == 0)
        {
            str = s;
        }
        else
        {
            str += "\t";
            str += s;
        }
    }
    std::cout << str << std::endl;
}

void ac_stdlib_tobool(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: tobool() has no argument");

    vm->setUserFuncRetVar(toBool(args->get(0), vm));
}

void ac_stdlib_toint32(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: toint32() has no argument");

    vm->setUserFuncRetVar(toInt32(args->get(0), vm));
}

void ac_stdlib_toint64(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: toint64() has no argument");

    vm->setUserFuncRetVar(toInt64(args->get(0), vm));
}

void ac_stdlib_tofloat(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: tofloat() has no argument");

    vm->setUserFuncRetVar(toFloat(args->get(0), vm));
}

void ac_stdlib_todouble(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: todouble() has no argument");

    vm->setUserFuncRetVar(toDouble(args->get(0), vm));
}

void ac_stdlib_tostr(acVariable* thisVar, acArray* args, acVM* vm)
{
    if(args->size() < 1)
        vm->runtimeError("Error: tostr() has no argument");

    vm->setUserFuncRetVar(toString(args->get(0), vm));
}

void acStdLib::bindStdFunctions(acVM* vm)
{
    vm->bindFunction("showAST", ac_stdlib_showAST);
    vm->bindFunction("showIR",  ac_stdlib_showIR);
    vm->bindFunction("showGC",  ac_stdlib_showGC);

    vm->bindFunction("typeof",   ac_stdlib_typeof);
    vm->bindFunction("print",    ac_stdlib_print);
    vm->bindFunction("tobool",   ac_stdlib_tobool);
    vm->bindFunction("toint32",  ac_stdlib_toint32);
    vm->bindFunction("toint64",  ac_stdlib_toint64);
    vm->bindFunction("tofloat",  ac_stdlib_tofloat);
    vm->bindFunction("todouble", ac_stdlib_todouble);
    vm->bindFunction("tostr",    ac_stdlib_tostr);
}

/* see copyright notice in aclang.h */

#include "ac_stdlib.h"
#include "ac_vm.h"
#include <iostream>

void ac_stdlib_printAST(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() > 0)
    {
        vm->setPrintAST(toBool(args->get(0), vm));
    }
}
void ac_stdlib_printIR(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() > 0)
    {
        vm->setPrintIR(toBool(args->get(0), vm));
    }
}
void ac_stdlib_printGC(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() > 0)
    {
        vm->setPrintGC(toBool(args->get(0), vm));
    }
}

void ac_stdlib_typeof(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: typeof() has no argument");
        return;
    }

    retVar->setValue(getVarTypeStr(args->get(0)->m_valueType).c_str(), vm);
}

void ac_stdlib_isfunction(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: typeof() has no argument");
        return;
    }

    std::string t = getVarTypeStr(args->get(0)->m_valueType);
    retVar->setValue(t == "function" || t == "userfunc");
}

void ac_stdlib_print(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    std::string str;
    int count = args->size();
    for(int i = 0; i < count; ++i)
    {
        if(i != 0)
        {
            str += "\t";
        }
        str += toString(args->get(i), vm);
    }
    vm->getMsgHandler()->output("%s\n", str.c_str());
}

void ac_stdlib_tobool(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: tobool() has no argument");
        return;
    }

    retVar->setValue(toBool(args->get(0), vm));
}

void ac_stdlib_toint32(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: toint32() has no argument");
        return;
    }

    retVar->setValue(toInt32(args->get(0), vm));
}

void ac_stdlib_toint64(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: toint64() has no argument");
        return;
    }

    retVar->setValue(toInt64(args->get(0), vm));
}

void ac_stdlib_tofloat(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: tofloat() has no argument");
        return;
    }

    retVar->setValue(toFloat(args->get(0), vm));
}

void ac_stdlib_todouble(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: todouble() has no argument");
        return;
    }

    retVar->setValue(toDouble(args->get(0), vm));
}

void ac_stdlib_tostr(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: tostr() has no argument");
        return;
    }

    retVar->setValue(toString(args->get(0), vm).c_str(), vm);
}

void ac_stdlib_bindfunc(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 2)
    {
        vm->runtimeError("Error: bindfunc() must has two arguments");
        return;
    }

    acVariable* tab0 = args->get(0);
    acVariable* tab1 = args->get(1);

    if(tab0->m_valueType != acVT_TABLE)
    {
        vm->runtimeError("Error: bindfunc(): args[0] must be a table");
        return;
    }

    if(tab1->m_valueType != acVT_TABLE)
    {
        vm->runtimeError("Error: bindfunc(): args[1] must be a table");
        return;
    }

    tab0->toTable()->bindFunc(tab1->toTable(), vm);
}

void ac_stdlib_clone(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: clone() has no argument");
        return;
    }

    args->get(0)->cloneTo(retVar, vm);
}

void ac_stdlib_inherit(acVariable* thisVar, acArray* args, acVariable* retVar, acVM* vm)
{
    if(args->size() < 1)
    {
        vm->runtimeError("Error: inherit() has no argument");
        return;
    }

    //check type
    for(int i = 0; i < args->size(); ++i)
    {
        acVariable* var = args->get(i);
        if(var->m_valueType != acVT_TABLE)
        {
            vm->runtimeError("Error: inherit(): all of args must be tables");
            return;
        }
    }

    //clone first table
    args->get(0)->cloneTo(retVar, vm);
    acTable* retTab = retVar->toTable();

    //copy all the other tables
    for(int i = 1; i < args->size(); ++i)
    {
        acTable* tab = args->get(i)->toTable();
        tab->copyDataTo(retTab, vm);
    }
}

void acStdLib::bindStdFunctions(acVM* vm)
{
    vm->bindFunction("printAST",    ac_stdlib_printAST);
    vm->bindFunction("printIR",     ac_stdlib_printIR);
    vm->bindFunction("printGC",     ac_stdlib_printGC);

    vm->bindFunction("typeof",      ac_stdlib_typeof);
    vm->bindFunction("isfunction",  ac_stdlib_isfunction);

    vm->bindFunction("print",       ac_stdlib_print);
    vm->bindFunction("tobool",      ac_stdlib_tobool);
    vm->bindFunction("toint32",     ac_stdlib_toint32);
    vm->bindFunction("toint64",     ac_stdlib_toint64);
    vm->bindFunction("tofloat",     ac_stdlib_tofloat);
    vm->bindFunction("todouble",    ac_stdlib_todouble);
    vm->bindFunction("tostr",       ac_stdlib_tostr);

    vm->bindFunction("bindfunc",    ac_stdlib_bindfunc);
    vm->bindFunction("clone",       ac_stdlib_clone);
    vm->bindFunction("inherit",     ac_stdlib_inherit);
}

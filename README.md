AC-Lang
-------

A simple C-like dynamic Language

Language Syntax
===============

    function fib(n)
    {
        local a = 1;
        local b = 1;
        for(local i = 3; i <= n ; ++i)
        {
            local c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
    var table = { n = 10 };
    var table.f = fib;
    print( "fib(10)=" + table.f(table.n) );

Feature
=======
- C-like syntax
- dynamic typing
- incremental GC
- all variables must be declared before they are used (by **var** or **local**)

How to Build
============

Required tools & libs:

1. llvm 3.4
2. cmake 2.8

ACLang can be built on Linux or Windows

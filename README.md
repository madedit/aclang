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

    local array = [ function(a, b){ print(a, b); }, 1, 3, 5 ];
    foreach(local i,v in array)
    {
        if(typeof(v) == "function")
        {
            var ::func = v; //store 'v' in global ::func
        }
        else
        {
            ::func(i, v);
        }
    }

Feature
=======
- C-like syntax
- dynamic typing
- first-class function
- closure
- incremental GC
- all variables must be declared before they are used (by **var** or **local**)

How to Build
============

Required tools & libs:

1. llvm 3.4
2. cmake 2.8

ACLang can be built on Linux and Windows


Todo
====

**bindfunc** feature. You can bind function to any variable. Sample code as below:

    //operator overload    
    var t1 = { i = 10 }, t2 = { i = 20 };
    bindfunc( t1, "_add", function(a, b) { return a.i + b.i; } )
    var result = t1 + t2; //op '+' call the bound "_add" function

    //sequence functions calling
    var str = "this is a string";
    bindfunc( str, "encode", function(encoding) { return this; } );
    bindfunc( str, "decode", function(encoding) { return this; } );
    str.decode("utf8").encode("big5");

AC-Lang
=======

A simple C-like dynamic Language.

Feature
=======
- C-like syntax
- dynamic typing
- first-class function
- closure
- all variables must be declared before they are used (by **var** or **local**)
- incremental GC (won't freeze the world)
- easy to bind C/C++ functions
- support Universal Character as variable name (e.g. **var 變數 = 10; print(變數);** )
- support JSON format natively

Language Syntax
---------------
```javascript
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
```
```javascript
local array = [ function(a, b){ print(a, b); }, 1, 3, 5 ];
for(local i,v : array)
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
```
```javascript
//closure
function newCounter()
{
    local i = 0;
    return function () {   // anonymous function
        ++i;
        return i;
    }
}

var c1 = newCounter();
print(c1());  //--> 1
print(c1());  //--> 2
```
```javascript
//support JSON format natively
var json = {
"firstName": "John",
"lastName": "Smith",
"isAlive": true,
"age": 25,
"height_cm": 167.6,
"address": {
    "streetAddress": "21 2nd Street",
    "city": "New York",
    "state": "NY",
    "postalCode": "10021-3100"
},
"phoneNumbers": [
    {
    "type": "home",
    "number": "212 555-1234"
    },
    {
    "type": "office",
    "number": "646 555-4567"
    }
]
};
print(json.phoneNumbers[0].number);
```
```javascript
//bindfunc
var t1 = { s = "abc" };
var t2 = { s = "qwe" };
var funcs = {
    _add = function(a, b) //operator+
    {
        return a.s + b.s;
    }
};
::bindfunc(t1, funcs);

print( t1+t2 ); //--> "abcqwe"
```

Download
========

You can download the pre-build executable file (Win32) from SourceForge:
[http://sourceforge.net/projects/aclang/files/?source=navbar](http://sourceforge.net/projects/aclang/files/?source=navbar)

How to Build
============

Required tools & libs:

1. llvm 3.5
2. cmake 2.8

ACLang can be built on Linux and Windows.

License
======
MIT License

Author
======
**Alston Chen**

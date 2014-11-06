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
function fib(n) //create function 'fib' in root-table
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
var table = { n = 10 }; //create 'table' in root-table
var table.f = fib;      //create 'f' in 'table'
print( "fib(10)=" + table.f(table.n) );
```
```javascript
//create a local variable 'array'
local array = [ function(a, b){ print(a, b); }, 1, 3, 5 ];
for(local i,v : array)
{
    if(typeof(v) == "function")
    {
        //create 'func' in global scope (root-table)
        var ::func = v;
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
    return function () { // anonymous function
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
```javascript
// new, clone(), inherit()
var A =
{
    i = 0,
    f = function(){print("A:"+i);},
};
::bindfunc(A,
{
    _new = function(v)
    {
        //print("op new()")
        i = v;
    },
    _add = function(lhs, rhs)
    {
        //print("op+");
        local v = ::clone(lhs);
        v.i += rhs.i;
        return v;
    },
    _sub = function(lhs, rhs) { print("op-"); },
    _mul = function(lhs, rhs) { print("op*"); },
    _div = function(lhs, rhs) { print("op/"); },
    _mod = function(lhs, rhs) { print("op%"); },
});

//B inherit from A, and then override function 'f'
var B = ::inherit(A, 
{
    f = function(){print("B:"+i);},
});

var a = new A(5), b = new B(10);
var c = a+b;

a.f(); //--> "A:5"
b.f(); //--> "B:10"
c.f(); //--> "A:15"
```
```javascript
//delete a element in a table
var t = { a = 1, b = 2, c = 3 };
print(">>> t =");
for(local i,v : t) print(i, v);

delete t.b; // delete 'b' in 't'
print(">>> t =");
for(local i,v : t) print(i, v);

delete t; // delete 't' in root-table
print(">>> roottable =");
//print elements in root-table (this-table)
for(local i,v : this) print(i, v);
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

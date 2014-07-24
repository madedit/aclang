/*
This library is distributed under the MIT License:
[http://opensource.org/licenses/mit-license.php]

AC-Lang Programming Library
Copyright (c) 2013-2014 Alston Chen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef ACLANG_H
#define ACLANG_H

#include <llvm/Support/DataTypes.h>

typedef int8_t      acInt8;
typedef uint8_t     acUInt8;
typedef int16_t     acInt16;
typedef uint16_t    acUInt16;
typedef int32_t     acInt32;
typedef uint32_t    acUInt32;
typedef int64_t     acInt64;
typedef uint64_t    acUInt64;

typedef float       acFloat;
typedef double      acDouble;

//typedef acUInt8     acBool;
//typedef acInt8      acByte;
//typedef acUInt8     acUbyte;
//typedef acInt16     acShort;
//typedef acUInt16    acUshort;
//typedef acInt32     acInt;
//typedef acUInt32    acUInt;
//typedef acInt64     acLong;
//typedef acUInt64    acUlong;
typedef acUInt8     acChar;
typedef acUInt16    acWchar;
typedef acUInt32    acDchar;

//typedef size_t      acPointer;

#endif //ACLANG_H

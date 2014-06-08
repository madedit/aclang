/* see copyright notice in aclang.h */

#ifndef AC_TOKEN_H
#define AC_TOKEN_H

#include "ac_utility.h"
#include "ac_utf.h"

struct acToken
{
    int         m_type;//yytokentype//acTokenType
    acChar*     m_begin;
    acChar*     m_end;
    int         m_beginLine;
    int         m_endLine;

    union
    {
        acDchar     m_charValue;
        acUInt64    m_integerValue;
        acDouble    m_doubleValue;
        struct
        {
            acDcharVector* m_string;
            acChar m_postfix;
        };
    };

    std::string getRawString()
    {
        return std::string(m_begin, m_end);
    }

    std::string toUTF8String()
    {
        std::string s;
        dcVecToUTF8Str(*m_string, s);
        return s;
    }
};

#endif //AC_TOKEN_H

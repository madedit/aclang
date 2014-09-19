/* see copyright notice in aclang.h */

#include "ac_lexer.h"
#include "ac_utf.h"
#include "ac_unichar.h"
#include "ac_msghandler.h"
#include <string>
#include <errno.h>
#include <stdlib.h>

namespace {

struct acKeyword
{
    const char *name;
    acTokenType type;
};

acKeyword bKeywords[] =
{
    "base",             TOK_BASE,
    "break",            TOK_BREAK,
};
const int bKeywords_count = sizeof(bKeywords) / sizeof(bKeywords[0]);

acKeyword cKeywords[] =
{
    "case",             TOK_CASE,
    "catch",            TOK_CATCH,
    "const",            TOK_CONST,
    "continue",         TOK_CONTINUE,
};
const int cKeywords_count = sizeof(cKeywords) / sizeof(cKeywords[0]);

acKeyword dKeywords[] =
{
    "default",          TOK_DEFAULT,
    "delegate",         TOK_DELEGATE,
    "delete",           TOK_DELETE,
    "do",               TOK_DO,
};
const int dKeywords_count = sizeof(dKeywords) / sizeof(dKeywords[0]);

acKeyword eKeywords[] =
{
    "else",             TOK_ELSE,
    "enum",             TOK_ENUM,
    "extends",          TOK_EXTENDS,
};
const int eKeywords_count = sizeof(eKeywords) / sizeof(eKeywords[0]);

acKeyword fKeywords[] =
{
    "false",            TOK_FALSE,
    "for",              TOK_FOR,
    "foreach",          TOK_FOREACH,
    "function",         TOK_FUNCTION,
};
const int fKeywords_count = sizeof(fKeywords) / sizeof(fKeywords[0]);

acKeyword iKeywords[] =
{
    "if",               TOK_IF,
    "in",               TOK_IN,
    "int",              TOK_INT,
};
const int iKeywords_count = sizeof(iKeywords) / sizeof(iKeywords[0]);

acKeyword lKeywords[] =
{
    "local",            TOK_LOCAL,
};
const int lKeywords_count = sizeof(lKeywords) / sizeof(lKeywords[0]);

acKeyword mKeywords[] =
{
    "metafunction",     TOK_METAFUNCTION,
};
const int mKeywords_count = sizeof(mKeywords) / sizeof(mKeywords[0]);

acKeyword nKeywords[] =
{
    "namespace",        TOK_NAMESPACE,
    "new",              TOK_NEW,
    "null",             TOK_NULL,
};
const int nKeywords_count = sizeof(nKeywords) / sizeof(nKeywords[0]);

acKeyword rKeywords[] =
{
    "resume",           TOK_RESUME,
    "return",           TOK_RETURN,
};
const int rKeywords_count = sizeof(rKeywords) / sizeof(rKeywords[0]);

acKeyword sKeywords[] =
{
    "switch",           TOK_SWITCH,
};
const int sKeywords_count = sizeof(sKeywords) / sizeof(sKeywords[0]);

acKeyword tKeywords[] =
{
    "this",             TOK_THIS,
    "throw",            TOK_THROW,
    "true",             TOK_TRUE,
    "try",              TOK_TRY,
//    "typeof",           TOK_TYPEOF,
};
const int tKeywords_count = sizeof(tKeywords) / sizeof(tKeywords[0]);

acKeyword vKeywords[] =
{
    "var",              TOK_VAR,
};
const int vKeywords_count = sizeof(vKeywords) / sizeof(vKeywords[0]);

acKeyword wKeywords[] =
{
    "while",            TOK_WHILE,
};
const int wKeywords_count = sizeof(wKeywords) / sizeof(wKeywords[0]);

acKeyword yKeywords[] =
{
    "yield",            TOK_YIELD,
};
const int yKeywords_count = sizeof(yKeywords) / sizeof(yKeywords[0]);

acKeyword stKeywords[] = {
    // special tokens
    "__EOF__",          TOK_EOF,
    "__FILE__",         STOK_FILE,
    "__LINE__",         STOK_LINE,
    "__DATE__",         STOK_DATE,
    "__TIME__",         STOK_TIME,
    "__TIMESTAMP__",    STOK_TIMESTAMP,
    "__VENDOR__",       STOK_VENDOR,
    "__VERSION__",      STOK_VERSION,
};
const int stKeywords_count = sizeof(stKeywords) / sizeof(stKeywords[0]);

int nameCmp(const acDchar *s1, const char *s2)
{
    int cmp;
    for(;;)
    {
        cmp = int(*s1) - int(*s2);
        if((cmp != 0) || (*s1 == 0) || (*s2 == 0))
        {
            break;
        }
        ++s1;
        ++s2;
    }
    return cmp;
}

acTokenType findTokenType(const acDchar *name, acKeyword* keywords, int count)
{
    for(int i=0; i<count; ++i, ++keywords)
    {
        int result = nameCmp(name + 1, (keywords->name) + 1);
        if(result == 0) return keywords->type;
        if(result < 0) break;
    }
    return TOK_IDENTIFIER;
}

acTokenType getTokenType(acDchar *name)
{
    switch(*name)
    {
    case '_': return findTokenType(name, stKeywords, stKeywords_count);
    case 'b': return findTokenType(name, bKeywords, bKeywords_count);
    case 'c': return findTokenType(name, cKeywords, cKeywords_count);
    case 'd': return findTokenType(name, dKeywords, dKeywords_count);
    case 'e': return findTokenType(name, eKeywords, eKeywords_count);
    case 'f': return findTokenType(name, fKeywords, fKeywords_count);
    case 'i': return findTokenType(name, iKeywords, iKeywords_count);
    case 'l': return findTokenType(name, lKeywords, lKeywords_count);
    case 'm': return findTokenType(name, mKeywords, mKeywords_count);
    case 'n': return findTokenType(name, nKeywords, nKeywords_count);
    case 'r': return findTokenType(name, rKeywords, rKeywords_count);
    case 's': return findTokenType(name, sKeywords, sKeywords_count);
    case 't': return findTokenType(name, tKeywords, tKeywords_count);
    case 'v': return findTokenType(name, vKeywords, vKeywords_count);
    case 'w': return findTokenType(name, wKeywords, wKeywords_count);
    case 'y': return findTokenType(name, yKeywords, yKeywords_count);
    }

    return TOK_IDENTIFIER;
}

#ifdef AC_DEBUG
const char* findTokenString(acTokenType type, acKeyword* keywords, int count)
{
    for(int i=0; i<count; ++i, ++keywords)
    {
        if(type == keywords->type) return keywords->name;
    }
    return 0;
}

const char* getTokenString0(acTokenType type)
{
    const char* str;
    str = findTokenString(type, stKeywords, stKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, bKeywords, bKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, cKeywords, cKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, dKeywords, dKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, eKeywords, eKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, fKeywords, fKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, iKeywords, iKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, mKeywords, mKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, nKeywords, nKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, rKeywords, rKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, sKeywords, sKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, tKeywords, tKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, vKeywords, vKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, wKeywords, wKeywords_count);
    if(str != 0) return str;
    str = findTokenString(type, yKeywords, yKeywords_count);
    if(str != 0) return str;
    
    return 0;
}
#endif

}//namespace

const char* getTokenString(acTokenType type)
{
    switch(type)
    {
    case TOK_DIV:        return "/";
    case TOK_DIVASS:     return "/=";
    case TOK_DOT:        return ".";
    case TOK_DOTDOT:     return "..";
    case TOK_DOTDOTDOT:  return "...";
    case TOK_AND:        return "&";
    case TOK_ANDASS:     return "&=";
    case TOK_ANDAND:     return "&&";
    case TOK_OR:         return "|";
    case TOK_ORASS:      return "|=";
    case TOK_OROR:       return "||";
    case TOK_MINUS:      return "-";
    case TOK_MINUSASS:   return "-=";
    case TOK_MINUSMINUS: return "--";
    case TOK_PLUS:       return "+";
    case TOK_PLUSASS:    return "+=";
    case TOK_PLUSPLUS:   return "++";
    case TOK_LT:         return "<";
    case TOK_LE:         return "<=";
    case TOK_SHL:        return "<<";
    case TOK_SHLASS:     return "<<=";
    case TOK_LG:         return "<>";
    case TOK_LEG:        return "<>=";
    case TOK_GT:         return ">";
    case TOK_GE:         return ">=";
    case TOK_SHRASS:     return ">>=";
    case TOK_USHRASS:    return ">>>=";
    case TOK_SHR:        return ">>";
    case TOK_USHR:       return ">>>";
    case TOK_NOT:        return "!";
    case TOK_NOTEQUAL:   return "!=";
    case TOK_UE:         return "!<>";
    case TOK_UNORD:      return "!<>=";
    case TOK_UGE:        return "!<";
    case TOK_UG:         return "!<=";
    case TOK_ULE:        return "!>";
    case TOK_UL:         return "!>=";
    case TOK_LPAREN:     return "(";
    case TOK_RPAREN:     return ")";
    case TOK_LBRACKET:   return "[";
    case TOK_RBRACKET:   return "]";
    case TOK_LCURLY:     return "{";
    case TOK_RCURLY:     return "}";
    case TOK_QUESTION:   return "?";
    case TOK_COMMA:      return ",";
    case TOK_SEMICOLON:  return ";";
    case TOK_COLON:      return ":";
    case TOK_COLONCOLON: return "::";
    case TOK_DOLLAR:     return "$";
    case TOK_ASSIGN:     return "=";
    case TOK_EQUAL:      return "==";
    case TOK_MUL:        return "*";
    case TOK_MULASS:     return "*=";
    case TOK_MOD:        return "%";
    case TOK_MODASS:     return "%=";
    case TOK_XOR:        return "^";
    case TOK_XORASS:     return "^=";
    case TOK_CAT:        return "~";
    case TOK_CATASS:     return "~=";
    }

    const char* str = ::getTokenString0(type);
    if(str != 0) return str;

    return "";
}

acLexer::acReturnType acLexer::next(acToken &token, acChar *bufferEnd)
{
    token.m_type = TOK_UNKNOWN;

    acChar* buf = token.m_begin;
    acChar ch;

    if(buf == bufferEnd)
    {
        token.m_type = TOK_EOF;
        token.m_end = bufferEnd;
        return RT_EOF;
    }

    ch = *buf;

    if(ch <= 0x20)
    {
        switch (ch)
        {
        // End of File
        case 0x00:
        case 0x1A:
            token.m_type = TOK_EOF;
            token.m_end = buf + 1;
            return RT_EOF;

        // End of Line
        case 0x0D:
            token.m_type = TOK_EOL;
            token.m_end = ++buf;
            ++token.m_endLine;
            if(buf != bufferEnd && *buf == 0x0A)
            {
                ++token.m_end;
            }
            return RT_OK;
        case 0x0A:
            token.m_type = TOK_EOL;
            token.m_end = buf + 1;
            ++token.m_endLine;
            return RT_OK;

        // White Space
        case 0x20:
        case 0x09:
        case 0x0B:
        case 0x0C:
            while( ++buf != bufferEnd &&
                ( (ch=*buf)==0x20 || ch==0x09 || ch==0x0B || ch==0x0C ) ) /* do nothing */ ;
            token.m_type = TOK_SPACE;
            token.m_end = buf;
            return RT_OK;

        // unsupported char
        default:
            token.m_end = buf + 1;
            m_msgHandler->error(token.m_endLine, "unsupported char 0x%02X", ch);
            return RT_ERROR;
        }
    }

    // Comments or '/' or '/='
    if(ch == '/')
    {
        if( ++buf == bufferEnd)
        {
            token.m_type = TOK_DIV;
            token.m_end = buf;
            return RT_OK;
        }

        ch = *buf;
        if(ch == '=')
        {
            token.m_type = TOK_DIVASS;
            token.m_end = buf + 1;
            return RT_OK;
        }

        switch (ch)
        {
        case '/':   // Line Comment
            while( ++buf != bufferEnd &&
                ( (ch=*buf)!=0x0D && ch!=0x0A && ch!=0x00 && ch!=0x1A ) ) /* do nothing */ ;
            token.m_type = TOK_COMMENT;
            token.m_end = buf;
            return RT_OK;

        case '*':   // Block Comment
            token.m_type = TOK_COMMENT;
            for(;;)
            {
                if(++buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
                {
                    token.m_end = buf;
                    break;
                }
                if(ch == 0x0D)
                {
                    ++token.m_endLine;
                    acChar *b = buf+1;
                    if(b != bufferEnd && (*b)==0x0A) ++buf;
                }
                else if(ch ==0x0A)
                {
                    ++token.m_endLine;
                }
                else if(ch == '*')
                {
                    acChar *b = buf + 1;
                    if(b != bufferEnd && *b == '/')
                    {
                        token.m_end = b + 1;
                        return RT_OK;
                    }
                }
            }
            m_msgHandler->error(token.m_endLine, "unterminated /* */ comment starting at line(%d)", token.m_beginLine);
            return RT_ERROR;

        case '+':   // Nesting Comment
            {
                token.m_type = TOK_COMMENT;
                int nesting = 1;
                for(;;)
                {
                    if(++buf == bufferEnd || (ch=*buf) == 0x00 || ch ==0x1A)
                    {
                        token.m_end = buf;
                        break;
                    }
                    if(ch == 0x0D)
                    {
                        ++token.m_endLine;
                        acChar *b = buf+1;
                        if(b != bufferEnd && (*b)==0x0A) ++buf;
                    }
                    else if(ch ==0x0A)
                    {
                        ++token.m_endLine;
                    }
                    else if(ch == '/')
                    {
                        if(++buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
                        {
                            token.m_end = buf;
                            break;
                        }
                        if(ch == '+')
                        {
                            ++nesting;
                            continue;
                        }
                    }
                    if(ch == '+')
                    {
                        if(++buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
                        {
                            token.m_end = buf;
                            break;
                        }
                        if(ch == '/')
                        {
                            if(--nesting == 0)
                            {
                                token.m_end = buf + 1;
                                return RT_OK;
                            }
                        }
                    }
                }
            }
            m_msgHandler->error(token.m_endLine, "unterminated /+ +/ comment starting at line(%d)", token.m_beginLine);
            return RT_ERROR;

        default:
            token.m_type = TOK_DIV;
            token.m_end = buf;
            return RT_OK;
        }
    }

    // String Literals
    if(ch == 'x' && (buf+1) != bufferEnd && *(buf+1) == '"')
    {
        m_strings.push_back( acDcharVector() );
        token.m_string = &(m_strings.back());
        token.m_postfix = 'c';
        token.m_type = TOK_STRING;
        return hexString(token, buf+2, bufferEnd);
    }
    if(ch == 'r' && (buf+1) != bufferEnd && *(buf+1) == '"')
    {
        m_strings.push_back( acDcharVector() );
        token.m_string = &(m_strings.back());
        token.m_postfix = 'c';
        token.m_type = TOK_STRING;
        return rawString(token, buf+2, bufferEnd, '"');
    }
    if(ch == '`')
    {
        m_strings.push_back( acDcharVector() );
        token.m_string = &(m_strings.back());
        token.m_postfix = 'c';
        token.m_type = TOK_STRING;
        return rawString(token, buf+1, bufferEnd, '`');
    }
    if(ch == '"')
    {
        m_strings.push_back( acDcharVector() );
        token.m_string = &(m_strings.back());
        token.m_postfix = 'c';
        token.m_type = TOK_STRING;
        return string(token, buf+1, bufferEnd);
    }

    // Character Literals
    if(ch == '\'')
    {
        token.m_type = TOK_CHAR;
        return dchar(token, buf+1, bufferEnd);
    }
    if(ch == '\\')
    {
        token.m_type = TOK_CHAR;
        return decodeEscapeSequence(0, token, buf+1, bufferEnd);
    }

    // Integer Literals and Floating Literals
    if(ch >= '0' && ch <='9')
    {
        return number(token, buf, bufferEnd);
    }
    if(ch == '.' && (buf+1) != bufferEnd)
    {
        acChar ch1 = *(buf + 1);
        if(ch1 >= '0' && ch1 <= '9')
        {
            return number(token, buf, bufferEnd);
        }
    }

    // Operators
    switch(ch)
    {
    case '.':
        token.m_type = TOK_DOT;
        if(++buf != bufferEnd && (*buf) == '.')
        {
            token.m_type = TOK_DOTDOT;
            if(++buf != bufferEnd && (*buf) == '.')
            {
                token.m_type = TOK_DOTDOTDOT;
                ++buf;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '&':
        token.m_type = TOK_AND;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=': token.m_type = TOK_ANDASS; ++buf; break;
            case '&': token.m_type = TOK_ANDAND; ++buf; break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '|':
        token.m_type = TOK_OR;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=': token.m_type = TOK_ORASS; ++buf; break;
            case '|': token.m_type = TOK_OROR; ++buf; break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '-':
        token.m_type = TOK_MINUS;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=': token.m_type = TOK_MINUSASS; ++buf; break;
            case '-': token.m_type = TOK_MINUSMINUS; ++buf; break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '+':
        token.m_type = TOK_PLUS;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=': token.m_type = TOK_PLUSASS; ++buf; break;
            case '+': token.m_type = TOK_PLUSPLUS; ++buf; break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '<':
        token.m_type = TOK_LT;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=':
                token.m_type = TOK_LE;
                ++buf;
                break;
            case '<':
                token.m_type = TOK_SHL;
                if(++buf != bufferEnd && (*buf) == '=')
                {
                    token.m_type = TOK_SHLASS;
                    ++buf;
                }
                break;
            case '>':
                token.m_type = TOK_LG;
                if(++buf != bufferEnd && (*buf) == '=')
                {
                    token.m_type = TOK_LEG;
                    ++buf;
                }
                break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '>':
        token.m_type = TOK_GT;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=':
                token.m_type = TOK_GE;
                ++buf;
                break;
            case '>':
                token.m_type = TOK_SHR;
                if(++buf != bufferEnd)
                {
                    switch(*buf)
                    {
                    case '=':
                        token.m_type = TOK_SHRASS;
                        ++buf;
                        break;
                    case '>':
                        token.m_type = TOK_USHR;
                        if(++buf != bufferEnd && (*buf) == '=')
                        {
                            token.m_type = TOK_USHRASS;
                            ++buf;
                        }
                        break;
                    }
                }
                break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '!':
        token.m_type = TOK_NOT;
        if(++buf != bufferEnd)
        {
            switch(*buf)
            {
            case '=':
                token.m_type = TOK_NOTEQUAL;
                ++buf;
                break;
            case '<':
                token.m_type = TOK_UGE;
                if(++buf != bufferEnd)
                {
                    switch(*buf)
                    {
                    case '=':
                        token.m_type = TOK_UG;
                        ++buf;
                        break;
                    case '>':
                        token.m_type = TOK_UE;
                        if(++buf != bufferEnd && (*buf) == '=')
                        {
                            token.m_type = TOK_UNORD;
                            ++buf;
                        }
                        break;
                    }
                }
                break;
            case '>':
                token.m_type = TOK_ULE;
                if(++buf != bufferEnd && (*buf) == '=')
                {
                    token.m_type = TOK_UL;
                    ++buf;
                }
                break;
            }
        }
        token.m_end = buf;
        return RT_OK;

    case '(': token.m_type = TOK_LPAREN;    token.m_end = buf + 1; return RT_OK;
    case ')': token.m_type = TOK_RPAREN;    token.m_end = buf + 1; return RT_OK;
    case '[': token.m_type = TOK_LBRACKET;  token.m_end = buf + 1; return RT_OK;
    case ']': token.m_type = TOK_RBRACKET;  token.m_end = buf + 1; return RT_OK;
    case '{': token.m_type = TOK_LCURLY;    token.m_end = buf + 1; return RT_OK;
    case '}': token.m_type = TOK_RCURLY;    token.m_end = buf + 1; return RT_OK;
    case '?': token.m_type = TOK_QUESTION;  token.m_end = buf + 1; return RT_OK;
    case ',': token.m_type = TOK_COMMA;     token.m_end = buf + 1; return RT_OK;
    case ';': token.m_type = TOK_SEMICOLON; token.m_end = buf + 1; return RT_OK;

    case ':':
        token.m_type = TOK_COLON;
        if(++buf != bufferEnd && (*buf) == ':')
        {
            token.m_type = TOK_COLONCOLON;
            ++buf;
        }
        token.m_end = buf;
        return RT_OK;

    case '$': token.m_type = TOK_DOLLAR;    token.m_end = buf + 1; return RT_OK;

    case '=':
        token.m_type = TOK_ASSIGN;
        if(++buf != bufferEnd && (*buf) == '=')
        {
            token.m_type = TOK_EQUAL;
            ++buf;
        }
        token.m_end = buf;
        return RT_OK;

    case '*':
        token.m_type = TOK_MUL;
        if(++buf != bufferEnd && (*buf) == '=')
        {
            token.m_type = TOK_MULASS;
            ++buf;
        }
        token.m_end = buf;
        return RT_OK;

    case '%':
        token.m_type = TOK_MOD;
        if(++buf != bufferEnd && (*buf) == '=')
        {
            token.m_type = TOK_MODASS;
            ++buf;
        }
        token.m_end = buf;
        return RT_OK;

    case '^':
        token.m_type = TOK_XOR;
        if(++buf != bufferEnd && (*buf) == '=')
        {
            token.m_type = TOK_XORASS;
            ++buf;
        }
        token.m_end = buf;
        return RT_OK;

    case '~':
        token.m_type = TOK_CAT;
        if(++buf != bufferEnd && (*buf) == '=')
        {
            token.m_type = TOK_CATASS;
            ++buf;
        }
        token.m_end = buf;
        return RT_OK;
    }

    // Keywords or Identifiers
    acDcharVector word;
    acDchar dch = ch;
    do
    {
        int len = UTF8ToDchar(buf, int(bufferEnd - buf), dch);
        if(len == 0)
        {
            token.m_end = buf;
            m_msgHandler->error(token.m_endLine, "invalid UTF-8 sequence");
            return RT_ERROR;
        }

        if(dch == 0xFEFB)//Unicode BOM
        {
            token.m_end = buf + len;
            token.m_type = TOK_SPACE;
            return RT_OK;
        }

        if((dch <= 'z' && dch >= 'a') ||
            (dch <= 'Z' && dch >= 'A') ||
            (dch <= '9' && dch >= '0') ||
            dch == '_'
#if AC_USE_UNICHAR
            || isUniversalChar(dch)
#endif //AC_USE_UNICHAR
            )
        {
            word.push_back(*buf++);
            if(--len > 0)
            {
                do
                {
                    word.push_back(*buf++);
                }
                while(--len > 0);
            }
        }
        else
        {
            break;
        }
    }
    while(buf != bufferEnd);

    token.m_end = buf;
    if(word.size() == 0)
    {
        m_msgHandler->error(token.m_endLine, "unsupported char 0x%X", dch);
        return RT_ERROR;
    }

    word.push_back('\0');
    token.m_type = getTokenType(&word.front());

    return RT_OK;
}

acLexer::acReturnType acLexer::hexString(acToken &token, acChar *buf, acChar *bufferEnd)
{
    bool high = false; // low or high nibble of a char
    acChar highNibble;

    acChar ch;
    for(;;)
    {
        if(buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
        {
            token.m_end = buf;
            m_msgHandler->error(token.m_endLine, "unterminated string constant starting at line(%d)", token.m_beginLine);
            return RT_ERROR;
        }

        ++buf;
        switch(ch)
        {
        case '"':
            if(high==true)
            {
                token.m_end = buf;
                m_msgHandler->error(token.m_endLine, "odd number of hex characters in hex string");
                return RT_ERROR;
            }

            if(buf != bufferEnd)
            {
                switch(*buf)
                {
                case 'c':
                    token.m_postfix = 'c';
                    ++buf;
                    break;
                case 'w':
                    token.m_postfix = 'w';
                    ++buf;
                    break;
                case 'd':
                    token.m_postfix = 'd';
                    ++buf;
                    break;
                }
            }
            token.m_end = buf;
            return RT_OK;

        case 0x0D:
            if(buf != bufferEnd && (*buf)==0x0A) ++buf;
        case 0x0A:
            ++token.m_endLine;
            continue;

        // White Space
        case 0x20:
        case 0x09:
        case 0x0B:
        case 0x0C:
            /* do nothing */
            continue;

        default:
            {
                int ret = toHex(ch, token.m_endLine, false);
                if(ret != RT_OK)
                {
                    switch(ret)
                    {
                    case RT_ERROR:
                        m_msgHandler->error(token.m_endLine, "non-hex character '%c'", ch);
                        break;
                    case RT_ERROR2:
                         m_msgHandler->error(token.m_endLine, "unterminated hex string constant starting at line(%d)", token.m_beginLine);
                        break;
                    }
                    token.m_end = buf;
                    return RT_ERROR;
                }
            }
            break;
        }

        if(high)
        {
            ch = highNibble | ch;
            token.m_string->push_back(ch);
            high = false;
        }
        else
        {
            highNibble = ch << 4;
            high = true;
        }
    }
    return RT_ERROR;
}

acLexer::acReturnType acLexer::rawString(acToken &token, acChar *buf, acChar *bufferEnd,
    acChar endChar)
{
    acChar ch;
    for(;;)
    {
        if(buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
        {
            token.m_end = buf;
            m_msgHandler->error(token.m_endLine, "unterminated string constant starting at line(%d)", token.m_beginLine);
            return RT_ERROR;
        }

        ++buf;
        if(ch == 0x0D)
        {
            token.m_string->push_back(0x0D);
            ++token.m_endLine;
            acChar *b = buf+1;
            if(b != bufferEnd && (*b)==0x0A)
            {
                token.m_string->push_back(0x0A);
                ++buf;
            }
        }
        else if(ch == 0x0A)
        {
            token.m_string->push_back(0x0A);
            ++token.m_endLine;
        }
        else if(ch == endChar)
        {
            if(buf != bufferEnd)
            {
                switch(*buf)
                {
                case 'c':
                    token.m_postfix = 'c';
                    ++buf;
                    break;
                case 'w':
                    token.m_postfix = 'w';
                    ++buf;
                    break;
                case 'd':
                    token.m_postfix = 'd';
                    ++buf;
                    break;
                }
            }
            token.m_end = buf;
            return RT_OK;
        }
        else
        {
            acDchar dch;
            int len = decodeUTF8(dch, token, buf - 1, bufferEnd);
            if(len <= 0)
            {
                return RT_ERROR;
            }
            buf = token.m_end;
        }
    }
    return RT_ERROR;
}

acLexer::acReturnType acLexer::string(acToken &token, acChar *buf, acChar *bufferEnd)
{
    acChar ch;
    for(;;)
    {
        if(buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
        {
            token.m_end = buf;
            m_msgHandler->error(token.m_endLine, "unterminated string constant starting at line(%d)", token.m_beginLine);
            return RT_ERROR;
        }

        ++buf;
        if(ch == 0x0D)
        {
            token.m_string->push_back(0x0D);
            ++token.m_endLine;
            acChar *b = buf+1;
            if(b != bufferEnd && (*b)==0x0A)
            {
                token.m_string->push_back(0x0A);
                ++buf;
            }
        }
        else if(ch == 0x0A)
        {
            token.m_string->push_back(0x0A);
            ++token.m_endLine;
        }
        else if(ch == '"')
        {
            if(buf != bufferEnd)
            {
                switch(*buf)
                {
                case 'c':
                    token.m_postfix = 'c';
                    ++buf;
                    break;
                case 'w':
                    token.m_postfix = 'w';
                    ++buf;
                    break;
                case 'd':
                    token.m_postfix = 'd';
                    ++buf;
                    break;
                }
            }
            token.m_end = buf;
            return RT_OK;
        }
        else if(ch == '\\')
        {
            acDchar dch;
            if(decodeEscapeSequence(&dch, token, buf, bufferEnd) != RT_OK)
            {
                return RT_ERROR;
            }

            acChar utf8_str[5];
            int len = dcharToUTF8(dch, utf8_str);

            if(len == 0)
            {
                m_msgHandler->error(token.m_endLine, "invalid UTF character \\U%08x", dch);
                return RT_ERROR;
            }

            for(int i=0; i<len; ++i)
            {
                token.m_string->push_back(utf8_str[i]);
            }

            buf = token.m_end;
        }
        else
        {
            acDchar dch;
            int len = decodeUTF8(dch, token, buf - 1, bufferEnd);
            if(len <= 0)
            {
                return RT_ERROR;
            }
            buf = token.m_end;
        }
    }

    return RT_OK;
}

acLexer::acReturnType acLexer::dchar(acToken &token, acChar *buf, acChar *bufferEnd)
{
    acChar ch;
    if(buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A || ch == 0x0D || ch == 0x0A)
    {
        token.m_end = buf;
        m_msgHandler->error(token.m_endLine, "unterminated character constant");
        return RT_ERROR;
    }

    if(ch == '\\')
    {
        if(decodeEscapeSequence(0, token, ++buf, bufferEnd) < 0)
        {
            return RT_ERROR;
        }
    }
    else
    {
        int len = decodeUTF8(token.m_charValue, token, buf, bufferEnd);
        if(len <= 0)
        {
            return RT_ERROR;
        }
    }

    buf = token.m_end;
    if(buf == bufferEnd || (*buf) != '\'')
    {
        token.m_end = buf;
        m_msgHandler->error(token.m_endLine, "unterminated character constant");
        return RT_ERROR;
    }

    ++token.m_end;
    return RT_OK;
}

acLexer::acReturnType acLexer::number(acToken &token, acChar *buf, acChar *bufferEnd)
{
    acChar ch = *buf++;
    acChar ch1;
    acCharVector num;

    if(buf == bufferEnd || (ch1=*buf)==0x00 || ch1 == 0x1A)
    {
        token.m_end = bufferEnd;
        num.push_back(ch);
        return strToDecimal(token, num);
    }

    int base = 10; // or 2 or 8 or 16
    acChar *ptrEnd;
    acCharVector hexFraction, hexExponent;
    if(ch == '0' && ch1 != 0)
    {
        switch(ch1)
        {
        case 'x': case 'X':
            base = 16;
            scanHexadecimal(buf+1, bufferEnd, &ptrEnd, num);
            break;
        case 'b': case 'B':
            base = 2;
            scanDecimal(buf+1, bufferEnd, &ptrEnd, num);
            break;
        default:
            base = 8;
            scanDecimal(buf, bufferEnd, &ptrEnd, num);
            break;
        }
    }
    else // '1' ~ '9' or '.'
    {
        num.push_back(ch);
        scanDecimal(buf, bufferEnd, &ptrEnd, num);
    }

    if(ptrEnd == bufferEnd || (ch1=*ptrEnd) == 0x00 || ch1 == 0x1A)
    {
        ch1 = 0;
    //    token.m_end = ptrEnd;
    //    m_msgHandler->error(token.m_endLine, "semicolon expected, not 'EOF'");
    //    return RT_ERROR;
    }

    if(ch1 == 'e' || ch1 == 'E') // decimal exponent
    {
        if(base == 2)
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "binary digit expected, not '%c'", ch1);
            return RT_ERROR;
        }
        if(base == 8) base = 10;
        ch = '.';
    }
    else if(ch1 == 'p' || ch1 == 'P') // hex exponent
    {
        if(base != 16)
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "digit expected, not '%c'", ch1);
            return RT_ERROR;
        }
        ch = '.';
    }
    else if(ch1 == '.') // scan FP fraction
    {
        if(ch == '.')
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "semicolon expected, not '.'");
            return RT_ERROR;
        }

        ch = '.';
        switch(base)
        {
        case 16:
            scanHexadecimal(ptrEnd + 1, bufferEnd, &ptrEnd, hexFraction);
            break;
        case 8:
        case 10:
            base = 10;
            if(num.size() == 0) num.push_back('0');
            num.push_back('.');
            scanDecimal(ptrEnd + 1, bufferEnd, &ptrEnd, num);
            break;
        default:
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "binary digit expected, not '.'");
            return RT_ERROR;
        }

        if(ptrEnd == bufferEnd || (ch1=*ptrEnd) == 0x00 || ch1 == 0x1A)
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "semicolon expected, not 'EOF'");
            return RT_ERROR;
        }
    }
    else if(ch1 == 'f' || ch1 == 'F')
    {
        token.m_type = TOK_FLOAT32;
        ch = '.';
    }

    if(ch == '.')
    {
        switch(ch1) // scan FP exponent
        {
        case 'e': case 'E':
        case 'p': case 'P':
            if(++ptrEnd != bufferEnd)
            {
                if(base != 16)
                {
                    if(num.size() == 0) num.push_back('0');
                    num.push_back(ch1);
                }

                ch1 = *ptrEnd;
                switch(ch1)
                {
                case '+': case '-':
                    if(base == 16) hexExponent.push_back(ch1);
                    else           num.push_back(ch1);
                    ++ptrEnd;
                    break;
                }

                if(ptrEnd != bufferEnd)
                {
                    buf = ptrEnd;
                    if(base == 16) scanDecimal(ptrEnd, bufferEnd, &ptrEnd, hexExponent);
                    else           scanDecimal(ptrEnd, bufferEnd, &ptrEnd, num);

                    if(buf == ptrEnd)
                    {
                        token.m_end = ptrEnd;
                        m_msgHandler->error(token.m_endLine, "exponent expected");
                        return RT_ERROR;
                    }
                }
            }
            break;
        }

        if(ptrEnd == bufferEnd || (ch1=*ptrEnd) == 0x00 || ch1 == 0x1A)
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "semicolon expected, not 'EOF'");
            return RT_ERROR;
        }

        switch(ch1)
        {
        case 'f': case 'F':
            token.m_type = TOK_FLOAT32;
            if(++ptrEnd == bufferEnd || (ch1=*ptrEnd) == 0x00 || ch1 == 0x1A)
            {
                token.m_end = ptrEnd;
                m_msgHandler->error(token.m_endLine, "semicolon expected, not 'EOF'");
                return RT_ERROR;
            }
            break;
        }

        if(!isDelimiter(ch1))
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "bad suffix on number, unexpected char '%c'", ch1);
            return RT_ERROR;
        }

        if(token.m_type != TOK_FLOAT32) token.m_type = TOK_FLOAT64;
        token.m_end = ptrEnd;
        if(base == 10)
        {
            num.push_back('\0');
            const char *pbeg = (const char *)&(num.front());
            char *pend;
            token.m_doubleValue = strtod(pbeg, &pend);

            if(errno != 0)
            {
                m_msgHandler->error(token.m_endLine, "number is not representable");
                return RT_ERROR;
            }

            if(pend != pbeg + num.size() - 1)
            {
                m_msgHandler->error(token.m_endLine, "'%s' is not floating point number", pbeg);
                return RT_ERROR;
            }
        }
        else // base == 16
        {
            if(hexExponent.size() == 0)
            {
                m_msgHandler->error(token.m_endLine, "binary-exponent-part required");
                return RT_ERROR;
            }

            if(hexToDouble(token, num, hexFraction, hexExponent) != RT_OK)
            {
                m_msgHandler->error(token.m_endLine, "number is not representable");
                return RT_ERROR;
            }
        }

        return RT_OK;
    }
    else // integer
    {
        switch(ch1) // suffix
        {
        case 'u':
        case 'U':
            token.m_type = TOK_UNS32;
            if(++ptrEnd != bufferEnd && ((ch1=*ptrEnd) == 'l' || ch1 == 'L'))
            {
                token.m_type = TOK_UNS64;
                if(++ptrEnd != bufferEnd)
                {
                    ch1 = *ptrEnd;
                }
            }
            break;
        case 'l':
        case 'L':
            token.m_type = TOK_UNS64;
            if(++ptrEnd != bufferEnd && ((ch1=*ptrEnd) == 'u' || ch1 == 'U'))
            {
                if(++ptrEnd != bufferEnd)
                {
                    ch1 = *ptrEnd;
                }
            }
            break;
        }

        token.m_end = ptrEnd;

        //if(ptrEnd == bufferEnd || ch1 == 0x00 || ch1 == 0x1A)
        //{
        //    m_msgHandler->error(token.m_endLine, "semicolon expected, not 'EOF'");
        //    return RT_ERROR;
        //}

        //if(ch1 == 'l')
        //{
        //    m_msgHandler->error(token.m_endLine, "'l' suffix is deprecated, use 'L' instead");
        //    return RT_ERROR;
        //}

        if(!isDelimiter(ch1))
        {
            token.m_end = ptrEnd;
            m_msgHandler->error(token.m_endLine, "bad suffix on number, unexpected char '%c'", ch1);
            return RT_ERROR;
        }

        switch(base)
        {
        case 2: return strToBinary(token, num);
        case 8: return strToOctal(token, num);
        case 10: return strToDecimal(token, num);
        case 16: return strToHexadecimal(token, num);
        }
    }

    return RT_OK;
}

acLexer::acReturnType acLexer::hexToDouble(acToken &token, acCharVector &integer,
    acCharVector &fraction, acCharVector &exponent)
{
    acUInt64 intv = 0, frav = 0;

    exponent.push_back('\0');
    int exp = strtol((const char *)&(exponent.front()), 0, 10);
    if(errno != 0)
        return RT_ERROR;

    if(integer.size() != 0)
    {
        if(hexToInteger(&(integer.front()), int(integer.size()), intv) != RT_OK)
            return RT_ERROR;
    }

    if(fraction.size() != 0)
    {
        if(hexToFraction(&(fraction.front()), int(fraction.size()), frav) != RT_OK)
            return RT_ERROR;
    }

    if(intv == 0)
    {
         if(frav == 0)
         {
            token.m_doubleValue = 0;
            return RT_OK;
         }

         do
         {
            intv <<= 1;
            if((frav & 0x8000000000000000ULL) != 0) ++intv;
            frav <<= 1;
            --exp;
         }
         while(intv == 0);
    }
    else // intv > 0
    {
        while(intv > 1)
        {
            frav >>= 1;
            if((((unsigned int)intv) & 1) != 0) frav |= 0x8000000000000000ULL;
            intv >>= 1;
            ++exp;
        };
    }

    if(exp > 1024 || exp < -1023) return RT_ERROR;
    exp += 1023;

    acUInt64 *pv = (acUInt64*)(&token.m_doubleValue);
    (*pv) = exp;
    (*pv) <<= 52;
    frav >>= 12;
    (*pv) |= frav;

    return RT_OK;
}

acLexer::acReturnType acLexer::strToBinary(acToken &token, acCharVector &str)
{
    token.m_integerValue = 0;
    size_t len = str.size();
    if(len == 0)
    {
        m_msgHandler->error(token.m_endLine, "binary digit expected");
        return RT_ERROR;
    }

    acChar *ptr = &(str.front());
    for(size_t i=0; i<len; ++i, ++ptr)
    {
        switch(*ptr)
        {
        case '0':
            token.m_integerValue <<= 1;
            break;
        case '1':
            token.m_integerValue <<= 1;
            ++token.m_integerValue;
            break;
        default:
            m_msgHandler->error(token.m_endLine, "binary digit expected, not '%c'", *ptr);
            return RT_ERROR;
        }
    }

    determineIntType(token);
    return RT_OK;
}

acLexer::acReturnType acLexer::strToOctal(acToken &token, acCharVector &str)
{
    token.m_integerValue = 0;
    size_t len = str.size();
    if(len != 0)
    {
        acChar *ptr = &(str.front());
        for(size_t i=0; i<len; ++i, ++ptr)
        {
            switch(*ptr)
            {
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
                token.m_integerValue *= 8;
                token.m_integerValue += ((*ptr) - '0');
                break;
            default:
                m_msgHandler->error(token.m_endLine, "octal digit expected, not '%c'", *ptr);
                return RT_ERROR;
            }
        }
    }

    determineIntType(token);
    return RT_OK;
}

acLexer::acReturnType acLexer::strToDecimal(acToken &token, acCharVector &str)
{
    token.m_integerValue = 0;
    size_t len = str.size();
    if(len == 0)
    {
        m_msgHandler->error(token.m_endLine, "decimal digit expected");
        return RT_ERROR;
    }

    acChar *ptr = &(str.front());
    for(size_t i=0; i<len; ++i, ++ptr)
    {
        switch(*ptr)
        {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            token.m_integerValue *= 10;
            token.m_integerValue += ((*ptr) - '0');
            break;
        default:
            m_msgHandler->error(token.m_endLine, "decimal digit expected, not '%c'", *ptr);
            return RT_ERROR;
        }
    }

    determineIntType(token);
    return RT_OK;
}

acLexer::acReturnType acLexer::strToHexadecimal(acToken &token, acCharVector &str)
{
    token.m_integerValue = 0;
    size_t len = str.size();
    if(len == 0)
    {
        m_msgHandler->error(token.m_endLine, "hexadecimal digit expected");
        return RT_ERROR;
    }

    acChar *ptr = &(str.front());
    for(size_t i=0; i<len; ++i, ++ptr)
    {
        acChar ch = *ptr;
        if(toHex(ch, 0, false) != RT_OK)
        {
            m_msgHandler->error(token.m_endLine, "hexadecimal digit expected, not '%c'", ch);
            return RT_ERROR;
        }
        token.m_integerValue *= 16;
        token.m_integerValue += ch;
    }

    determineIntType(token);
    return RT_OK;
}

void acLexer::determineIntType(acToken &token)
{
    if(token.m_type == TOK_UNKNOWN)
    {
        if(token.m_integerValue <= 0xFFFFFFFF) token.m_type = TOK_UNS32;
        else                                   token.m_type = TOK_UNS64;
    }
}

int acLexer::decodeUTF8(acDchar &dch, acToken &token, acChar *buf, acChar *bufferEnd)
{
    int len = UTF8ToDchar(buf, int(bufferEnd - buf), dch);
    if(len == 0)
    {
        token.m_end = buf;
        m_msgHandler->error(token.m_endLine, "invalid UTF-8 sequence");
        return -1;
    }

    switch(token.m_type)
    {
    case TOK_STRING:
        {
            int l = len;
            token.m_string->push_back(*buf++); // 1
            if(--l > 0)
            {
                token.m_string->push_back(*buf++); // 2
                if(--l > 0)
                {
                    token.m_string->push_back(*buf++); // 3
                    if(--l > 0)
                    {
                        token.m_string->push_back(*buf++); // 4
                    }
                }
            }
        }
        break;
    case TOK_CHAR:
        token.m_charValue = dch;
        buf += len;
        break;
    default:
        break;
    }

    token.m_end = buf;
    return len;
}

acLexer::acReturnType acLexer::decodeEscapeSequence(acDchar *dch, acToken &token,
    acChar *buf, acChar *bufferEnd)
{
    acChar ch;
    if(buf == bufferEnd || (ch=*buf) == 0x00 || ch == 0x1A)
    {
        token.m_end = buf;
        m_msgHandler->error(token.m_endLine, "escape sequence expected, not 'EOF'");
        return RT_ERROR;
    }

    acDchar *pdch = dch;
    if(!pdch)
    {
        pdch = &token.m_charValue;
    }

    buf++;
    switch(ch)
    {
    case 0x0D:
    case 0x0A:
        token.m_end = buf - 1;
        m_msgHandler->error(token.m_endLine, "escape sequence expected, not 'EOL'");
        return RT_ERROR;

    case '\'':
        *pdch = '\'';
        break;
    case '"':
        *pdch = '"';
        break;
    case '?':
        *pdch = '?';
        break;
    case '\\':
        *pdch = '\\';
        break;
    case 'a':
        *pdch = '\a';
        break;
    case 'b':
        *pdch = '\b';
        break;
    case 'f':
        *pdch = '\f';
        break;
    case 'n':
        *pdch = '\n';
        break;
    case 'r':
        *pdch = '\r';
        break;
    case 't':
        *pdch = '\t';
        break;
    case 'v':
        *pdch = '\v';
        break;
    case 'x':
        {
            acChar chs[2] = { 0, 0 };
            for(int i=0; i<2; ++i)
            {
                if(buf != bufferEnd)
                {
                    chs[i] = *buf++;
                    if(toHex(chs[i], token.m_endLine, true) != RT_OK)
                    {
                        token.m_end = buf - 1;
                        return RT_ERROR;
                    }
                }
                else
                {
                    token.m_end = buf;
                    m_msgHandler->error(token.m_endLine, "hex character expected, not 'EOF'");
                    return RT_ERROR;
                }
            }
            *pdch = (chs[0] << 4) | chs[1];
        }
        break;
    case 'u':
        {
            acChar chs[4] = { 0, 0, 0, 0 };
            for(int i=0; i<4; ++i)
            {
                if(buf != bufferEnd)
                {
                    chs[i] = *buf++;
                    if(toHex(chs[i], token.m_endLine, true) != RT_OK)
                    {
                        token.m_end = buf - 1;
                        return RT_ERROR;
                    }
                }
                else
                {
                    token.m_end = buf;
                    m_msgHandler->error(token.m_endLine, "hex character expected, not 'EOF'");
                    return RT_ERROR;
                }
            }
            *pdch = (acDchar(chs[0]) << 12) | (acDchar(chs[1]) << 8) |
                (acDchar(chs[2]) << 4) | chs[3];
        }
        break;
    case 'U':
        {
            acChar chs[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            for(int i=0; i<8; ++i)
            {
                if(buf != bufferEnd)
                {
                    chs[i] = *buf++;
                    if(toHex(chs[i], token.m_endLine, true) != RT_OK)
                    {
                        token.m_end = buf - 1;
                        return RT_ERROR;
                    }
                }
                else
                {
                    token.m_end = buf;
                    m_msgHandler->error(token.m_endLine, "hex character expected, not 'EOF'");
                    return RT_ERROR;
                }
            }
            *pdch = (acDchar(chs[0]) << 28) | (acDchar(chs[1]) << 24) |
                (acDchar(chs[2]) << 20) | (acDchar(chs[3]) << 16) |
                (acDchar(chs[4]) << 12) | (acDchar(chs[5]) << 8) |
                (acDchar(chs[6]) << 4) | chs[7];
        }
        break;

    default:
        if(ch >= '0' && ch <= '7')
        {
            *pdch = ch - '0';
            if(buf != bufferEnd && (ch=*buf) >= '0' && ch <= '7')
            {
                *pdch = ((*pdch) * 8) + ch - '0';
                if(++buf != bufferEnd && (ch=*buf) >= '0' && ch <= '7')
                {
                    *pdch = ((*pdch) * 8) + ch - '0';
                    ++buf;
                }
            }
        }
        else
        {
            token.m_end = buf;
            m_msgHandler->error(token.m_endLine, "undefined escape sequence \\%c", ch);
            return RT_ERROR;
        }
        break;
    }

    token.m_end = buf;
    return RT_OK;
}

acLexer::acReturnType acLexer::toHex(acChar &ch, int line, bool showError)
{

    switch(ch)
    {
    case 0: case 0x1A:
        if(showError) m_msgHandler->error(line, "hex character expected, not 'EOF'");
        return RT_ERROR2;

    case 0x0D: case 0x0A:
        if(showError) m_msgHandler->error(line, "hex character expected, not 'EOL'");
        return RT_ERROR2;

    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        ch = ch - 'A' + 10;
        break;

    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        ch = ch - 'a' + 10;
        break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        ch = ch - '0';
        break;

    default:
        if(showError) m_msgHandler->error(line, "non-hex character '%c'", ch);
        return RT_ERROR;
    }
    return RT_OK;
}

void acLexer::scanDecimal(acChar *buf, acChar *bufferEnd, acChar **ptrEnd,
    acCharVector &result)
{
    while(buf != bufferEnd)
    {
        const acChar ch = *buf;
        switch(ch)
        {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            result.push_back(ch);
            ++buf;
            break;
        case '_':
            ++buf;
            break;
        default:
            bufferEnd = buf;
            break;
        }
    }
    *ptrEnd = buf;
}

void acLexer::scanHexadecimal(acChar *buf, acChar *bufferEnd, acChar **ptrEnd,
    acCharVector &result)
{
    while(buf != bufferEnd)
    {
        const acChar ch = *buf;
        switch(ch)
        {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            result.push_back(ch);
            ++buf;
            break;
        case '_':
            ++buf;
            break;
        default:
            bufferEnd = buf;
            break;
        }
    }
    *ptrEnd = buf;
}

bool acLexer::isDelimiter(acChar ch)
{
    switch(ch)
    {
    case 0x00: case 0x1A: //EOF
    case 0x0D: case 0x0A: //EOL
    case 0x20: case 0x09: case 0x0B: case 0x0C: //SPACE
    case '~': case '!': case '@': case '#': case '$': case '%': case '^':
    case '&': case '*': case '(': case ')': case '-': case '+': case '=':
    case '|': case ';': case ':': case '<': case ',': case '>': case '/': case '?':
    case '[': case ']': case '{': case '}':
        return true;
    }
    return false;
}

acLexer::acReturnType acLexer::hexToInteger(const acChar *str, int strLen, acUInt64 &value)
{
    value = 0;
    int lshift = 0;
    while(strLen != 0)
    {
        acChar ch = str[--strLen];
        toHex(ch, 0, false);
        value |= (acUInt64(ch) << lshift);
        lshift += 4;
        if(lshift >= 64) return RT_ERROR;
    }
    return RT_OK;
}

acLexer::acReturnType acLexer::hexToFraction(const acChar *str, int strLen, acUInt64 &value)
{
    value = 0;
    int lshift = 60;
    int idx = 0;
    while(idx < strLen)
    {
        acChar ch = str[idx++];
        toHex(ch, 0, false);
        value |= (acUInt64(ch) << lshift);
        lshift -= 4;
        if(lshift < 0) return RT_ERROR;
    }
    return RT_OK;
}

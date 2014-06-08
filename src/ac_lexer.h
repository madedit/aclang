/* see copyright notice in aclang.h */

#ifndef AC_LEXER_H
#define AC_LEXER_H

#include "ac_config.h"
#include "ac_ast.h"
#include "ac_utility.h"
#include "ac_msghandler.h"
#include "ac_token.h"
#include "yyparser.hpp"

#include <list>
#include <errno.h>

/**
 * token types
 */

//typedef yytokentype acTokenType;

/*
enum acTokenType
{
    TOK_UNKNOWN = 0,

    // literal tokens
    TOK_EOF,
    TOK_EOL,
    TOK_SPACE,
    TOK_COMMENT,

    // identifier
    TOK_IDENTIFIER,

    TOK_STRING,
    TOK_CHAR,
    TOK_UNS32,
    TOK_UNS64,
    TOK_FLOAT32,
    TOK_FLOAT64,

    // operators
    TOK_DIV,        // /
    TOK_DIVASS,     // /=
    TOK_DOT,        // .
    TOK_DOTDOT,     // ..
    TOK_DOTDOTDOT,  // ...
    TOK_AND,        // &
    TOK_ANDASS,     // &=
    TOK_ANDAND,     // &&
    TOK_OR,         // |
    TOK_ORASS,      // |=
    TOK_OROR,       // ||
    TOK_MINUS,      // -
    TOK_MINUSASS,   // -=
    TOK_MINUSMINUS, // --
    TOK_PLUS,       // +
    TOK_PLUSASS,    // +=
    TOK_PLUSPLUS,   // ++
    TOK_LT,         // <
    TOK_LE,         // <=
    TOK_SHL,        // <<
    TOK_SHLASS,     // <<=
    TOK_LG,         // <>
    TOK_LEG,        // <>=
    TOK_GT,         // >
    TOK_GE,         // >=
    TOK_SHRASS,     // >>=
    TOK_USHRASS,    // >>>=
    TOK_SHR,        // >>
    TOK_USHR,       // >>>
    TOK_NOT,        // !
    TOK_NOTEQUAL,   // !=
    TOK_UE,         // !<>
    TOK_UNORD,      // !<>=
    TOK_UGE,        // !<
    TOK_UG,         // !<=
    TOK_ULE,        // !>
    TOK_UL,         // !>=
    TOK_LPAREN,     // (
    TOK_RPAREN,     // )
    TOK_LBRACKET,   // [
    TOK_RBRACKET,   // ]
    TOK_LCURLY,     // {
    TOK_RCURLY,     // }
    TOK_QUESTION,   // ?
    TOK_COMMA,      // ,
    TOK_SEMICOLON,  // ;
    TOK_COLON,      // :
    TOK_COLONCOLON, // ::
    TOK_DOLLAR,     // $
    TOK_ASSIGN,     // =
    TOK_EQUAL,      // ==
    TOK_MUL,        // *
    TOK_MULASS,     // *=
    TOK_MOD,        // %
    TOK_MODASS,     // %=
    TOK_XOR,        // ^
    TOK_XORASS,     // ^=
    TOK_CAT,        // ~
    TOK_CATASS,     // ~=

    // keywords
    TOK_BASE,
    TOK_BREAK,

    TOK_CASE,
    TOK_CATCH,
    TOK_CONST,
    TOK_CONTINUE,

    TOK_DEFAULT,
    TOK_DELEGATE,
    TOK_DELETE,
    TOK_DO,

    TOK_ELSE,
    TOK_ENUM,
    TOK_EXTENDS,

    TOK_FALSE,
    TOK_FOR,
    TOK_FOREACH,
    TOK_FUNCTION,

    TOK_IF,
    TOK_IN,

    TOK_LOCAL,

    TOK_METAFUNCTION,

    TOK_NAMESPACE,
    TOK_NEW,
    TOK_NULL,

    TOK_RESUME,
    TOK_RETURN,

    TOK_SWITCH,

    TOK_THIS,
    TOK_THROW,
    TOK_TRUE,
    TOK_TRY,
    TOK_TYPEOF,

    TOK_VAR,

    TOK_WHILE,

    TOK_YIELD,

    // special tokens
    STOK_FILE,
    STOK_LINE,
    STOK_DATE,
    STOK_TIME,
    STOK_TIMESTAMP,
    STOK_VENDOR,
    STOK_VERSION
};
*/

/**
 * acLexer
 */
class acLexer
{
protected:
    // store acToken.m_string
    std::list<acDcharVector> m_strings;
    acMsgHandler* m_msgHandler;

public:

    enum acReturnType
    {
        RT_ERROR2 = -2,
        RT_ERROR = -1,
        RT_OK = 0,
        RT_EOF = 1
    };

    acLexer(acMsgHandler* msgHandler): m_msgHandler(msgHandler)
    {
        errno = 0;
    }

    /**
     * get next token
     * @param token stores the token informations
     * @param bufferEnd indicates the end of buffer
     * @return 1 when eof occurred; 0 when no error; -1 when error occurred
     */
    acReturnType next(acToken &token, acChar *bufferEnd);

protected:
    acReturnType hexString(acToken &token, acChar *buf, acChar *bufferEnd);
    acReturnType rawString(acToken &token, acChar *buf, acChar *bufferEnd, acChar endChar);
    acReturnType string(acToken &token, acChar *buf, acChar *bufferEnd);
    acReturnType dchar(acToken &token, acChar *buf, acChar *bufferEnd);
    acReturnType number(acToken &token, acChar *buf, acChar *bufferEnd);
    acReturnType hexToDouble(acToken &token, acCharVector &integer,
                             acCharVector &fraction, acCharVector &exponent);
    acReturnType strToBinary(acToken &token, acCharVector &str);
    acReturnType strToOctal(acToken &token, acCharVector &str);
    acReturnType strToDecimal(acToken &token, acCharVector &str);
    acReturnType strToHexadecimal(acToken &token, acCharVector &str);

    void determineIntType(acToken &token);

    int decodeUTF8(acDchar &dch, acToken &token, acChar *buf, acChar *bufferEnd);
    acReturnType decodeEscapeSequence(acDchar *dch, acToken &token, acChar *buf, acChar *bufferEnd);
    acReturnType toHex(acChar &ch, int line, bool showError);
    void scanDecimal(acChar *buf, acChar *bufferEnd, acChar **ptrEnd,
                     acCharVector &result);
    void scanHexadecimal(acChar *buf, acChar *bufferEnd, acChar **ptrEnd,
        acCharVector &result);

    bool isDelimiter(acChar ch);
    acReturnType hexToInteger(const acChar *str, int strLen, acUInt64 &value);
    acReturnType hexToFraction(const acChar *str, int strLen, acUInt64 &value);
};

#endif //AC_LEXER_H

/* see copyright notice in aclang.h */
#include "ac_parser.h"
#include "ac_msghandler.h"
#include "ac_vm.h"
//#include <llvm/Analysis/Verifier.h>
//#include <llvm/IR/DataLayout.h>
//#include <llvm/IR/DerivedTypes.h>
//#include <llvm/Support/TargetSelect.h>
#include <stdio.h>

using namespace llvm;

acParser::acParser(acVM* vm)
    : m_vm(vm)
    , m_msgHandler(vm->getMsgHandler())
    , m_lexer(m_msgHandler)
{
}

acCodeGenerator* acParser::getCodeGenerator()
{
    return m_vm->getCodeGenerator();
}

void acParser::releaseNodeASTList()
{
    std::list<NodeAST*>::iterator it = m_nodeASTList.begin();
    while(it != m_nodeASTList.end())
    {
        delete *it;
        ++it;
    }
    m_nodeASTList.clear();
}

int acParser::setCode(const char* code)
{
    m_buffer.clear();
    if(code != 0)
    {
        m_buffer = code;
        m_currTok.m_end = (acChar*)m_buffer.c_str();
        m_currTok.m_endLine = 1;
    }
    return m_buffer.length();
}

int acParser::inputCode(const char* code)
{
    if(code == 0) return inputCode();

    m_buffer.clear();
    
    fprintf(stderr, "\nready (press Ctrl+D to end input) >\n");
    errno = 0;

    while(1)
    {
        int ch = *code++;
        if(ch == 0 || ch == -1 || ch == 0x04) break;
        printf("%c", (char)ch);
        m_buffer += (char)ch;
    }
    printf("\n");

    m_currTok.m_end = (acChar*)m_buffer.c_str();
    m_currTok.m_endLine = 1;

    return m_buffer.length();
}

int acParser::inputCode()
{
    fflush(stdin);

    fprintf(stderr, "\nready (press Ctrl+D to end input) >\n");
    errno = 0;

    m_buffer.clear();

    while(1)
    {
        int ch = -1;
        ch = getchar();
        if(ch == -1 || ch == 0x04) break;
        m_buffer += (char)ch;
    }

    m_currTok.m_end = (acChar*)m_buffer.c_str();
    m_currTok.m_endLine = 1;

    return m_buffer.length();
}

int yylex(YYSTYPE* yylval,void* parser)
{
    acToken& currTok = ((acParser*)parser)->getCurrentToken();
    std::string& codeBuffer = ((acParser*)parser)->getBuffer();

    currTok.m_begin = currTok.m_end;
    currTok.m_beginLine = currTok.m_endLine;

    acLexer::acReturnType ret = ((acParser*)parser)->getLexer().next(currTok, (acChar*)codeBuffer.c_str() + codeBuffer.length());

    switch(ret)
    {
    case acLexer::RT_OK:
        switch(currTok.m_type)
        {
        case TOK_EOF:
            yylval->token = currTok;
            return 0;//YYEOF

        case TOK_UNKNOWN:
            yylval->token = currTok;
            return 2;//YYUNDEFTOK

        case TOK_EOL:
        case TOK_SPACE:
        case TOK_COMMENT:
            return yylex(yylval, parser);

        default:
            yylval->token = currTok;
            break;
        }
        break;

    case acLexer::RT_EOF:
        yylval->token = currTok;
        return 0;//YYEOF

    default: //RT_ERROR
        yylval->token = currTok;
        return 2;//YYUNDEFTOK
    }

    return currTok.m_type;
}

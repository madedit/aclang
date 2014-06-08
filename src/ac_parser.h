/* see copyright notice in aclang.h */

#ifndef AC_PARSER_H
#define AC_PARSER_H

#include "ac_config.h"
#include "ac_codegen.h"
#include "ac_lexer.h"
#include "ac_msghandler.h"
#include "ac_token.h"
#include "ac_utility.h"


class acVM;

class acParser
{
protected:
    acVM* m_vm;
    acMsgHandler* m_msgHandler;
    acLexer m_lexer;
    acToken m_currTok;
    std::string m_buffer;
    std::list<NodeAST*> m_nodeASTList;

public:
    acParser(acVM* vm);

    acCodeGenerator* getCodeGenerator();

    void setProgramBlockAST(BlockAST* block) { getCodeGenerator()->setProgramBlockAST(block); }
    BlockAST* getProgramBlockAST() { return getCodeGenerator()->getProgramBlockAST(); }

    void addNodeAST(NodeAST* node) { m_nodeASTList.push_back(node); }
    void releaseNodeASTList();

    acMsgHandler* getMsgHandler() { return m_msgHandler; }
    acLexer& getLexer() { return m_lexer; }
    acToken& getCurrentToken() { return m_currTok; }
    std::string& getBuffer() { return m_buffer; }

    int setCode(const char* code);

    //input code from shell
    int inputCode(const char* code);
    int inputCode();

};

#endif //AC_PARSER_H

/* see copyright notice in aclang.h */

#include "ac_msghandler.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void acMsgHandler::setFileName(const char* filename)
{
    m_filename = filename;
}

void acMsgHandler::error(acToken& tok, const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    char buffer2[1024];
    sprintf(buffer2, "%s(%d): on token `%s`: %s", m_filename.c_str(), tok.m_beginLine, tok.getRawString().c_str(), buffer);
    m_printMsgFunc(MessageLevel::ERROR, buffer2);
}

void acMsgHandler::error(int line, const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    char buffer2[1024];
    sprintf(buffer2, "%s(%d): %s", m_filename.c_str(), line, buffer);
    m_printMsgFunc(MessageLevel::ERROR, buffer2);
}

void acMsgHandler::error(const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    m_printMsgFunc(MessageLevel::ERROR, buffer);
}

void acMsgHandler::warning(const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    m_printMsgFunc(MessageLevel::WARNING, buffer);
}

void acMsgHandler::info(const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    m_printMsgFunc(MessageLevel::INFO, buffer);
}

void acMsgHandler::output(const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    m_printMsgFunc(MessageLevel::OUTPUT, buffer);
}

void acMsgHandler::registerPrintMsg(PrintMsg func)
{
    m_printMsgFunc = func;
}

//default printMsg function
void acMsgHandler::printMsg(int level, const char *msg)
{
    if(level == MessageLevel::OUTPUT)
        printf("%s", msg);
    else
        printf("%s\n", msg);
}

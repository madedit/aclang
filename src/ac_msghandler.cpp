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

void acMsgHandler::errorMessage(acToken& tok, const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    printf("%s(%d): on token `%s`: %s\n", m_filename.c_str(), tok.m_beginLine, tok.getRawString().c_str(), buffer);
}

void acMsgHandler::errorMessage(int line, const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    printf("%s(%d): %s\n", m_filename.c_str(), line, buffer);
}

void acMsgHandler::errorMessage(const char *format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    printf("%s\n", buffer);
}


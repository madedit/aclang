/* see copyright notice in aclang.h */

#ifndef AC_MSGHANDLER_H
#define AC_MSGHANDLER_H

#include "ac_token.h"

class acMsgHandler
{
public:
    acMsgHandler()
    {
        m_filename = "input";
        registerPrintMsg(printMsg);
    }

    void setFileName(const char* filename);
    std::string& getFileName() { return m_filename; }

    void error(acToken& tok, const char *format, ...);
    void error(const char *file, int line, const char *format, ...);
    void error(int line, const char *format, ...);
    void error(const char *format, ...);
    void warning(const char *format, ...);
    void info(const char *format, ...);
    void output(const char *format, ...);

    enum MessageType
    {
        //compile-time & run-time message
        ERROR,
        WARNING,
        INFO,
        //program output, e.g. print()
        OUTPUT,
    };
    typedef void(*PrintMsg)(int type, const char *msg);
    void registerPrintMsg(PrintMsg func);

protected:
    PrintMsg m_printMsgFunc;
    std::string m_filename;
    static void printMsg(int type, const char *msg);
};


#endif // AC_MSGHANDLER_H

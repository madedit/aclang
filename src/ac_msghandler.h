/* see copyright notice in aclang.h */

#ifndef AC_MSGHANDLER_H
#define AC_MSGHANDLER_H

#include "ac_token.h"

class acMsgHandler
{
public:
    acMsgHandler()
    {
        m_filename.clear();
    }

    void setFileName(const char* filename);
    std::string getFileName() { return m_filename; }

    void error(acToken& tok, const char *format, ...);
    void error(int line, const char *format, ...);
    void error(const char *format, ...);
    void warning(const char *format, ...);
    void info(const char *format, ...);

    enum MessageLevel
    {
        ERROR,
        WARNING,
        INFO
    };
    typedef void(*PrintMsg)(int level, const char *msg);
    void registerPrintMsg(PrintMsg func);

protected:
    PrintMsg m_printMsgFunc;
    std::string m_filename;

};


#endif // AC_MSGHANDLER_H

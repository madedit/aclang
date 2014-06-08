/* see copyright notice in aclang.h */

#ifndef AC_MSGHANDLER_H
#define AC_MSGHANDLER_H

#include "ac_token.h"

class acMsgHandler
{
protected:
    std::string m_filename;

public:
    acMsgHandler()
    {
        m_filename.clear();
    }

    void setFileName(const char* filename);
    std::string getFileName() { return m_filename; }
    void errorMessage(acToken& tok, const char *format, ...);
    void errorMessage(int line, const char *format, ...);
    void errorMessage(const char *format, ...);
};


#endif // AC_MSGHANDLER_H

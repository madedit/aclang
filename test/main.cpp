

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ac_vm.h>

#if defined(WIN32)
#include <windows.h>
#endif

//>>>>> Dump Memory Leaks >>>>>
#if defined(WIN32) && defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK ,__FILE__, __LINE__)
struct __DumpMemLeaks
{
    __DumpMemLeaks()
    {
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
        long ba = -1;
        _CrtSetBreakAlloc(ba);
    }
};
static __DumpMemLeaks __dml;
#endif
//<<<<< Dump Memory Leaks <<<<<


using namespace std;

void test_lexer();
void test_parser();
void test_gc();

void aclang_shell();
int inputCode(std::string& buffer, acVM* vm);
int MBCSToUTF8(std::string& buffer);

int main()
{
    //test_lexer();
    //cout << "test_lexer() finished.\n";

    //test_parser();
    //cout << "test_parser() finished.\n";

    //test_gc();
    //cout << "test_gc() finished.\n";

    //cout <<  "\nAll tests finished.\nPress any key to continue...";
    //getchar();

    aclang_shell();

    return 0;
}

void aclang_shell()
{
    acVM vm;
    vm.getMsgHandler()->setFileName("<stdin>");
    std::string buffer;

    while(inputCode(buffer, &vm) > 0)
    {
        vm.runCode(buffer.c_str());
    }
}

int inputCode(std::string& buffer, acVM* vm)
{
    fflush(stdin);

    fprintf(stderr, "\n[printAST() = %s, printIR() = %s, printGC() = %s]\n",
        vm->getPrintAST()? "true":"false",
        vm->getPrintIR()? "true":"false",
        vm->getPrintGC()? "true":"false" );
    fprintf(stderr, "ACLang ready (press Ctrl+D to end input) >\n");

    errno = 0;

    buffer.clear();

    while(1)
    {
        int ch = -1;
        ch = getchar();
        if(ch == -1 || ch == 0x04) break;
        buffer += (char)ch;
    }

#if defined(WIN32)
    MBCSToUTF8(buffer);
#endif

    return buffer.length();
}

#if defined(WIN32)
WCHAR* pTempWCBuf = 0;
int nTempWCBufSize = 0;
int MBCSToUTF8(std::string& buffer)
{
    WCHAR outBuf[ 1024 ];

    /// MBCS -> Unicode
    int iWideCharCnt = MultiByteToWideChar( CP_ACP,
        0,
        buffer.c_str(),
        static_cast<int>(buffer.length()), 
        outBuf, 
        0 );

    WCHAR* pOutBuf = NULL;
    size_t    iOutBufSize = 0;
    if( iWideCharCnt >= 1024 )
    {
        if( iWideCharCnt > nTempWCBufSize )
        {
            if( pTempWCBuf )
            {
                delete[] pTempWCBuf;
                pTempWCBuf = NULL;
            }
            pTempWCBuf = new WCHAR[ iWideCharCnt + 10 ];
            nTempWCBufSize = iWideCharCnt;
        }
        pOutBuf = pTempWCBuf;
        iOutBufSize = nTempWCBufSize;
    }
    else
    {
        pOutBuf = outBuf;
        iOutBufSize = sizeof( outBuf );
    }

    /// MBCS -> Unicode
    iWideCharCnt = MultiByteToWideChar( CP_ACP, //When this is set, dwFlags must be zero.
        0, 
        buffer.c_str(),
        buffer.length(), 
        pOutBuf, 
        static_cast<int>(iOutBufSize) );
    pOutBuf[iWideCharCnt] = 0;

    /// Unicode -> UTF8
    int ret = WideCharToMultiByte( CP_UTF8,
        0, 
        pOutBuf, 
        -1, 
        0, 
        0, 
        0, 
        0 );
    buffer.resize(ret);

    ret = WideCharToMultiByte( CP_UTF8,
        0, 
        pOutBuf, 
        -1, 
        &buffer[0], 
        ret, 
        0, 
        0 );
    if(buffer[ret] == 0)
    {
        --ret;
        buffer.resize(ret);
    }
    return ret;
}
#endif



#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ac_vm.h>

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
int inputCode(std::string& buffer);

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

    while(inputCode(buffer) > 0)
    {
        vm.runCode(buffer.c_str());
    }
}

int inputCode(std::string& buffer)
{
    fflush(stdin);

    fprintf(stderr, "\nACLang ready (press Ctrl+D to end input) >\n");
    errno = 0;

    buffer.clear();

    while(1)
    {
        int ch = -1;
        ch = getchar();
        if(ch == -1 || ch == 0x04) break;
        buffer += (char)ch;
    }

    return buffer.length();
}

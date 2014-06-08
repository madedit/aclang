
#include <ac_parser.h>
#include <ac_vm.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

extern int yydebug;
extern int yyparse(void*);

int parser_main()
{
    char* filename = "test.ac";//"<stdin>";

    acVM vm;
    vm.getMsgHandler()->setFileName(filename);
    acParser *parser = vm.getParser();
    acCodeGenerator *codegen = vm.getCodeGenerator();

    yydebug = 0;

	char *code;
    int length;

    std::vector<char> buf;
    std::ifstream is;
    is.open (filename, std::ios::binary );

    if(!is.is_open())
    {
        std::cout << "Cannot open " << filename << "\n";
        return -1;
    }

    // get length of file:
    is.seekg (0, std::ios::end);
    length = is.tellg();
    is.seekg (0, std::ios::beg);

    // allocate memory:
    buf.resize(length + 1);
    code = &buf[0];

    // read data as a block:
    is.read (code, length);
    is.close();

    code[length] = 0;

#if 0
    char *code = "function f(var a, b)  \n"
                 "{ var c = a+b*10;     \n"
                 "  return function()   \n"
                 "  {                   \n"\
                 "      print(a+b+c);   \n"
                 "  }                   \n"
                 "}\n"
                 "var f1 = f(10, 20); \n"
                 "f1();";
    void f(acArray* A, acArray* T, acArray* U) //A:args, T:tmpVars. U:upVars
    {
        var* a = getVar(A, 1);
        var* b = getVar(A, 2);
        var* c = getVar(T, 0);
        var* $t1 = getVar(T, 1);
        var* $t2 = getVar(T, 2);
        var* $t3 = getVar(T, 3);

        assignVar_int32($t1, 10);
        assignVar($t2, b);
        mulVar($t2, $t1);
        assignVar($t3, a);
        addVar($t3, $t2);
        assignVar(c, $t3);

        createArray($t1);
        pushVar($t1, a);
        pushVar($t1, b);
        pushVar($t1, c);
        createAnonyFunc($t2, "anonyfunc1", $t1);

        setVar(A, 0, $t2);
    }
    void anonyfunc1(acArray* A, acArray* T, acArray* U)
    {
        var* $t0 = getVar(T, 0);
        var* $t1 = getVar(T, 1);
        var* $t2 = getVar(T, 2);
        var* a = getVar(U, 0);
        var* b = getVar(U, 1);
        var* c = getVar(U, 2);
        assignVar($t0, a);
        addVar($t0, b);
        addVar($t0, c);

        createArray($t1);
        $this = getVar(A, 0);
        pushVar($t1, $this);
        pushVar($t1, $t0);

        findFuncInScope($t2, "print");
        call($t2, $t1);

        setVar_null(A, 0);//return;
    }
#endif

#if 0
    char *code = "function f(var a, b)  \n"
                 "{ var c = a+b*10;     \n"
                 "  return c;           \n"
                 "}\n"
                 "f(10, 20);";
    void f(acArray* A, acArray* T, acArray* U) //A:args, T:tmpVars. U:upVars
    {
        var* a = getVar(A, 1);
        var* b = getVar(A, 2);
        var* c = getVar(T, 0);
        var* $t1 = getVar(T, 1);
        var* $t2 = getVar(T, 2);
        var* $t3 = getVar(T, 3);
        assignVar_int32($t1, 10);
        assignVar($t2, b);
        mulVar($t2, $t1);
        assignVar($t3, a);
        addVar($t3, $t2);
        assignVar(c, $t3);
        setVar(A, 0, c);//return c;
    }
    void main1(acArray* A, acArray* T)
    {
        var* $t0 = getVar(T, 0);
        createArray($t0);
        $this = getVar(A, 0);
        pushVar($t0, $this);
        pushInt32($t0, 10);
        pushInt32($t0, 20);
        var* f = findVar(A, 0, "f");
        call(f, $t0);
    }
#endif

    
int64_t v0= 0x8000000000000000LL;
int64_t v1= 0x8000000100000000LL;
int a = v0-v1;


    while(parser->inputCode(code) > 0)
    {
        int ret = yyparse(parser);
        std::cout << "yyparse() = " << ret << endl << endl;

	    if(ret == 0)
        {
            if(parser->getProgramBlockAST() != 0)
            {
                printf("========AST Begin========\n");
                parser->getProgramBlockAST()->print(0);        
                printf("========AST End========\n");
            }

	        //std::cout << programBlock << endl;
	        codegen->generateCode();
            if(!codegen->isCompileError())
            {
	            codegen->runCode();
            }
        }

        parser->releaseNodeASTList();
        code = 0;
    }
	
    std::cout << "press Enter to continue..." << endl;
    fflush(stdin);
    getchar();
    return 0;
}

void test_parser()
{
    parser_main();
}

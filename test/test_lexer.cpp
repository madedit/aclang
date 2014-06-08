
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ac_lexer.h>

void test_lexer()
{
    size_t length;
    char *buffer;
    
#if 1
    buffer=
    "  /* block /* *comment */ /+ \n"
    "   /+ // line comment +/\n" 
    "/= +/ /=  / \n"
    "x\"e0 af 80 00\"d    \n"
    "  `abcdefghi`c      \n"
    "  x\"f ff  f\"w      \n"
    "  \" \\t \xe4\xb8\x80 \\U0000FFff \"   \n"
    "  \\n\\xff\\U00000001\n"
    "  0e0 1.f .0 078.e10f 0x1.0p102 999f 0.e1f 1_e_1_ \n"
    " 0b1_1_1_0 1 2 0x344L \n"
    "/ /= . .. ... & &= && | |= || - -= -- + += ++ \n"
    "< <= << <<= <> <>= > >= >>= >>>= >> >>> \n"
    "! != !<> !<>= !< !<= !> !>= ( ) [ ] { } \n"
    "? , ; : $ = == * *= % %= ^ ^= ~ ~= \n"
    " a _slkdfjsldf_jk for(int a=10;a<=15;a++) a++;\n"
    "void x=-10;\n"
    ;
    
    length = strlen(buffer);

#else

    std::vector<char> buf;

    std::ifstream is;
    is.open ("test.ac", std::ios::binary );

    // get length of file:
    is.seekg (0, std::ios::end);
    length = is.tellg();
    is.seekg (0, std::ios::beg);

    // allocate memory:
    buf.resize(length);
    buffer = &buf[0];

    // read data as a block:
    is.read (buffer,length);
    is.close();
#endif
    
    unsigned char *bufferEnd = (unsigned char*)(buffer+length);

    acMsgHandler msghandler;
    acLexer lexer(&msghandler);
    acToken tk;

    int ret;
    tk.m_begin = (unsigned char*)buffer;
    tk.m_beginLine = tk.m_endLine = 1;
    while( (ret=lexer.next(tk, bufferEnd))==0 && tk.m_type != TOK_EOF)
    {
        acString str(tk.m_begin, tk.m_end);

        if(tk.m_type!=TOK_EOL && tk.m_type!=TOK_SPACE)
            printf("%d: line %d:\n%s\n", tk.m_type, tk.m_beginLine, str.c_str());

        tk.m_begin = tk.m_end;

        switch(tk.m_type)
        {
        case TOK_EOL:
            {
            }
            break;
        case TOK_FLOAT64:
            {
                printf("  --> tk.doubleValue = %f\n", tk.m_doubleValue);
            }
            break;
        case TOK_FLOAT32:
            {
                printf("  --> tk.floatValue = %f\n", tk.m_doubleValue);
            }
            break;
        case TOK_UNS32:
            {
                printf("  --> tk.uns32Value = %d\n", tk.m_integerValue);
            }
            break;
        case TOK_UNS64:
            {
                printf("  --> tk.uns64Value = %d\n", tk.m_integerValue);
            }
            break;
        case TOK_IDENTIFIER:
            {
                printf("  --> tt_identifier\n");
            }
            break;
        }
        tk.m_beginLine = tk.m_endLine;
    }
    if(ret<0)
    {
        acString str(tk.m_begin, tk.m_end);
        printf("error occurred!: %d: line %d: [[%s]]\n", tk.m_type, tk.m_beginLine, str.c_str());
        getchar();
    }
    
}

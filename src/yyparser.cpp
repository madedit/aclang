/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "yyparser.y"

/* see copyright notice in aclang.h */
#include "ac_ast.h"
#include "ac_token.h"
#include "ac_parser.h"

#define YYLEX_PARAM parser
#define YYPARSE_PARAM parser

extern int yylex(YYSTYPE* yylval, void* YYLEX_PARAM);
extern int yyparse(void* YYPARSE_PARAM);

#define PARSER ((acParser*)parser)

//#define yyerror(MSG) PARSER->getMsgHandler()->errorMessage(PARSER->getCurrentToken(), MSG)
#define yyerror(MSG) PARSER->getMsgHandler()->errorMessage(yylval.token, MSG)
//int yyerror(const char *s) { std::printf("Error: %s\n", s); return 1; }


/* Line 371 of yacc.c  */
#line 88 "yyparser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yyparser.hpp".  */
#ifndef YY_YY_YYPARSER_HPP_INCLUDED
# define YY_YY_YYPARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IFX = 258,
     TOK_ELSE = 259,
     THISX = 260,
     TOK_DOT = 261,
     TOK_LBRACKET = 262,
     TOK_UNKNOWN = 263,
     TOK_EOF = 264,
     TOK_EOL = 265,
     TOK_SPACE = 266,
     TOK_COMMENT = 267,
     TOK_IDENTIFIER = 268,
     TOK_STRING = 269,
     TOK_CHAR = 270,
     TOK_UNS32 = 271,
     TOK_UNS64 = 272,
     TOK_FLOAT32 = 273,
     TOK_FLOAT64 = 274,
     TOK_DIV = 275,
     TOK_DIVASS = 276,
     TOK_DOTDOT = 277,
     TOK_DOTDOTDOT = 278,
     TOK_AND = 279,
     TOK_ANDASS = 280,
     TOK_ANDAND = 281,
     TOK_OR = 282,
     TOK_ORASS = 283,
     TOK_OROR = 284,
     TOK_MINUS = 285,
     TOK_MINUSASS = 286,
     TOK_MINUSMINUS = 287,
     TOK_PLUS = 288,
     TOK_PLUSASS = 289,
     TOK_PLUSPLUS = 290,
     TOK_LT = 291,
     TOK_LE = 292,
     TOK_SHL = 293,
     TOK_SHLASS = 294,
     TOK_LG = 295,
     TOK_LEG = 296,
     TOK_GT = 297,
     TOK_GE = 298,
     TOK_SHRASS = 299,
     TOK_USHRASS = 300,
     TOK_SHR = 301,
     TOK_USHR = 302,
     TOK_NOT = 303,
     TOK_NOTEQUAL = 304,
     TOK_UE = 305,
     TOK_UNORD = 306,
     TOK_UGE = 307,
     TOK_UG = 308,
     TOK_ULE = 309,
     TOK_UL = 310,
     TOK_LPAREN = 311,
     TOK_RPAREN = 312,
     TOK_RBRACKET = 313,
     TOK_LCURLY = 314,
     TOK_RCURLY = 315,
     TOK_QUESTION = 316,
     TOK_COMMA = 317,
     TOK_SEMICOLON = 318,
     TOK_COLON = 319,
     TOK_COLONCOLON = 320,
     TOK_DOLLAR = 321,
     TOK_ASSIGN = 322,
     TOK_EQUAL = 323,
     TOK_MUL = 324,
     TOK_MULASS = 325,
     TOK_MOD = 326,
     TOK_MODASS = 327,
     TOK_XOR = 328,
     TOK_XORASS = 329,
     TOK_CAT = 330,
     TOK_CATASS = 331,
     TOK_BASE = 332,
     TOK_BREAK = 333,
     TOK_CASE = 334,
     TOK_CATCH = 335,
     TOK_CONST = 336,
     TOK_CONTINUE = 337,
     TOK_DEFAULT = 338,
     TOK_DELEGATE = 339,
     TOK_DELETE = 340,
     TOK_DO = 341,
     TOK_ENUM = 342,
     TOK_EXTENDS = 343,
     TOK_FALSE = 344,
     TOK_FOR = 345,
     TOK_FOREACH = 346,
     TOK_FUNCTION = 347,
     TOK_IF = 348,
     TOK_IN = 349,
     TOK_INT = 350,
     TOK_LOCAL = 351,
     TOK_METAFUNCTION = 352,
     TOK_NAMESPACE = 353,
     TOK_NEW = 354,
     TOK_NULL = 355,
     TOK_RESUME = 356,
     TOK_RETURN = 357,
     TOK_SWITCH = 358,
     TOK_THIS = 359,
     TOK_THROW = 360,
     TOK_TRUE = 361,
     TOK_TRY = 362,
     TOK_VAR = 363,
     TOK_WHILE = 364,
     TOK_YIELD = 365,
     STOK_FILE = 366,
     STOK_LINE = 367,
     STOK_DATE = 368,
     STOK_TIME = 369,
     STOK_TIMESTAMP = 370,
     STOK_VENDOR = 371,
     STOK_VERSION = 372
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 34 "yyparser.y"

    acToken token;
    NodeAST* node;
    BlockAST* block;
    GetVarAST* getvar;
    FunctionAST* func;
    StringList* arglist;
    NodeASTList* nodelist;


/* Line 387 of yacc.c  */
#line 259 "yyparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_YYPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 286 "yyparser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1394

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNRULES -- Number of states.  */
#define YYNSTATES  300

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   372

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    13,    15,    17,
      19,    21,    23,    27,    30,    32,    35,    37,    39,    41,
      43,    45,    47,    51,    53,    55,    57,    59,    63,    65,
      69,    74,    78,    83,    86,    89,    91,    93,    95,    97,
      99,   102,   105,   108,   110,   114,   118,   122,   124,   128,
     132,   134,   138,   142,   144,   148,   152,   156,   160,   162,
     166,   170,   172,   176,   178,   182,   184,   188,   190,   194,
     196,   200,   202,   208,   210,   212,   214,   216,   218,   220,
     222,   224,   226,   228,   230,   232,   234,   236,   240,   244,
     248,   250,   252,   254,   256,   258,   260,   262,   264,   266,
     268,   270,   272,   276,   282,   284,   288,   290,   294,   297,
     301,   306,   308,   310,   314,   317,   321,   326,   328,   330,
     332,   334,   336,   339,   341,   344,   348,   353,   355,   359,
     364,   367,   372,   376,   382,   384,   387,   391,   396,   402,
     409,   412,   417,   423,   431,   437,   445,   447,   450,   455,
     459,   463,   466,   469,   472,   475,   479,   482,   485,   491,
     499,   506,   514,   521,   529,   537,   545,   551
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,    -1,   120,    -1,   121,    -1,   120,   121,
      -1,   123,    -1,   154,    -1,   163,    -1,   166,    -1,   167,
      -1,   168,    -1,    59,   120,    60,    -1,    59,    60,    -1,
      63,    -1,   142,    63,    -1,   122,    -1,   144,    -1,   145,
      -1,   146,    -1,   152,    -1,   156,    -1,    56,   143,    57,
      -1,   104,    -1,   141,    -1,   149,    -1,   162,    -1,   125,
      62,   141,    -1,   124,    -1,   126,     6,    13,    -1,   126,
       7,   142,    58,    -1,   126,    56,    57,    -1,   126,    56,
     125,    57,    -1,   126,    35,    -1,   126,    32,    -1,    33,
      -1,    30,    -1,    75,    -1,    48,    -1,   126,    -1,    35,
     128,    -1,    32,   128,    -1,   127,   128,    -1,   128,    -1,
     129,    69,   128,    -1,   129,    20,   128,    -1,   129,    71,
     128,    -1,   129,    -1,   130,    33,   129,    -1,   130,    30,
     129,    -1,   130,    -1,   131,    38,   130,    -1,   131,    46,
     130,    -1,   131,    -1,   132,    36,   131,    -1,   132,    42,
     131,    -1,   132,    37,   131,    -1,   132,    43,   131,    -1,
     132,    -1,   133,    68,   132,    -1,   133,    49,   132,    -1,
     133,    -1,   134,    24,   133,    -1,   134,    -1,   135,    73,
     134,    -1,   135,    -1,   136,    27,   135,    -1,   136,    -1,
     137,    26,   136,    -1,   137,    -1,   138,    29,   137,    -1,
     138,    -1,   138,    61,   143,    64,   143,    -1,    67,    -1,
      21,    -1,    25,    -1,    28,    -1,    31,    -1,    34,    -1,
      39,    -1,    44,    -1,    45,    -1,    70,    -1,    72,    -1,
      74,    -1,    76,    -1,   139,    -1,   128,   140,   141,    -1,
     128,   140,   149,    -1,   128,   140,   162,    -1,   141,    -1,
     142,    -1,   149,    -1,   162,    -1,   106,    -1,    89,    -1,
      16,    -1,    17,    -1,    18,    -1,    19,    -1,    14,    -1,
      13,    -1,    13,    67,   143,    -1,     7,   142,    58,    67,
     143,    -1,   160,    -1,   146,    64,   143,    -1,   147,    -1,
     148,    62,   147,    -1,    59,    60,    -1,    59,   148,    60,
      -1,    59,   148,    62,    60,    -1,   143,    -1,   150,    -1,
     151,    62,   150,    -1,     7,    58,    -1,     7,   151,    58,
      -1,     7,   151,    62,    58,    -1,   108,    -1,    96,    -1,
     155,    -1,   160,    -1,   161,    -1,   158,    63,    -1,    13,
      -1,    65,    13,    -1,   104,     6,    13,    -1,   104,     7,
     142,    58,    -1,   156,    -1,   157,     6,    13,    -1,   157,
       7,   142,    58,    -1,   153,   157,    -1,   153,   157,    67,
     143,    -1,   158,    62,   157,    -1,   158,    62,   157,    67,
     143,    -1,    13,    -1,   153,    13,    -1,   159,    62,    13,
      -1,   159,    62,   153,    13,    -1,    92,   157,    56,    57,
     122,    -1,    92,   157,    56,   159,    57,   122,    -1,    96,
     160,    -1,    92,    56,    57,   122,    -1,    92,    56,   159,
      57,   122,    -1,    93,    56,   142,    57,   121,     4,   121,
      -1,    93,    56,   142,    57,   121,    -1,   103,    56,   142,
      57,    59,   164,    60,    -1,   165,    -1,   164,   165,    -1,
      79,   142,    64,   120,    -1,    79,   142,    64,    -1,    83,
      64,   120,    -1,    83,    64,    -1,    82,    63,    -1,    78,
      63,    -1,   102,    63,    -1,   102,   142,    63,    -1,   102,
     149,    -1,   102,   162,    -1,   109,    56,   142,    57,   121,
      -1,    86,   121,   109,    56,   142,    57,    63,    -1,    90,
      56,   123,   123,    57,   121,    -1,    90,    56,   123,   123,
     142,    57,   121,    -1,    90,    56,   155,   123,    57,   121,
      -1,    90,    56,   155,   123,   142,    57,   121,    -1,    91,
      56,   142,    94,   143,    57,   121,    -1,    91,    56,   158,
      94,   143,    57,   121,    -1,    98,   157,    59,   120,    60,
      -1,    98,   157,    59,    60,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   176,   176,   177,   181,   182,   186,   187,   188,   189,
     190,   191,   195,   196,   200,   201,   202,   206,   207,   208,
     210,   211,   213,   214,   218,   219,   220,   221,   225,   226,
     227,   228,   229,   230,   231,   236,   237,   238,   239,   243,
     244,   245,   246,   250,   251,   252,   253,   257,   258,   259,
     263,   264,   265,   269,   270,   271,   272,   273,   277,   278,
     279,   283,   284,   288,   289,   293,   294,   298,   299,   303,
     304,   308,   309,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   329,   330,   331,   332,
     336,   340,   341,   342,   346,   347,   351,   352,   353,   354,
     358,   362,   363,   364,   365,   367,   371,   372,   376,   377,
     378,   382,   386,   387,   391,   392,   393,   397,   398,   404,
     405,   406,   410,   414,   415,   416,   417,   423,   424,   425,
     428,   436,   444,   451,   461,   462,   463,   472,   484,   489,
     497,   500,   505,   513,   514,   515,   520,   521,   533,   534,
     535,   536,   540,   541,   542,   543,   544,   545,   549,   550,
     551,   552,   553,   554,   555,   556,   560,   561
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IFX", "TOK_ELSE", "THISX", "TOK_DOT",
  "TOK_LBRACKET", "TOK_UNKNOWN", "TOK_EOF", "TOK_EOL", "TOK_SPACE",
  "TOK_COMMENT", "TOK_IDENTIFIER", "TOK_STRING", "TOK_CHAR", "TOK_UNS32",
  "TOK_UNS64", "TOK_FLOAT32", "TOK_FLOAT64", "TOK_DIV", "TOK_DIVASS",
  "TOK_DOTDOT", "TOK_DOTDOTDOT", "TOK_AND", "TOK_ANDASS", "TOK_ANDAND",
  "TOK_OR", "TOK_ORASS", "TOK_OROR", "TOK_MINUS", "TOK_MINUSASS",
  "TOK_MINUSMINUS", "TOK_PLUS", "TOK_PLUSASS", "TOK_PLUSPLUS", "TOK_LT",
  "TOK_LE", "TOK_SHL", "TOK_SHLASS", "TOK_LG", "TOK_LEG", "TOK_GT",
  "TOK_GE", "TOK_SHRASS", "TOK_USHRASS", "TOK_SHR", "TOK_USHR", "TOK_NOT",
  "TOK_NOTEQUAL", "TOK_UE", "TOK_UNORD", "TOK_UGE", "TOK_UG", "TOK_ULE",
  "TOK_UL", "TOK_LPAREN", "TOK_RPAREN", "TOK_RBRACKET", "TOK_LCURLY",
  "TOK_RCURLY", "TOK_QUESTION", "TOK_COMMA", "TOK_SEMICOLON", "TOK_COLON",
  "TOK_COLONCOLON", "TOK_DOLLAR", "TOK_ASSIGN", "TOK_EQUAL", "TOK_MUL",
  "TOK_MULASS", "TOK_MOD", "TOK_MODASS", "TOK_XOR", "TOK_XORASS",
  "TOK_CAT", "TOK_CATASS", "TOK_BASE", "TOK_BREAK", "TOK_CASE",
  "TOK_CATCH", "TOK_CONST", "TOK_CONTINUE", "TOK_DEFAULT", "TOK_DELEGATE",
  "TOK_DELETE", "TOK_DO", "TOK_ENUM", "TOK_EXTENDS", "TOK_FALSE",
  "TOK_FOR", "TOK_FOREACH", "TOK_FUNCTION", "TOK_IF", "TOK_IN", "TOK_INT",
  "TOK_LOCAL", "TOK_METAFUNCTION", "TOK_NAMESPACE", "TOK_NEW", "TOK_NULL",
  "TOK_RESUME", "TOK_RETURN", "TOK_SWITCH", "TOK_THIS", "TOK_THROW",
  "TOK_TRUE", "TOK_TRY", "TOK_VAR", "TOK_WHILE", "TOK_YIELD", "STOK_FILE",
  "STOK_LINE", "STOK_DATE", "STOK_TIME", "STOK_TIMESTAMP", "STOK_VENDOR",
  "STOK_VERSION", "$accept", "program", "stmts", "stmt", "block",
  "expr_stmt", "primary_expr", "argument_expr_list", "postfix_expr",
  "unary_op", "unary_expr", "multiplicative_expr", "additive_expr",
  "shift_expr", "relational_expr", "equality_expr", "and_expr",
  "exclusive_or_expr", "inclusive_or_expr", "logical_and_expr",
  "logical_or_expr", "conditional_expr", "assignment_op",
  "assignment_expr", "expr", "inner_expr", "boolean", "numeric", "string",
  "keyvalue", "keyvalue_list", "table", "element", "element_list", "array",
  "type_specifier", "decl_stmt", "var_decl_stmt", "getvar_primary_expr",
  "getvar_postfix_expr", "var_decl", "func_decl_arglist", "func_decl",
  "local_func_decl", "anony_func_decl", "selection_stmt", "labeled_stmts",
  "labeled_stmt", "jump_stmt", "iteration_stmt", "namespace_block", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   124,   124,   124,
     124,   124,   124,   124,   125,   125,   125,   125,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   127,   128,
     128,   128,   128,   129,   129,   129,   129,   130,   130,   130,
     131,   131,   131,   132,   132,   132,   132,   132,   133,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   141,
     142,   143,   143,   143,   144,   144,   145,   145,   145,   145,
     146,   147,   147,   147,   147,   147,   148,   148,   149,   149,
     149,   150,   151,   151,   152,   152,   152,   153,   153,   154,
     154,   154,   155,   156,   156,   156,   156,   157,   157,   157,
     158,   158,   158,   158,   159,   159,   159,   159,   160,   160,
     161,   162,   162,   163,   163,   163,   164,   164,   165,   165,
     165,   165,   166,   166,   166,   166,   166,   166,   167,   167,
     167,   167,   167,   167,   167,   167,   168,   168
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     3,     1,     3,
       4,     3,     4,     2,     2,     1,     1,     1,     1,     1,
       2,     2,     2,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     5,     1,     3,     1,     3,     2,     3,
       4,     1,     1,     3,     2,     3,     4,     1,     1,     1,
       1,     1,     2,     1,     2,     3,     4,     1,     3,     4,
       2,     4,     3,     5,     1,     2,     3,     4,     5,     6,
       2,     4,     5,     7,     5,     7,     1,     2,     4,     3,
       3,     2,     2,     2,     2,     3,     2,     2,     5,     7,
       6,     7,     6,     7,     7,     7,     5,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,   123,   100,    96,    97,    98,    99,    36,     0,
      35,     0,    38,     0,     0,    14,     0,    37,     0,     0,
       0,    95,     0,     0,     0,     0,   118,     0,     0,     0,
      23,    94,   117,     0,     0,     3,     4,    16,     6,    28,
      39,     0,    43,    47,    50,    53,    58,    61,    63,    65,
      67,    69,    71,    86,    90,     0,    17,    18,    19,    20,
       0,     7,   119,    21,     0,   120,   121,     8,     9,    10,
      11,   114,     0,     0,    91,   111,    92,   112,     0,    93,
      41,    40,     0,    13,     0,   124,   153,   152,     0,     0,
       0,     0,   127,     0,     0,   140,     0,   154,     0,   156,
     157,     0,     0,     0,     0,     1,     5,     0,     0,    34,
      33,     0,    42,    74,    75,    76,    77,    78,    79,    80,
      81,    73,    82,    83,    84,    85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,   130,     0,   122,
       0,   101,   108,     0,   106,     0,   104,     0,   115,     0,
      22,    12,     0,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,   125,     0,     0,    29,     0,
      31,     0,    24,    25,    26,    87,    88,    89,    45,    44,
      46,    43,    49,    48,    51,    52,    54,    56,    55,    57,
      60,    59,    62,    64,    66,    68,    70,     0,     0,   132,
       0,     0,     0,   109,     0,   134,     0,     0,     0,   116,
     113,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       0,   167,     0,     0,   126,     0,    30,    32,     0,     0,
     131,     0,     0,   102,   105,   110,   107,   141,   135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   138,
       0,   144,   166,     0,   158,    27,    72,   133,     0,   142,
     136,     0,     0,   160,     0,   162,     0,     0,     0,   139,
       0,     0,     0,     0,   146,   103,   137,   159,   161,   163,
     164,   165,   143,     0,   151,   145,   147,   149,   150,   148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    34,    35,    36,    37,    38,    39,   181,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   126,    54,    55,    75,    56,    57,    58,   154,
     155,    76,    77,    78,    59,    60,    61,    62,    63,    93,
      64,   218,    65,    66,    79,    67,   283,   284,    68,    69,
      70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -183
static const yytype_int16 yypact[] =
{
     663,   864,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  1288,
    -183,  1288,  -183,  1076,   271,  -183,    47,  -183,    11,    18,
     663,  -183,    57,    59,    -2,    72,     7,    -2,   917,    73,
      79,  -183,  -183,    76,   135,   663,  -183,  -183,  -183,  -183,
     157,  1288,   121,    -1,    -6,    26,    81,     8,   115,    67,
     114,   117,    -8,  -183,  -183,    85,  -183,  -183,  -183,  -183,
      -2,  -183,  -183,  -183,    63,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,    19,    88,  -183,  -183,  -183,  -183,   -11,  -183,
    -183,  -183,    94,  -183,   369,  -183,  -183,  -183,    44,   761,
     797,    79,  -183,    31,  1288,  -183,    34,  -183,    91,  -183,
    -183,  1288,   143,  1288,  1288,  -183,  -183,   144,  1288,  -183,
    -183,   970,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  1076,  1288,  1288,  1288,
    1288,  1288,  1288,  1288,  1288,  1288,  1288,  1288,  1288,  1288,
    1288,  1288,  1288,  1288,  1288,  1076,  -183,    16,    -2,  -183,
    1288,    95,  -183,    97,  -183,    15,  -183,     1,  -183,  1023,
    -183,  -183,   111,  -183,  1129,  1129,    74,   -32,   181,  1288,
       2,   139,   467,  -183,   141,  -183,   142,   147,  -183,   148,
    -183,   -13,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,    -1,    -1,    -6,    -6,    26,    26,    26,    26,
      81,    81,     8,   115,    67,   114,   117,   137,  1076,    49,
     149,  1076,  1076,  -183,    22,  -183,   146,   196,   -12,  -183,
    -183,  1288,  1182,  1235,  1076,  1076,  -183,   152,   146,     9,
     663,  -183,   565,   155,  -183,   663,  -183,  -183,  1288,  1076,
    -183,  1076,   150,  -183,  -183,  -183,  -183,  -183,  -183,   146,
       4,   161,   663,   162,   663,   163,   170,   172,  -183,  -183,
     146,   229,  -183,   -10,  -183,  -183,  -183,  -183,  1076,  -183,
    -183,   221,   173,  -183,   663,  -183,   663,   663,   663,  -183,
     663,  1288,   171,   -18,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,   174,   663,  -183,  -183,   663,   663,   663
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,   -14,    -4,  -182,   -69,  -183,  -183,  -183,  -183,
      43,   -42,     5,   -15,    -5,   100,    96,   101,    99,   102,
    -183,  -183,  -183,  -108,     0,    -9,  -183,  -183,   -67,    30,
    -183,   -20,    86,  -183,  -183,  -145,  -183,   158,   -17,   -21,
     159,    82,   -24,  -183,   -19,  -183,  -183,   -30,  -183,  -183,
    -183
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      84,    74,    95,   182,    82,   153,    96,    92,    99,   100,
      92,     2,   217,    74,   215,   215,    88,   270,   185,   127,
     164,   144,   168,   169,   130,   217,   150,   131,    98,   150,
     148,   106,   151,     3,   247,   151,     3,   168,   169,   147,
     168,   169,   295,    92,   237,   249,   259,   158,   156,   238,
     250,   159,    80,   145,    81,   168,   169,   138,   216,   228,
      85,   281,   225,    16,   132,   282,   260,   269,   128,   281,
     129,   250,   133,   282,    86,   213,   139,   214,   279,   152,
     106,    87,   245,   208,   112,   102,   103,   170,   192,   193,
     166,   183,   184,   172,   171,   222,   223,   163,   163,    24,
     163,   174,    91,   176,   177,   271,   186,   187,   179,    32,
      32,    24,    32,    89,    24,    90,   241,   134,   135,   196,
     197,   198,   199,   136,   137,   148,   149,   209,    94,   101,
     265,    92,   104,   200,   201,   105,   207,   194,   195,   140,
     141,   142,   113,   143,   157,    74,   114,   153,   146,   115,
     210,   160,   116,   162,   173,   117,   175,   178,   232,    74,
     118,   212,   211,   107,   108,   119,   120,   221,   224,   227,
     188,   189,   190,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   121,   109,
     156,   122,   110,   123,   226,   124,   230,   125,   233,   240,
     234,   239,   243,   244,   235,    14,   236,   242,    74,   248,
     258,    74,    74,   111,   263,   256,   257,   268,   272,   274,
     276,   251,   253,   255,    74,    74,   261,   277,   106,   278,
     266,   264,   267,   280,   286,   294,   287,   203,   297,    74,
     202,    74,   205,   204,   246,   220,   206,   165,   273,   167,
     275,     0,   229,   296,     0,     0,     0,     0,     0,   285,
       0,     0,     0,     0,     0,     0,     0,     0,    74,     0,
     288,     0,   289,   290,   291,     0,   292,     0,     1,     0,
     298,   293,     0,   299,     2,     3,     0,     4,     5,     6,
       7,     0,     0,     0,   106,   106,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,    13,     0,     0,
      14,    83,     0,     0,    15,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
       0,     0,     0,    19,     0,     0,     0,    20,     0,     0,
      21,    22,    23,    24,    25,     0,     0,    26,     0,    27,
       0,     0,     0,    28,    29,    30,     1,    31,     0,    32,
      33,     0,     2,     3,     0,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     9,    10,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,    14,   161,
       0,     0,    15,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,    18,     0,     0,
       0,    19,     0,     0,     0,    20,     0,     0,    21,    22,
      23,    24,    25,     0,     0,    26,     0,    27,     0,     0,
       0,    28,    29,    30,     1,    31,     0,    32,    33,     0,
       2,     3,     0,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,    14,   231,     0,     0,
      15,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    18,     0,     0,     0,    19,
       0,     0,     0,    20,     0,     0,    21,    22,    23,    24,
      25,     0,     0,    26,     0,    27,     0,     0,     0,    28,
      29,    30,     1,    31,     0,    32,    33,     0,     2,     3,
       0,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,    14,   262,     0,     0,    15,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,    18,     0,     0,     0,    19,     0,     0,
       0,    20,     0,     0,    21,    22,    23,    24,    25,     0,
       0,    26,     0,    27,     0,     0,     0,    28,    29,    30,
       1,    31,     0,    32,    33,     0,     2,     3,     0,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     9,    10,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,     0,     0,     0,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    18,     0,     0,     0,    19,     0,     0,     0,    20,
       0,     0,    21,    22,    23,    24,    25,     0,     0,    26,
       0,    27,     0,     0,     0,    28,    29,    30,     1,    31,
       0,    32,    33,     0,     2,     3,     0,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     0,    12,
       2,     3,     0,     4,     5,     6,     7,    13,     0,     0,
      14,     0,     0,     0,    15,     0,    16,     8,     0,     9,
      10,     0,    11,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
      21,     0,     0,    13,     0,     0,     0,   163,     0,     0,
       0,     0,    16,     0,     0,    30,     0,    31,     0,    32,
       0,     1,    17,     0,     0,     0,     0,     2,     3,     0,
       4,     5,     6,     7,     0,     0,    21,     0,     0,     0,
       0,     0,     0,   163,     8,     0,     9,    10,     0,    11,
       0,    30,     0,    31,     0,    32,     0,     0,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,     0,     0,
      13,     0,    71,    72,     1,     0,     0,     0,     0,    16,
       2,     3,     0,     4,     5,     6,     7,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,     0,    11,    21,     0,     0,    73,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,    30,     0,
      31,     0,     0,    13,     0,     0,    72,     1,     0,     0,
      97,     0,    16,     2,     3,     0,     4,     5,     6,     7,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,     0,    11,    21,     0,     0,    73,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       0,    30,     0,    31,     0,     0,    13,   180,     0,    72,
       1,     0,     0,     0,     0,    16,     2,     3,     0,     4,
       5,     6,     7,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     9,    10,     0,    11,    21,
       0,     0,    73,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,    30,     0,    31,     0,     0,    13,
       0,   219,    72,     1,     0,     0,     0,     0,    16,     2,
       3,     0,     4,     5,     6,     7,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     9,    10,
       0,    11,    21,     0,     0,    73,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     0,     0,    30,     0,    31,
       0,     0,    13,     0,     0,    72,     1,     0,     0,     0,
       0,    16,     2,     3,     0,     4,     5,     6,     7,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     9,    10,     0,    11,    21,     0,     0,    73,     0,
       0,     0,     0,     0,     0,     0,     0,    12,     0,     0,
      30,     0,    31,     0,     0,    13,     0,     0,    14,     1,
       0,     0,    15,     0,    16,     2,     3,     0,     4,     5,
       6,     7,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     9,    10,     0,    11,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     0,    30,     0,    31,     0,     0,    13,   252,
       0,     0,     1,     0,     0,     0,     0,    16,     2,     3,
       0,     4,     5,     6,     7,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,     0,     0,    30,     0,    31,     0,
       0,    13,   254,     0,     0,     1,     0,     0,     0,     0,
      16,     2,     3,     0,     4,     5,     6,     7,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     0,     0,    30,
       0,    31,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,    31
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-183)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      14,     1,    26,   111,    13,    72,    27,    24,    28,    28,
      27,    13,   157,    13,    13,    13,    20,    13,   126,    20,
      89,    29,     6,     7,    30,   170,     7,    33,    28,     7,
      62,    35,    13,    14,   216,    13,    14,     6,     7,    60,
       6,     7,    60,    60,    57,    57,   228,    58,    72,    62,
      62,    62,     9,    61,    11,     6,     7,    49,    57,    57,
      13,    79,    94,    65,    38,    83,    57,   249,    69,    79,
      71,    62,    46,    83,    63,    60,    68,    62,   260,    60,
      84,    63,    60,    67,    41,     6,     7,    56,   130,   131,
      90,   111,   111,    59,    94,   164,   165,    96,    96,    92,
      96,   101,   104,   103,   104,   250,   126,   126,   108,   108,
     108,    92,   108,    56,    92,    56,    67,    36,    37,   134,
     135,   136,   137,    42,    43,    62,    63,   148,    56,    56,
     238,   148,    56,   138,   139,     0,   145,   132,   133,    24,
      73,    27,    21,    26,    56,   145,    25,   214,    63,    28,
     150,    57,    31,   109,    63,    34,    13,    13,   172,   159,
      39,    64,    67,     6,     7,    44,    45,    56,    94,   169,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,    67,    32,
     214,    70,    35,    72,    13,    74,    57,    76,    57,   208,
      58,    64,   211,   212,    57,    59,    58,    58,   208,    13,
      58,   211,   212,    56,    59,   224,   225,    67,    57,    57,
      57,   221,   222,   223,   224,   225,   230,    57,   232,    57,
     239,   235,   241,     4,    13,    64,    63,   141,    64,   239,
     140,   241,   143,   142,   214,   159,   144,    89,   252,    90,
     254,    -1,   170,   283,    -1,    -1,    -1,    -1,    -1,   268,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   268,    -1,
     274,    -1,   276,   277,   278,    -1,   280,    -1,     7,    -1,
     294,   281,    -1,   297,    13,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    -1,   298,   299,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      59,    60,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    78,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    91,    92,    93,    -1,    -1,    96,    -1,    98,
      -1,    -1,    -1,   102,   103,   104,     7,   106,    -1,   108,
     109,    -1,    13,    14,    -1,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    -1,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    60,
      -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    78,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      91,    92,    93,    -1,    -1,    96,    -1,    98,    -1,    -1,
      -1,   102,   103,   104,     7,   106,    -1,   108,   109,    -1,
      13,    14,    -1,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    59,    60,    -1,    -1,
      63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    91,    92,
      93,    -1,    -1,    96,    -1,    98,    -1,    -1,    -1,   102,
     103,   104,     7,   106,    -1,   108,   109,    -1,    13,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,    60,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    78,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    86,    -1,    -1,    89,    90,    91,    92,    93,    -1,
      -1,    96,    -1,    98,    -1,    -1,    -1,   102,   103,   104,
       7,   106,    -1,   108,   109,    -1,    13,    14,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    -1,    -1,    -1,    63,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    91,    92,    93,    -1,    -1,    96,
      -1,    98,    -1,    -1,    -1,   102,   103,   104,     7,   106,
      -1,   108,   109,    -1,    13,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    48,
      13,    14,    -1,    16,    17,    18,    19,    56,    -1,    -1,
      59,    -1,    -1,    -1,    63,    -1,    65,    30,    -1,    32,
      33,    -1,    35,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    56,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    65,    -1,    -1,   104,    -1,   106,    -1,   108,
      -1,     7,    75,    -1,    -1,    -1,    -1,    13,    14,    -1,
      16,    17,    18,    19,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    30,    -1,    32,    33,    -1,    35,
      -1,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    58,    59,     7,    -1,    -1,    -1,    -1,    65,
      13,    14,    -1,    16,    17,    18,    19,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    35,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,   104,    -1,
     106,    -1,    -1,    56,    -1,    -1,    59,     7,    -1,    -1,
      63,    -1,    65,    13,    14,    -1,    16,    17,    18,    19,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    -1,    35,    89,    -1,    -1,    92,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,   104,    -1,   106,    -1,    -1,    56,    57,    -1,    59,
       7,    -1,    -1,    -1,    -1,    65,    13,    14,    -1,    16,
      17,    18,    19,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,   104,    -1,   106,    -1,    -1,    56,
      -1,    58,    59,     7,    -1,    -1,    -1,    -1,    65,    13,
      14,    -1,    16,    17,    18,    19,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      -1,    35,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,   104,    -1,   106,
      -1,    -1,    56,    -1,    -1,    59,     7,    -1,    -1,    -1,
      -1,    65,    13,    14,    -1,    16,    17,    18,    19,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    -1,    35,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
     104,    -1,   106,    -1,    -1,    56,    -1,    -1,    59,     7,
      -1,    -1,    63,    -1,    65,    13,    14,    -1,    16,    17,
      18,    19,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    -1,    35,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,   104,    -1,   106,    -1,    -1,    56,    57,
      -1,    -1,     7,    -1,    -1,    -1,    -1,    65,    13,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,
      35,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,   104,    -1,   106,    -1,
      -1,    56,    57,    -1,    -1,     7,    -1,    -1,    -1,    -1,
      65,    13,    14,    -1,    16,    17,    18,    19,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    -1,    35,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,   104,
      -1,   106,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    14,    16,    17,    18,    19,    30,    32,
      33,    35,    48,    56,    59,    63,    65,    75,    78,    82,
      86,    89,    90,    91,    92,    93,    96,    98,   102,   103,
     104,   106,   108,   109,   119,   120,   121,   122,   123,   124,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   141,   142,   144,   145,   146,   152,
     153,   154,   155,   156,   158,   160,   161,   163,   166,   167,
     168,    58,    59,    92,   142,   143,   149,   150,   151,   162,
     128,   128,   143,    60,   120,    13,    63,    63,   121,    56,
      56,   104,   156,   157,    56,   160,   157,    63,   142,   149,
     162,    56,     6,     7,    56,     0,   121,     6,     7,    32,
      35,    56,   128,    21,    25,    28,    31,    34,    39,    44,
      45,    67,    70,    72,    74,    76,   140,    20,    69,    71,
      30,    33,    38,    46,    36,    37,    42,    43,    49,    68,
      24,    73,    27,    26,    29,    61,    63,   157,    62,    63,
       7,    13,    60,   146,   147,   148,   160,    56,    58,    62,
      57,    60,   109,    96,   123,   155,   142,   158,     6,     7,
      56,   142,    59,    63,   142,    13,   142,   142,    13,   142,
      57,   125,   141,   149,   162,   141,   149,   162,   128,   128,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     132,   132,   133,   134,   135,   136,   137,   143,    67,   157,
     142,    67,    64,    60,    62,    13,    57,   153,   159,    58,
     150,    56,   123,   123,    94,    94,    13,   142,    57,   159,
      57,    60,   120,    57,    58,    57,    58,    57,    62,    64,
     143,    67,    58,   143,   143,    60,   147,   122,    13,    57,
      62,   142,    57,   142,    57,   142,   143,   143,    58,   122,
      57,   121,    60,    59,   121,   141,   143,   143,    67,   122,
      13,   153,    57,   121,    57,   121,    57,    57,    57,   122,
       4,    79,    83,   164,   165,   143,    13,    63,   121,   121,
     121,   121,   121,   142,    64,    60,   165,    64,   120,   120
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 176 "yyparser.y"
    { PARSER->setProgramBlockAST(NULL); }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 177 "yyparser.y"
    { PARSER->setProgramBlockAST((yyvsp[(1) - (1)].block)); }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 181 "yyparser.y"
    { (yyval.block) = new BlockAST(); PARSER->addNodeAST((yyval.block)); if((yyvsp[(1) - (1)].node) != NULL) (yyval.block)->m_statements.push_back((yyvsp[(1) - (1)].node)); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 182 "yyparser.y"
    { if((yyvsp[(2) - (2)].node) != NULL) (yyvsp[(1) - (2)].block)->m_statements.push_back((yyvsp[(2) - (2)].node)); }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 186 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 187 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 188 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 189 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 190 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 191 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 195 "yyparser.y"
    { (yyval.block) = (yyvsp[(2) - (3)].block); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 196 "yyparser.y"
    { (yyval.block) = new BlockAST(); PARSER->addNodeAST((yyval.block)); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 200 "yyparser.y"
    { (yyval.node) = NULL; }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 201 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 202 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].block); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 206 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 207 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 208 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 210 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 211 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].getvar); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 213 "yyparser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 214 "yyparser.y"
    { (yyval.node) = new GetVarAST(NULL, "this"); PARSER->addNodeAST((yyval.node)); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 218 "yyparser.y"
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[(1) - (1)].node)); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 219 "yyparser.y"
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[(1) - (1)].node)); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 220 "yyparser.y"
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[(1) - (1)].func)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 221 "yyparser.y"
    { (yyvsp[(1) - (3)].nodelist)->push_back((yyvsp[(3) - (3)].node)); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 225 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 226 "yyparser.y"
    { (yyval.node) = new GetVarAST((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].token).getRawString()); PARSER->addNodeAST((yyval.node)); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 227 "yyparser.y"
    { (yyval.node) = new GetVarAST((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 228 "yyparser.y"
    { (yyval.node) = new CallAST((yyvsp[(1) - (3)].node), NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 229 "yyparser.y"
    { (yyval.node) = new CallAST((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 230 "yyparser.y"
    { (yyval.node) = new PostfixIncrementAST((yyvsp[(1) - (2)].node), TOK_PLUSPLUS); PARSER->addNodeAST((yyval.node)); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 231 "yyparser.y"
    { (yyval.node) = new PostfixIncrementAST((yyvsp[(1) - (2)].node), TOK_MINUSMINUS); PARSER->addNodeAST((yyval.node)); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 243 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 244 "yyparser.y"
    { (yyval.node) = new UnaryAST((yyvsp[(2) - (2)].node), TOK_PLUSPLUS); PARSER->addNodeAST((yyval.node)); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 245 "yyparser.y"
    { (yyval.node) = new UnaryAST((yyvsp[(2) - (2)].node), TOK_MINUSMINUS); PARSER->addNodeAST((yyval.node)); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 246 "yyparser.y"
    { (yyval.node) = new UnaryAST((yyvsp[(2) - (2)].node), (yyvsp[(1) - (2)].token).m_type); PARSER->addNodeAST((yyval.node)); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 250 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 251 "yyparser.y"
    { (yyval.node) = new MultiplicativeAST((yyvsp[(1) - (3)].node), TOK_MUL, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 252 "yyparser.y"
    { (yyval.node) = new MultiplicativeAST((yyvsp[(1) - (3)].node), TOK_DIV, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 253 "yyparser.y"
    { (yyval.node) = new MultiplicativeAST((yyvsp[(1) - (3)].node), TOK_MOD, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 257 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 258 "yyparser.y"
    { (yyval.node) = new AdditiveAST((yyvsp[(1) - (3)].node), TOK_PLUS, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 259 "yyparser.y"
    { (yyval.node) = new AdditiveAST((yyvsp[(1) - (3)].node), TOK_MINUS, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 263 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 264 "yyparser.y"
    { (yyval.node) = new ShiftAST((yyvsp[(1) - (3)].node), TOK_SHL, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 265 "yyparser.y"
    { (yyval.node) = new ShiftAST((yyvsp[(1) - (3)].node), TOK_SHR, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 269 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 270 "yyparser.y"
    { (yyval.node) = new RelationalAST((yyvsp[(1) - (3)].node), TOK_LT, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 271 "yyparser.y"
    { (yyval.node) = new RelationalAST((yyvsp[(1) - (3)].node), TOK_GT, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 272 "yyparser.y"
    { (yyval.node) = new RelationalAST((yyvsp[(1) - (3)].node), TOK_LE, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 273 "yyparser.y"
    { (yyval.node) = new RelationalAST((yyvsp[(1) - (3)].node), TOK_GE, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 277 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 278 "yyparser.y"
    { (yyval.node) = new EqualityAST((yyvsp[(1) - (3)].node), TOK_EQUAL, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 279 "yyparser.y"
    { (yyval.node) = new EqualityAST((yyvsp[(1) - (3)].node), TOK_NOTEQUAL, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 283 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 284 "yyparser.y"
    { (yyval.node) = new AndAST((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 288 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 289 "yyparser.y"
    { (yyval.node) = new ExclusiveOrAST((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 293 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 294 "yyparser.y"
    { (yyval.node) = new InclusiveOrAST((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 298 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 299 "yyparser.y"
    { (yyval.node) = new LogicalAndAST((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 303 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 304 "yyparser.y"
    { (yyval.node) = new LogicalOrAST((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 308 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 309 "yyparser.y"
    { (yyval.node) = new ConditionalAST((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 329 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 330 "yyparser.y"
    { (yyval.node) = new AssignmentAST((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].token).m_type, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 331 "yyparser.y"
    { (yyval.node) = new AssignmentAST((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].token).m_type, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 332 "yyparser.y"
    { (yyval.node) = new AssignmentAST((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].token).m_type, (yyvsp[(3) - (3)].func)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 336 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 340 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 341 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 342 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].func); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 346 "yyparser.y"
    { (yyval.node) = new BooleanAST(1); PARSER->addNodeAST((yyval.node)); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 347 "yyparser.y"
    { (yyval.node) = new BooleanAST(0); PARSER->addNodeAST((yyval.node)); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 351 "yyparser.y"
    { (yyval.node) = new Int32AST((yyvsp[(1) - (1)].token).m_integerValue); PARSER->addNodeAST((yyval.node)); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 352 "yyparser.y"
    { (yyval.node) = new Int64AST((yyvsp[(1) - (1)].token).m_integerValue); PARSER->addNodeAST((yyval.node)); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 353 "yyparser.y"
    { (yyval.node) = new FloatAST((yyvsp[(1) - (1)].token).m_doubleValue); PARSER->addNodeAST((yyval.node)); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 354 "yyparser.y"
    { (yyval.node) = new DoubleAST((yyvsp[(1) - (1)].token).m_doubleValue); PARSER->addNodeAST((yyval.node)); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 358 "yyparser.y"
    { (yyval.node) = new StringAST((yyvsp[(1) - (1)].token).toUTF8String(), (yyvsp[(1) - (1)].token).m_postfix); PARSER->addNodeAST((yyval.node)); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 362 "yyparser.y"
    { (yyval.node) = new KeyValueAST((yyvsp[(1) - (1)].token).getRawString(), NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 363 "yyparser.y"
    { (yyval.node) = new KeyValueAST((yyvsp[(1) - (3)].token).getRawString(), (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 364 "yyparser.y"
    { (yyval.node) = new KeyValueAST((yyvsp[(2) - (5)].node), (yyvsp[(5) - (5)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 365 "yyparser.y"
    { (yyval.node) = new KeyValueAST("", (yyvsp[(1) - (1)].func)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 367 "yyparser.y"
    { (yyval.node) = new KeyValueAST(((StringAST*)(yyvsp[(1) - (3)].node))->m_val, (yyvsp[(3) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 371 "yyparser.y"
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[(1) - (1)].node)); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 372 "yyparser.y"
    { (yyvsp[(1) - (3)].nodelist)->push_back((yyvsp[(3) - (3)].node)); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 376 "yyparser.y"
    { (yyval.node) = new TableAST(NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 377 "yyparser.y"
    { (yyval.node) = new TableAST((yyvsp[(2) - (3)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 378 "yyparser.y"
    { (yyval.node) = new TableAST((yyvsp[(2) - (4)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 382 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 386 "yyparser.y"
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[(1) - (1)].node)); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 387 "yyparser.y"
    { (yyvsp[(1) - (3)].nodelist)->push_back((yyvsp[(3) - (3)].node)); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 391 "yyparser.y"
    { (yyval.node) = new ArrayAST(NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 392 "yyparser.y"
    { (yyval.node) = new ArrayAST((yyvsp[(2) - (3)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 393 "yyparser.y"
    { (yyval.node) = new ArrayAST((yyvsp[(2) - (4)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 404 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 405 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].func); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 406 "yyparser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].func); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 410 "yyparser.y"
    { (yyval.node) = new VariableDeclarationListAST((yyvsp[(1) - (2)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 414 "yyparser.y"
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[(1) - (1)].token).getRawString(), GetVarAST::NONE); PARSER->addNodeAST((yyval.getvar)); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 415 "yyparser.y"
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[(2) - (2)].token).getRawString(), GetVarAST::GLOBAL); PARSER->addNodeAST((yyval.getvar)); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 416 "yyparser.y"
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[(3) - (3)].token).getRawString(), GetVarAST::THIS); PARSER->addNodeAST((yyval.getvar)); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 417 "yyparser.y"
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[(3) - (4)].node), GetVarAST::THIS); PARSER->addNodeAST((yyval.getvar)); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 423 "yyparser.y"
    { (yyval.getvar) = (yyvsp[(1) - (1)].getvar); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 424 "yyparser.y"
    { (yyval.getvar) = new GetVarAST((yyvsp[(1) - (3)].getvar), (yyvsp[(3) - (3)].token).getRawString()); PARSER->addNodeAST((yyval.getvar)); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 425 "yyparser.y"
    { (yyval.getvar) = new GetVarAST((yyvsp[(1) - (4)].getvar), (yyvsp[(3) - (4)].node)); PARSER->addNodeAST((yyval.getvar)); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 429 "yyparser.y"
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[(2) - (2)].getvar), NULL, ((yyvsp[(1) - (2)].token).m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 437 "yyparser.y"
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[(2) - (4)].getvar), (yyvsp[(4) - (4)].node), ((yyvsp[(1) - (4)].token).m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 445 "yyparser.y"
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyval.nodelist)->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[(3) - (3)].getvar), NULL, node0->m_isLocal);
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 452 "yyparser.y"
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyval.nodelist)->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[(3) - (5)].getvar), (yyvsp[(5) - (5)].node), node0->m_isLocal);
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 461 "yyparser.y"
    { (yyval.arglist) = new StringList(); PARSER->addNodeAST((yyval.arglist)); (yyval.arglist)->push_back((yyvsp[(1) - (1)].token).getRawString()); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 462 "yyparser.y"
    { (yyval.arglist) = new StringList(); PARSER->addNodeAST((yyval.arglist)); (yyval.arglist)->push_back((yyvsp[(2) - (2)].token).getRawString()); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 464 "yyparser.y"
    {
            (yyvsp[(1) - (3)].arglist)->push_back((yyvsp[(3) - (3)].token).getRawString());
            if((yyvsp[(1) - (3)].arglist)->m_hasDuplicateStr)
            {
                yyerror("argument name is duplicate");
                YYABORT;
            }
        }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 473 "yyparser.y"
    {
            (yyvsp[(1) - (4)].arglist)->push_back((yyvsp[(4) - (4)].token).getRawString());
            if((yyvsp[(1) - (4)].arglist)->m_hasDuplicateStr)
            {
                yyerror("argument name is duplicate");
                YYABORT;
            }
        }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 485 "yyparser.y"
    {
            (yyval.func) = new FunctionAST((yyvsp[(2) - (5)].getvar), NULL, (yyvsp[(5) - (5)].block));
            PARSER->addNodeAST((yyval.func));
        }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 490 "yyparser.y"
    {
            (yyval.func) = new FunctionAST((yyvsp[(2) - (6)].getvar), (yyvsp[(4) - (6)].arglist), (yyvsp[(6) - (6)].block));
            PARSER->addNodeAST((yyval.func));
        }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 497 "yyparser.y"
    { (yyvsp[(2) - (2)].func)->m_isLocal = true; (yyval.func) = (yyvsp[(2) - (2)].func); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 501 "yyparser.y"
    {
            (yyval.func) = new FunctionAST(NULL, NULL, (yyvsp[(4) - (4)].block));
            PARSER->addNodeAST((yyval.func));
        }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 506 "yyparser.y"
    {
            (yyval.func) = new FunctionAST(NULL, (yyvsp[(3) - (5)].arglist), (yyvsp[(5) - (5)].block));
            PARSER->addNodeAST((yyval.func));
        }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 513 "yyparser.y"
    { (yyval.node) = new IfElseAST((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 514 "yyparser.y"
    { (yyval.node) = new IfElseAST((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 516 "yyparser.y"
    { (yyval.node) = new SwitchAST((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].nodelist)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 520 "yyparser.y"
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->add_case_ast((CaseAST*)((yyvsp[(1) - (1)].node))); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 522 "yyparser.y"
    {
            (yyvsp[(1) - (2)].nodelist)->add_case_ast((CaseAST*)((yyvsp[(2) - (2)].node)));
            if((yyvsp[(1) - (2)].nodelist)->m_hasMultipleDefaultStmt)
            {
                yyerror("multiple default labels in one switch");
                YYABORT;
            }
        }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 533 "yyparser.y"
    { (yyval.node) = new CaseAST((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].block)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 534 "yyparser.y"
    { (yyval.node) = new CaseAST((yyvsp[(2) - (3)].node), NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 535 "yyparser.y"
    { (yyval.node) = new CaseAST(NULL, (yyvsp[(3) - (3)].block)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 536 "yyparser.y"
    { (yyval.node) = new CaseAST(NULL, NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 540 "yyparser.y"
    { (yyval.node) = new ContinueAST(); PARSER->addNodeAST((yyval.node)); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 541 "yyparser.y"
    { (yyval.node) = new BreakAST(); PARSER->addNodeAST((yyval.node)); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 542 "yyparser.y"
    { (yyval.node) = new ReturnAST(NULL); PARSER->addNodeAST((yyval.node)); }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 543 "yyparser.y"
    { (yyval.node) = new ReturnAST((yyvsp[(2) - (3)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 544 "yyparser.y"
    { (yyval.node) = new ReturnAST((yyvsp[(2) - (2)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 545 "yyparser.y"
    { (yyval.node) = new ReturnAST((yyvsp[(2) - (2)].func)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 549 "yyparser.y"
    { (yyval.node) = new WhileAST((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 550 "yyparser.y"
    { (yyval.node) = new DoWhileAST((yyvsp[(5) - (7)].node), (yyvsp[(2) - (7)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 551 "yyparser.y"
    { (yyval.node) = new ForAST((yyvsp[(3) - (6)].node), (yyvsp[(4) - (6)].node), NULL, (yyvsp[(6) - (6)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 552 "yyparser.y"
    { (yyval.node) = new ForAST((yyvsp[(3) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 553 "yyparser.y"
    { (yyval.node) = new ForAST((yyvsp[(3) - (6)].node), (yyvsp[(4) - (6)].node), NULL, (yyvsp[(6) - (6)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 554 "yyparser.y"
    { (yyval.node) = new ForAST((yyvsp[(3) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 555 "yyparser.y"
    { (yyval.node) = new ForeachAST((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 556 "yyparser.y"
    { (yyval.node) = new ForeachAST((yyvsp[(3) - (7)].nodelist), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 560 "yyparser.y"
    { (yyval.node) = new NamespaceAST((yyvsp[(2) - (5)].getvar), (yyvsp[(4) - (5)].block)); PARSER->addNodeAST((yyval.node)); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 561 "yyparser.y"
    { (yyval.node) = new NamespaceAST((yyvsp[(2) - (4)].getvar), NULL); PARSER->addNodeAST((yyval.node)); }
    break;


/* Line 1787 of yacc.c  */
#line 2960 "yyparser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 564 "yyparser.y"


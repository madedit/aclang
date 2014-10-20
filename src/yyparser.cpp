/* A Bison parser, made by GNU Bison 3.0.2.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yyparser.y" /* yacc.c:339  */

/* see copyright notice in aclang.h */
#include "ac_ast.h"
#include "ac_token.h"
#include "ac_parser.h"

extern int yylex(YYSTYPE* yylval, void* parser);
extern int yyparse(void* parser);

#define PARSER ((acParser*)parser)

#define yyerror(P, MSG) ((acParser*)P)->getMsgHandler()->error(yylval.token, MSG)
//int yyerror(const char *s) { std::printf("Error: %s\n", s); return 1; }


#line 82 "yyparser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 33 "yyparser.y" /* yacc.c:355  */

    acToken token;
    NodeAST* node;
    BlockAST* block;
    GetVarAST* getvar;
    FunctionAST* func;
    StringList* arglist;
    NodeASTList* nodelist;

#line 250 "yyparser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void* parser);

#endif /* !YY_YY_YYPARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 264 "yyparser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1292

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   372

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   175,   175,   176,   180,   181,   185,   186,   187,   188,
     189,   190,   194,   195,   199,   200,   201,   205,   206,   207,
     208,   210,   211,   213,   214,   218,   219,   220,   221,   222,
     223,   227,   228,   229,   230,   231,   232,   233,   237,   238,
     239,   240,   244,   245,   246,   247,   251,   252,   253,   254,
     258,   259,   260,   264,   265,   266,   270,   271,   272,   273,
     274,   278,   279,   280,   284,   285,   289,   290,   294,   295,
     299,   300,   304,   305,   309,   310,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   330,
     331,   332,   333,   337,   341,   342,   343,   347,   348,   352,
     353,   354,   355,   359,   363,   368,   373,   378,   390,   398,
     399,   403,   404,   405,   409,   413,   414,   418,   419,   420,
     424,   425,   431,   432,   433,   437,   441,   442,   443,   444,
     450,   451,   452,   456,   464,   472,   479,   489,   495,   501,
     510,   522,   527,   535,   539,   544,   552,   554,   556,   561,
     567,   579,   580,   581,   582,   586,   587,   588,   589,   590,
     591,   595,   596,   597,   598,   599,   600,   601,   605,   615,
     625,   661,   662
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
  "labeled_stmt", "jump_stmt", "iteration_stmt", "foreach_stmt",
  "namespace_block", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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

#define YYPACT_NINF -148

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-148)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      46,   751,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  1186,
    -148,  1186,  -148,   974,   323,  -148,    35,  -148,   -37,     7,
      46,  -148,    36,     8,    47,    -9,     8,  -148,   815,    52,
      51,  -148,  -148,    77,    74,    46,  -148,  -148,  -148,  -148,
      37,  1186,  1204,    29,   130,   -16,   136,   -31,    64,    72,
      92,   125,   -15,  -148,  -148,    90,  -148,  -148,  -148,  -148,
       8,  -148,  -148,  -148,   106,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,    83,   114,  -148,  -148,  -148,  -148,   -20,
    -148,  -148,  -148,   119,  -148,   421,  -148,  -148,  -148,    84,
     715,    51,  -148,   111,  1186,  -148,     9,  -148,   135,  -148,
    -148,  1186,   186,  1186,  1186,  -148,  -148,   187,  1186,  -148,
    -148,   868,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,   974,  1186,  1186,  1186,
    1186,  1186,  1186,  1186,  1186,  1186,  1186,  1186,  1186,  1186,
    1186,  1186,  1186,  1186,  1186,   974,  -148,    13,     8,  -148,
    1186,   134,  -148,   139,  -148,    63,  -148,    14,  -148,   921,
    -148,  -148,   149,  -148,  1027,   124,  1027,   102,   193,  1186,
      18,   151,   519,  -148,   152,  -148,   153,   159,  -148,   163,
    -148,   -10,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,    29,    29,   130,   130,   -16,   -16,   -16,   -16,
     136,   136,   -31,    64,    72,    92,   125,   146,   974,    22,
     164,   974,   974,  -148,   127,  -148,   158,   212,     4,  -148,
    -148,  1186,  1080,     8,   974,  1133,   974,  -148,   169,   158,
      20,    46,  -148,   617,   170,  -148,    46,  -148,  -148,   974,
     974,  -148,   974,   161,  -148,  -148,  -148,  -148,  -148,  -148,
     158,    -1,   173,    46,   174,    27,   175,    46,   184,   188,
    -148,  -148,   158,   238,  -148,   -29,  -148,  -148,  -148,  -148,
    -148,  -148,   974,  -148,  -148,   233,   190,  -148,    46,   974,
      46,  -148,    46,    46,  -148,    46,  1186,   183,   -28,  -148,
    -148,  -148,  -148,  -148,   191,  -148,  -148,  -148,  -148,   195,
      46,  -148,  -148,    46,    46,    46,  -148,    46
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,   126,   103,    99,   100,   101,   102,    39,     0,
      38,     0,    41,     0,     0,    14,     0,    40,     0,     0,
       0,    98,     0,     0,     0,   121,     0,    17,     0,     0,
      24,    97,   120,     0,     0,     3,     4,    16,     6,    31,
      42,     0,    46,    50,    53,    56,    61,    64,    66,    68,
      70,    72,    74,    89,    93,     0,    18,    19,    20,    21,
       0,     7,   122,    22,     0,   123,   124,     8,     9,    10,
     167,    11,   117,     0,     0,    94,   114,    95,   115,     0,
      96,    44,    43,     0,    13,     0,   127,   156,   155,     0,
       0,     0,   130,     0,     0,   143,     0,   157,     0,   159,
     160,     0,     0,     0,     0,     1,     5,     0,     0,    37,
      36,     0,    45,    77,    78,    79,    80,    81,    82,    83,
      84,    76,    85,    86,    87,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,   133,     0,   125,
       0,   104,   111,     0,   109,     0,   107,     0,   118,     0,
      23,    12,     0,   121,     0,    42,     0,     0,     0,     0,
       0,     0,     0,   158,     0,   128,     0,     0,    32,     0,
      34,     0,    25,    26,    27,    90,    91,    92,    48,    47,
      49,    46,    52,    51,    54,    55,    57,    59,    58,    60,
      63,    62,    65,    67,    69,    71,    73,     0,     0,   135,
       0,     0,     0,   112,     0,   137,     0,     0,     0,   119,
     116,     0,     0,     0,     0,     0,     0,   131,     0,     0,
       0,     0,   172,     0,     0,   129,     0,    33,    35,     0,
       0,   134,     0,     0,   105,   108,   113,   110,   144,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     132,   141,     0,   147,   171,     0,   161,    28,    29,    30,
      75,   136,     0,   145,   139,     0,     0,   163,     0,     0,
       0,   165,     0,     0,   142,     0,     0,     0,     0,   149,
     106,   140,   162,   164,     0,   168,   166,   170,   146,     0,
     154,   148,   150,     0,   152,   153,   169,   151
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,   -14,   -18,   -55,   -79,  -148,  -148,   160,  -148,
     185,   -95,    57,    48,    53,   109,   110,   113,   118,   122,
    -148,  -148,  -148,  -102,    12,    32,  -148,  -148,   -67,    43,
    -148,   -27,   104,  -148,  -148,  -147,  -148,   178,   -19,   -21,
     179,   100,   -17,  -148,   -25,  -148,  -148,   -13,  -148,  -148,
    -148,  -148
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    34,    35,    36,    37,    38,    39,   181,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   126,    54,    55,    76,    56,    57,    58,   154,
     155,    77,    78,    79,    59,    60,    61,    62,    63,    93,
      64,   218,    65,    66,    80,    67,   288,   289,    68,    69,
      70,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      85,    99,    89,   100,    92,    96,   153,    92,    95,   182,
     217,   164,   274,    75,   144,   168,   169,   106,   138,   168,
     169,     2,   132,   217,   185,    75,    87,   215,   168,   169,
     133,   215,   301,   168,   169,   192,   193,   139,   158,   147,
      98,    92,   159,   107,   108,    83,   145,   238,    86,   127,
     286,   286,   239,     1,   287,   287,   156,   102,   103,     2,
       3,   250,     4,     5,     6,     7,   251,   106,   172,   109,
      88,   216,   110,    16,   105,   229,     8,   262,     9,    10,
     208,    11,   251,    23,   183,   222,   184,   225,   140,   242,
     150,   279,    90,   111,    12,   163,   151,     3,   128,   186,
     129,   187,    13,    94,   275,    14,   171,    32,   101,    15,
     163,    16,    91,   174,   163,   176,   177,   168,   169,   142,
     179,    17,    32,   213,    18,   214,    32,   209,    19,    92,
     107,   108,    20,   104,   150,    21,    22,   267,    23,    24,
     151,     3,    25,   152,    26,   141,    27,   153,    28,    29,
      30,   143,    31,   146,    32,    33,   109,    75,   233,   110,
     130,   248,   210,   131,   148,   149,   226,   170,   148,   149,
     157,    75,   134,   135,   261,    23,   160,   207,   136,   137,
     111,   228,   196,   197,   198,   199,   223,   246,   224,   194,
     195,   200,   201,   162,    81,   273,    82,   156,   173,   175,
     178,   211,   255,   212,    92,   221,   227,   284,   231,   234,
     240,   235,   268,   263,   269,   106,   236,    14,   266,    23,
      75,   237,   243,    75,    75,   249,   112,   260,   272,   265,
     276,   278,   280,   252,   254,   277,    75,   258,    75,   281,
     241,   282,   285,   244,   245,   283,   291,   300,   303,   202,
     165,   203,    75,   292,    75,   204,   256,   247,   259,   304,
     293,   205,   295,   220,   296,   297,   206,   298,   166,   167,
     230,     0,   270,     0,   271,   302,     0,     0,     0,     0,
       0,     0,     0,     0,    75,   306,   305,   106,     0,   106,
     307,    75,     0,     0,     0,     0,     0,     0,   299,     0,
       0,     0,     0,     0,   290,     0,     0,     0,     0,     0,
       0,   294,   188,   189,   190,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
       1,     0,     0,     0,     0,     0,     2,     3,     0,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     9,    10,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,    84,     0,     0,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    18,     0,     0,     0,    19,     0,     0,     0,    20,
       0,     0,    21,    22,     0,    23,    24,     0,     0,    25,
       0,    26,     0,    27,     0,    28,    29,    30,     1,    31,
       0,    32,    33,     0,     2,     3,     0,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,    13,     0,     0,
      14,   161,     0,     0,    15,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
       0,     0,     0,    19,     0,     0,     0,    20,     0,     0,
      21,    22,     0,    23,    24,     0,     0,    25,     0,    26,
       0,    27,     0,    28,    29,    30,     1,    31,     0,    32,
      33,     0,     2,     3,     0,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     9,    10,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,    14,   232,
       0,     0,    15,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,    18,     0,     0,
       0,    19,     0,     0,     0,    20,     0,     0,    21,    22,
       0,    23,    24,     0,     0,    25,     0,    26,     0,    27,
       0,    28,    29,    30,     1,    31,     0,    32,    33,     0,
       2,     3,     0,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,    14,   264,     0,     0,
      15,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    18,     0,     0,     0,    19,
       0,     0,     0,    20,     0,     0,    21,    22,     0,    23,
      24,     0,     0,    25,     0,    26,     0,    27,     0,    28,
      29,    30,     1,    31,     0,    32,    33,     0,     2,     3,
       0,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,    12,     2,     3,     0,     4,     5,     6,
       7,    13,     0,     0,    14,     0,     0,     0,    15,     0,
      16,     8,     0,     9,    10,     0,    11,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,    21,     0,     0,    13,     0,    72,
      73,   163,     0,     0,     0,    27,    16,     0,     0,    30,
       0,    31,     1,    32,     0,     0,    17,     0,     2,     3,
       0,     4,     5,     6,     7,     0,     0,     0,     0,     0,
      21,     0,     0,    74,     0,     8,     0,     9,    10,     0,
      11,    27,     0,     0,     0,    30,     0,    31,     0,     0,
       0,     0,     0,    12,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,    73,     1,     0,     0,    97,     0,
      16,     2,     3,     0,     4,     5,     6,     7,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    21,     0,     0,    74,     0,     0,
       0,     0,     0,     0,     0,    27,    12,     0,     0,    30,
       0,    31,     0,     0,    13,   180,     0,    73,     1,     0,
       0,     0,     0,    16,     2,     3,     0,     4,     5,     6,
       7,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,    21,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,    27,    12,
       0,     0,    30,     0,    31,     0,     0,    13,     0,   219,
      73,     1,     0,     0,     0,     0,    16,     2,     3,     0,
       4,     5,     6,     7,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     9,    10,     0,    11,
      21,     0,     0,    74,     0,     0,     0,     0,     0,     0,
       0,    27,    12,     0,     0,    30,     0,    31,     0,     0,
      13,     0,     0,    73,     1,     0,     0,     0,     0,    16,
       2,     3,     0,     4,     5,     6,     7,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,     0,    11,    21,     0,     0,    74,     0,     0,     0,
       0,     0,     0,     0,    27,    12,     0,     0,    30,     0,
      31,     0,     0,    13,     0,     0,    14,     1,     0,     0,
      15,     0,    16,     2,     3,     0,     4,     5,     6,     7,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,     0,    11,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,    12,     0,
       0,    30,     0,    31,     0,     0,    13,   253,     0,     0,
       1,     0,     0,     0,     0,    16,     2,     3,     0,     4,
       5,     6,     7,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     9,    10,     0,    11,    21,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    12,     0,     0,    30,     0,    31,     0,     0,    13,
     257,     0,     0,     1,     0,     0,     0,     0,    16,     2,
       3,     0,     4,     5,     6,     7,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     9,    10,
       0,    11,    21,     0,     0,   113,     0,     0,     0,   114,
       0,     0,   115,    27,    12,   116,     0,    30,   117,    31,
       0,     0,    13,   118,     0,     0,     0,     0,   119,   120,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   121,     0,     0,   122,    21,   123,     0,   124,     0,
     125,     0,     0,     0,     0,     0,    27,     0,     0,     0,
      30,     0,    31
};

static const yytype_int16 yycheck[] =
{
      14,    28,    20,    28,    23,    26,    73,    26,    25,   111,
     157,    90,    13,     1,    29,     6,     7,    35,    49,     6,
       7,    13,    38,   170,   126,    13,    63,    13,     6,     7,
      46,    13,    60,     6,     7,   130,   131,    68,    58,    60,
      28,    60,    62,     6,     7,    13,    61,    57,    13,    20,
      79,    79,    62,     7,    83,    83,    73,     6,     7,    13,
      14,    57,    16,    17,    18,    19,    62,    85,    59,    32,
      63,    57,    35,    65,     0,    57,    30,    57,    32,    33,
      67,    35,    62,    92,   111,   164,   111,   166,    24,    67,
       7,    64,    56,    56,    48,    96,    13,    14,    69,   126,
      71,   126,    56,    56,   251,    59,    94,   108,    56,    63,
      96,    65,   104,   101,    96,   103,   104,     6,     7,    27,
     108,    75,   108,    60,    78,    62,   108,   148,    82,   148,
       6,     7,    86,    56,     7,    89,    90,   239,    92,    93,
      13,    14,    96,    60,    98,    73,   100,   214,   102,   103,
     104,    26,   106,    63,   108,   109,    32,   145,   172,    35,
      30,   216,   150,    33,    62,    63,    64,    56,    62,    63,
      56,   159,    36,    37,   229,    92,    57,   145,    42,    43,
      56,   169,   134,   135,   136,   137,    62,    60,    64,   132,
     133,   138,   139,   109,     9,   250,    11,   214,    63,    13,
      13,    67,   223,    64,   223,    56,    13,   262,    57,    57,
      64,    58,   239,   231,   239,   233,    57,    59,   236,    92,
     208,    58,    58,   211,   212,    13,    41,    58,    67,    59,
      57,    57,    57,   221,   222,   253,   224,   225,   226,   257,
     208,    57,     4,   211,   212,    57,    13,    64,    57,   140,
      90,   141,   240,    63,   242,   142,   224,   214,   226,    64,
     278,   143,   280,   159,   282,   283,   144,   285,    90,    90,
     170,    -1,   240,    -1,   242,   288,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   272,   303,   300,   305,    -1,   307,
     304,   279,    -1,    -1,    -1,    -1,    -1,    -1,   286,    -1,
      -1,    -1,    -1,    -1,   272,    -1,    -1,    -1,    -1,    -1,
      -1,   279,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    60,    -1,    -1,    63,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    -1,    92,    93,    -1,    -1,    96,
      -1,    98,    -1,   100,    -1,   102,   103,   104,     7,   106,
      -1,   108,   109,    -1,    13,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      59,    60,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    78,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    -1,    92,    93,    -1,    -1,    96,    -1,    98,
      -1,   100,    -1,   102,   103,   104,     7,   106,    -1,   108,
     109,    -1,    13,    14,    -1,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    -1,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    60,
      -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    78,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    -1,    96,    -1,    98,    -1,   100,
      -1,   102,   103,   104,     7,   106,    -1,   108,   109,    -1,
      13,    14,    -1,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    59,    60,    -1,    -1,
      63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    -1,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,     7,   106,    -1,   108,   109,    -1,    13,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
      -1,    -1,    -1,    48,    13,    14,    -1,    16,    17,    18,
      19,    56,    -1,    -1,    59,    -1,    -1,    -1,    63,    -1,
      65,    30,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    56,    -1,    58,
      59,    96,    -1,    -1,    -1,   100,    65,    -1,    -1,   104,
      -1,   106,     7,   108,    -1,    -1,    75,    -1,    13,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    -1,    30,    -1,    32,    33,    -1,
      35,   100,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,     7,    -1,    -1,    63,    -1,
      65,    13,    14,    -1,    16,    17,    18,    19,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    -1,    35,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,    48,    -1,    -1,   104,
      -1,   106,    -1,    -1,    56,    57,    -1,    59,     7,    -1,
      -1,    -1,    -1,    65,    13,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    -1,    35,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    48,
      -1,    -1,   104,    -1,   106,    -1,    -1,    56,    -1,    58,
      59,     7,    -1,    -1,    -1,    -1,    65,    13,    14,    -1,
      16,    17,    18,    19,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   100,    48,    -1,    -1,   104,    -1,   106,    -1,    -1,
      56,    -1,    -1,    59,     7,    -1,    -1,    -1,    -1,    65,
      13,    14,    -1,    16,    17,    18,    19,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    35,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,    48,    -1,    -1,   104,    -1,
     106,    -1,    -1,    56,    -1,    -1,    59,     7,    -1,    -1,
      63,    -1,    65,    13,    14,    -1,    16,    17,    18,    19,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    -1,    35,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    48,    -1,
      -1,   104,    -1,   106,    -1,    -1,    56,    57,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    65,    13,    14,    -1,    16,
      17,    18,    19,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,    48,    -1,    -1,   104,    -1,   106,    -1,    -1,    56,
      57,    -1,    -1,     7,    -1,    -1,    -1,    -1,    65,    13,
      14,    -1,    16,    17,    18,    19,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      -1,    35,    89,    -1,    -1,    21,    -1,    -1,    -1,    25,
      -1,    -1,    28,   100,    48,    31,    -1,   104,    34,   106,
      -1,    -1,    56,    39,    -1,    -1,    -1,    -1,    44,    45,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    70,    89,    72,    -1,    74,    -1,
      76,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,
     104,    -1,   106
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    14,    16,    17,    18,    19,    30,    32,
      33,    35,    48,    56,    59,    63,    65,    75,    78,    82,
      86,    89,    90,    92,    93,    96,    98,   100,   102,   103,
     104,   106,   108,   109,   119,   120,   121,   122,   123,   124,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   141,   142,   144,   145,   146,   152,
     153,   154,   155,   156,   158,   160,   161,   163,   166,   167,
     168,   169,    58,    59,    92,   142,   143,   149,   150,   151,
     162,   128,   128,   143,    60,   120,    13,    63,    63,   121,
      56,   104,   156,   157,    56,   160,   157,    63,   142,   149,
     162,    56,     6,     7,    56,     0,   121,     6,     7,    32,
      35,    56,   128,    21,    25,    28,    31,    34,    39,    44,
      45,    67,    70,    72,    74,    76,   140,    20,    69,    71,
      30,    33,    38,    46,    36,    37,    42,    43,    49,    68,
      24,    73,    27,    26,    29,    61,    63,   157,    62,    63,
       7,    13,    60,   146,   147,   148,   160,    56,    58,    62,
      57,    60,   109,    96,   123,   126,   155,   158,     6,     7,
      56,   142,    59,    63,   142,    13,   142,   142,    13,   142,
      57,   125,   141,   149,   162,   141,   149,   162,   128,   128,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     132,   132,   133,   134,   135,   136,   137,   143,    67,   157,
     142,    67,    64,    60,    62,    13,    57,   153,   159,    58,
     150,    56,   123,    62,    64,   123,    64,    13,   142,    57,
     159,    57,    60,   120,    57,    58,    57,    58,    57,    62,
      64,   143,    67,    58,   143,   143,    60,   147,   122,    13,
      57,    62,   142,    57,   142,   157,   143,    57,   142,   143,
      58,   122,    57,   121,    60,    59,   121,   141,   149,   162,
     143,   143,    67,   122,    13,   153,    57,   121,    57,    64,
      57,   121,    57,    57,   122,     4,    79,    83,   164,   165,
     143,    13,    63,   121,   143,   121,   121,   121,   121,   142,
      64,    60,   165,    57,    64,   120,   121,   120
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   124,   124,   124,
     124,   124,   124,   124,   124,   125,   125,   125,   125,   125,
     125,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     127,   127,   128,   128,   128,   128,   129,   129,   129,   129,
     130,   130,   130,   131,   131,   131,   132,   132,   132,   132,
     132,   133,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     141,   141,   141,   142,   143,   143,   143,   144,   144,   145,
     145,   145,   145,   146,   147,   147,   147,   147,   147,   148,
     148,   149,   149,   149,   150,   151,   151,   152,   152,   152,
     153,   153,   154,   154,   154,   155,   156,   156,   156,   156,
     157,   157,   157,   158,   158,   158,   158,   159,   159,   159,
     159,   160,   160,   161,   162,   162,   163,   163,   163,   164,
     164,   165,   165,   165,   165,   166,   166,   166,   166,   166,
     166,   167,   167,   167,   167,   167,   167,   167,   168,   168,
     168,   169,   169
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     3,     3,
       3,     1,     3,     4,     3,     4,     2,     2,     1,     1,
       1,     1,     1,     2,     2,     2,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     1,     3,     1,
       3,     2,     3,     4,     1,     1,     3,     2,     3,     4,
       1,     1,     1,     1,     1,     2,     1,     2,     3,     4,
       1,     3,     4,     2,     4,     3,     5,     1,     2,     3,
       4,     5,     6,     2,     4,     5,     7,     5,     7,     1,
       2,     4,     3,     3,     2,     2,     2,     2,     3,     2,
       2,     5,     7,     6,     7,     6,     7,     1,     7,     9,
       7,     5,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, parser); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* parser)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (parser);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* parser)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void* parser)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, parser); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void* parser)
{
  YYUSE (yyvaluep);
  YYUSE (parser);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void* parser)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex (&yylval, parser);
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
     '$$ = $1'.

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
#line 175 "yyparser.y" /* yacc.c:1646  */
    { PARSER->setProgramBlockAST(NULL); }
#line 1800 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 176 "yyparser.y" /* yacc.c:1646  */
    { PARSER->setProgramBlockAST((yyvsp[0].block)); }
#line 1806 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 180 "yyparser.y" /* yacc.c:1646  */
    { (yyval.block) = new BlockAST(); PARSER->addNodeAST((yyval.block)); if((yyvsp[0].node) != NULL) (yyval.block)->m_statements.push_back((yyvsp[0].node)); }
#line 1812 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 181 "yyparser.y" /* yacc.c:1646  */
    { if((yyvsp[0].node) != NULL) (yyvsp[-1].block)->m_statements.push_back((yyvsp[0].node)); }
#line 1818 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 185 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1824 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 186 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1830 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 187 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1836 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 188 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1842 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 189 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1848 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 190 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1854 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 194 "yyparser.y" /* yacc.c:1646  */
    { (yyval.block) = (yyvsp[-1].block); }
#line 1860 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 195 "yyparser.y" /* yacc.c:1646  */
    { (yyval.block) = new BlockAST(); PARSER->addNodeAST((yyval.block)); }
#line 1866 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 199 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1872 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 200 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1878 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 201 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].block); }
#line 1884 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 205 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NullAST(); PARSER->addNodeAST((yyval.node)); }
#line 1890 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 206 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1896 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 207 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1902 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 208 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1908 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 210 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1914 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 211 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].getvar); }
#line 1920 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 213 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1926 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 214 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new GetVarAST(NULL, "this"); PARSER->addNodeAST((yyval.node)); }
#line 1932 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 218 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 1938 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 219 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 1944 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 220 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].func)); }
#line 1950 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 221 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 1956 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 222 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 1962 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 223 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].func)); }
#line 1968 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 227 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1974 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 228 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new GetVarAST((yyvsp[-2].node), (yyvsp[0].token).getRawString()); PARSER->addNodeAST((yyval.node)); }
#line 1980 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 229 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new GetVarAST((yyvsp[-3].node), (yyvsp[-1].node)); PARSER->addNodeAST((yyval.node)); }
#line 1986 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 230 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CallAST((yyvsp[-2].node), NULL); PARSER->addNodeAST((yyval.node)); }
#line 1992 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 231 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CallAST((yyvsp[-3].node), (yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 1998 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 232 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixIncrementAST((yyvsp[-1].node), TOK_PLUSPLUS); PARSER->addNodeAST((yyval.node)); }
#line 2004 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 233 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixIncrementAST((yyvsp[-1].node), TOK_MINUSMINUS); PARSER->addNodeAST((yyval.node)); }
#line 2010 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 244 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2016 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 245 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryAST((yyvsp[0].node), TOK_PLUSPLUS); PARSER->addNodeAST((yyval.node)); }
#line 2022 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 246 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryAST((yyvsp[0].node), TOK_MINUSMINUS); PARSER->addNodeAST((yyval.node)); }
#line 2028 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 247 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryAST((yyvsp[0].node), (yyvsp[-1].token).m_type); PARSER->addNodeAST((yyval.node)); }
#line 2034 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 251 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2040 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 252 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeAST((yyvsp[-2].node), TOK_MUL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2046 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 253 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeAST((yyvsp[-2].node), TOK_DIV, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2052 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 254 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeAST((yyvsp[-2].node), TOK_MOD, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2058 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 258 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2064 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 259 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AdditiveAST((yyvsp[-2].node), TOK_PLUS, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2070 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 260 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AdditiveAST((yyvsp[-2].node), TOK_MINUS, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2076 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 264 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2082 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 265 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ShiftAST((yyvsp[-2].node), TOK_SHL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2088 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 266 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ShiftAST((yyvsp[-2].node), TOK_SHR, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2094 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 270 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2100 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 271 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_LT, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2106 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 272 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_GT, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2112 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 273 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_LE, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2118 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 274 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_GE, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2124 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 278 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2130 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 279 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new EqualityAST((yyvsp[-2].node), TOK_EQUAL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2136 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 280 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new EqualityAST((yyvsp[-2].node), TOK_NOTEQUAL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2142 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 284 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2148 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 285 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AndAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2154 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 289 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2160 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 290 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ExclusiveOrAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2166 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 294 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2172 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 295 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new InclusiveOrAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2178 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 299 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2184 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 300 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new LogicalAndAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2190 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 304 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2196 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 305 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new LogicalOrAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2202 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 309 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2208 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 310 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ConditionalAST((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2214 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 330 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2220 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 331 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentAST((yyvsp[-2].node), (yyvsp[-1].token).m_type, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2226 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 332 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentAST((yyvsp[-2].node), (yyvsp[-1].token).m_type, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2232 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 333 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentAST((yyvsp[-2].node), (yyvsp[-1].token).m_type, (yyvsp[0].func)); PARSER->addNodeAST((yyval.node)); }
#line 2238 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 337 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2244 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 341 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2250 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 342 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2256 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 343 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].func); }
#line 2262 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 347 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new BooleanAST(1); PARSER->addNodeAST((yyval.node)); }
#line 2268 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 348 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new BooleanAST(0); PARSER->addNodeAST((yyval.node)); }
#line 2274 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 352 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new Int32AST((yyvsp[0].token).m_integerValue); PARSER->addNodeAST((yyval.node)); }
#line 2280 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 353 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new Int64AST((yyvsp[0].token).m_integerValue); PARSER->addNodeAST((yyval.node)); }
#line 2286 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 354 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new FloatAST((yyvsp[0].token).m_doubleValue); PARSER->addNodeAST((yyval.node)); }
#line 2292 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 355 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new DoubleAST((yyvsp[0].token).m_doubleValue); PARSER->addNodeAST((yyval.node)); }
#line 2298 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 359 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new StringAST((yyvsp[0].token).toUTF8String(), (yyvsp[0].token).m_postfix); PARSER->addNodeAST((yyval.node)); }
#line 2304 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 364 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST((yyvsp[0].token).getRawString(), NULL);
            PARSER->addNodeAST((yyval.node));
        }
#line 2313 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 369 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST((yyvsp[-2].token).getRawString(), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2322 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 374 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST((yyvsp[-3].node), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2331 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 379 "yyparser.y" /* yacc.c:1646  */
    {
            GetVarAST* gv = (yyvsp[0].func)->m_nameExpr;
            if(gv->m_keyIdentifier.empty() || gv->m_parentExpr != 0 || gv->m_keyExpr != 0)
            {
                yyerror(parser, "invalid function name in table, must be a string");
                YYABORT;
            }
            (yyval.node) = new KeyValueAST(gv->m_keyIdentifier, (yyvsp[0].func));
            PARSER->addNodeAST((yyval.node));
        }
#line 2346 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 391 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST(((StringAST*)(yyvsp[-2].node))->m_val, (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2355 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 398 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 2361 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 399 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 2367 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 403 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new TableAST(NULL); PARSER->addNodeAST((yyval.node)); }
#line 2373 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 404 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new TableAST((yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2379 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 405 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new TableAST((yyvsp[-2].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2385 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 409 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2391 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 413 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 2397 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 414 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 2403 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 418 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ArrayAST(NULL); PARSER->addNodeAST((yyval.node)); }
#line 2409 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 419 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ArrayAST((yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2415 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 420 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ArrayAST((yyvsp[-2].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2421 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 431 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2427 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 432 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].func); }
#line 2433 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 433 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].func); }
#line 2439 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 437 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new VariableDeclarationListAST((yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2445 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 441 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[0].token).getRawString(), GetVarAST::NONE); PARSER->addNodeAST((yyval.getvar)); }
#line 2451 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 442 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[0].token).getRawString(), GetVarAST::GLOBAL); PARSER->addNodeAST((yyval.getvar)); }
#line 2457 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 443 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[0].token).getRawString(), GetVarAST::THIS); PARSER->addNodeAST((yyval.getvar)); }
#line 2463 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 444 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[-1].node), GetVarAST::THIS); PARSER->addNodeAST((yyval.getvar)); }
#line 2469 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 450 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = (yyvsp[0].getvar); }
#line 2475 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 451 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST((yyvsp[-2].getvar), (yyvsp[0].token).getRawString()); PARSER->addNodeAST((yyval.getvar)); }
#line 2481 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 452 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST((yyvsp[-3].getvar), (yyvsp[-1].node)); PARSER->addNodeAST((yyval.getvar)); }
#line 2487 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 457 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[0].getvar), NULL, ((yyvsp[-1].token).m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2499 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 465 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[-2].getvar), (yyvsp[0].node), ((yyvsp[-3].token).m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2511 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 473 "yyparser.y" /* yacc.c:1646  */
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyval.nodelist)->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[0].getvar), NULL, node0->m_isLocal);
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2522 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 480 "yyparser.y" /* yacc.c:1646  */
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyval.nodelist)->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[-2].getvar), (yyvsp[0].node), node0->m_isLocal);
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2533 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 490 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.arglist) = new StringList();
            PARSER->addNodeAST((yyval.arglist));
            (yyval.arglist)->push_back((yyvsp[0].token).getRawString());
        }
#line 2543 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 496 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.arglist) = new StringList();
            PARSER->addNodeAST((yyval.arglist));
            (yyval.arglist)->push_back((yyvsp[0].token).getRawString());
        }
#line 2553 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 502 "yyparser.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].arglist)->push_back((yyvsp[0].token).getRawString());
            if((yyvsp[-2].arglist)->m_hasDuplicateStr)
            {
                yyerror(parser, "argument name is duplicate");
                YYABORT;
            }
        }
#line 2566 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 511 "yyparser.y" /* yacc.c:1646  */
    {
            (yyvsp[-3].arglist)->push_back((yyvsp[0].token).getRawString());
            if((yyvsp[-3].arglist)->m_hasDuplicateStr)
            {
                yyerror(parser, "argument name is duplicate");
                YYABORT;
            }
        }
#line 2579 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 523 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST((yyvsp[-3].getvar), NULL, (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2588 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 528 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST((yyvsp[-4].getvar), (yyvsp[-2].arglist), (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2597 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 535 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[0].func)->m_isLocal = true; (yyval.func) = (yyvsp[0].func); }
#line 2603 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 540 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST(NULL, NULL, (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2612 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 545 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST(NULL, (yyvsp[-2].arglist), (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2621 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 553 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new IfElseAST((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2627 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 555 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new IfElseAST((yyvsp[-2].node), (yyvsp[0].node), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2633 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 557 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new SwitchAST((yyvsp[-4].node), (yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2639 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 562 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            (yyval.nodelist)->add_case_ast((CaseAST*)((yyvsp[0].node)));
        }
#line 2649 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 568 "yyparser.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].nodelist)->add_case_ast((CaseAST*)((yyvsp[0].node)));
            if((yyvsp[-1].nodelist)->m_hasMultipleDefaultStmt)
            {
                yyerror(parser, "multiple default labels in one switch");
                YYABORT;
            }
        }
#line 2662 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 579 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST((yyvsp[-2].node), (yyvsp[0].block)); PARSER->addNodeAST((yyval.node)); }
#line 2668 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 580 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST((yyvsp[-1].node), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2674 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 581 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST(NULL, (yyvsp[0].block)); PARSER->addNodeAST((yyval.node)); }
#line 2680 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 582 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST(NULL, NULL); PARSER->addNodeAST((yyval.node)); }
#line 2686 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 586 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ContinueAST(); PARSER->addNodeAST((yyval.node)); }
#line 2692 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 587 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new BreakAST(); PARSER->addNodeAST((yyval.node)); }
#line 2698 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 588 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST(NULL); PARSER->addNodeAST((yyval.node)); }
#line 2704 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 589 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST((yyvsp[-1].node)); PARSER->addNodeAST((yyval.node)); }
#line 2710 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 590 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST((yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2716 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 591 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST((yyvsp[0].func)); PARSER->addNodeAST((yyval.node)); }
#line 2722 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 595 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new WhileAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2728 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 596 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new DoWhileAST((yyvsp[-2].node), (yyvsp[-5].node)); PARSER->addNodeAST((yyval.node)); }
#line 2734 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 597 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-3].node), (yyvsp[-2].node), NULL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2740 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 598 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2746 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 599 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-3].node), (yyvsp[-2].node), NULL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2752 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 600 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2758 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 601 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2764 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 606 "yyparser.y" /* yacc.c:1646  */
    {
            if((yyvsp[-4].node)->m_type != NodeAST::tGetVarAST)
            {
                yyerror(parser, "for-each expression is illegal");
                YYABORT;
            }
            (yyval.node) = new ForeachAST(0, NULL, (GetVarAST*)(yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2778 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 616 "yyparser.y" /* yacc.c:1646  */
    {
            if((yyvsp[-6].node)->m_type != NodeAST::tGetVarAST)
            {
                yyerror(parser, "for-each expression is illegal");
                YYABORT;
            }
            (yyval.node) = new ForeachAST(0, (GetVarAST*)(yyvsp[-6].node), (yyvsp[-4].getvar), (yyvsp[-2].node), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2792 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 626 "yyparser.y" /* yacc.c:1646  */
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyvsp[-4].nodelist)->m_nodeASTVec[0];
            if(node0->m_assignmentExpr != NULL)
            {
                yyerror(parser, "for-each expression is illegal");
                YYABORT;
            }
            GetVarAST* getvar0 = node0->m_varExpr;
            
            VariableDeclarationAST* node1 = NULL;
            GetVarAST* getvar1 = NULL;
            if((yyvsp[-4].nodelist)->m_nodeASTVec.size() >= 2)
            {
                node1 = (VariableDeclarationAST*)(yyvsp[-4].nodelist)->m_nodeASTVec[1];
                if(node1->m_assignmentExpr != NULL)
                {
                    yyerror(parser, "for-each expression is illegal");
                    YYABORT;
                }
                getvar1 = node1->m_varExpr;
            }
            
            if(getvar1 == 0)
            {
                (yyval.node) = new ForeachAST(node0->m_isLocal? TOK_LOCAL : TOK_VAR, NULL, getvar0, (yyvsp[-2].node), (yyvsp[0].node));
            }
            else
            {
                (yyval.node) = new ForeachAST(node0->m_isLocal? TOK_LOCAL : TOK_VAR, getvar0, getvar1, (yyvsp[-2].node), (yyvsp[0].node));
            }
            PARSER->addNodeAST((yyval.node));
        }
#line 2829 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 661 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NamespaceAST((yyvsp[-3].getvar), (yyvsp[-1].block)); PARSER->addNodeAST((yyval.node)); }
#line 2835 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 662 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NamespaceAST((yyvsp[-2].getvar), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2841 "yyparser.cpp" /* yacc.c:1646  */
    break;


#line 2845 "yyparser.cpp" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parser, YY_("syntax error"));
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
        yyerror (parser, yymsgp);
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
                      yytoken, &yylval, parser);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
                  yystos[yystate], yyvsp, parser);
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
  yyerror (parser, YY_("memory exhausted"));
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
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, parser);
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
  return yyresult;
}
#line 665 "yyparser.y" /* yacc.c:1906  */


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
#define YYFINAL  111
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1409

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  319

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
       0,   176,   176,   177,   181,   182,   186,   187,   188,   189,
     190,   191,   195,   196,   200,   201,   202,   203,   207,   208,
     209,   210,   212,   213,   215,   216,   217,   221,   222,   223,
     224,   225,   226,   230,   231,   232,   233,   234,   235,   236,
     240,   241,   242,   243,   247,   248,   249,   250,   254,   255,
     256,   257,   261,   262,   263,   267,   268,   269,   273,   274,
     275,   276,   277,   281,   282,   283,   287,   288,   292,   293,
     297,   298,   302,   303,   307,   308,   312,   313,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   333,   334,   335,   336,   340,   344,   345,   346,   350,
     351,   355,   356,   357,   358,   362,   366,   371,   376,   381,
     393,   401,   402,   406,   407,   408,   412,   416,   417,   421,
     422,   423,   427,   428,   434,   435,   436,   440,   444,   445,
     446,   447,   453,   454,   455,   459,   467,   475,   482,   492,
     498,   504,   513,   525,   530,   538,   542,   547,   555,   557,
     559,   564,   570,   582,   583,   584,   585,   589,   590,   591,
     592,   593,   594,   598,   599,   600,   601,   602,   603,   604,
     608,   618,   628,   664,   665,   669,   670,   674
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
  "namespace_block", "new_expr", "delete_expr", YY_NULLPTR
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

#define YYPACT_NINF -151

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-151)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     721,   819,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  1303,
    -151,  1303,  -151,  1144,   329,  -151,    19,  -151,    26,    47,
       3,   721,  -151,    39,     3,    60,    44,     3,     3,  -151,
     872,    75,    53,  -151,  -151,    96,   122,   721,  -151,  -151,
    -151,  -151,    32,  1303,   825,     5,    24,    10,   120,    -3,
      42,    14,   128,   138,   -10,  -151,  -151,   106,  -151,  -151,
    -151,  -151,     3,  -151,  -151,  -151,    80,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,   119,  -151,    21,   127,  -151,
    -151,  -151,  -151,    87,  -151,  -151,  -151,   130,  -151,   427,
    -151,  -151,  -151,    53,  -151,    73,    83,    85,    76,  1303,
    -151,    34,    79,  -151,   125,  -151,  -151,  1303,   182,  1303,
    1303,  -151,  -151,   184,  1303,  -151,  -151,   925,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  1144,  1303,  1303,  1303,  1303,  1303,  1303,  1303,
    1303,  1303,  1303,  1303,  1303,  1303,  1303,  1303,  1303,  1303,
    1303,  1144,  -151,    17,     3,  -151,  -151,  1303,   136,  -151,
     140,  -151,   -40,  -151,    13,  -151,   978,  -151,  -151,   192,
    1303,   150,  -151,  1031,   202,  1031,   116,    16,   153,   525,
    1091,  -151,   155,  -151,   149,   156,  -151,   159,  -151,   -13,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
       5,     5,    24,    24,    10,    10,    10,    10,   120,   120,
      -3,    42,    14,   128,   138,   160,  1144,    30,   162,  1144,
    1144,  -151,    48,  -151,   166,   214,     1,  -151,  -151,  -151,
     172,  1303,  1197,     3,  1144,  1250,  1144,   166,    15,   721,
    -151,   623,  -151,    66,   173,  -151,   721,  -151,  -151,  1144,
    1144,  -151,  1144,   168,  -151,  -151,  -151,  -151,  -151,  -151,
     166,    18,  -151,   176,   721,   181,    36,   186,   721,   189,
     193,  -151,   166,   237,  -151,  -151,    89,  -151,  -151,  -151,
    -151,  -151,  -151,  1144,  -151,  -151,   229,   190,  -151,   721,
    1144,   721,  -151,   721,   721,  -151,   721,  1303,   195,    -8,
    -151,  -151,  -151,  -151,  -151,   200,  -151,  -151,  -151,  -151,
     196,   721,  -151,  -151,   721,   721,   721,  -151,   721
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,   128,   105,   101,   102,   103,   104,    41,     0,
      40,     0,    43,     0,     0,    14,     0,    42,     0,     0,
       0,     0,   100,     0,     0,     0,   123,     0,     0,    18,
       0,     0,    25,    99,   122,     0,     0,     3,     4,    17,
       6,    33,    44,     0,    48,    52,    55,    58,    63,    66,
      68,    70,    72,    74,    76,    91,    95,     0,    19,    20,
      21,    22,     0,     7,   124,    23,     0,   125,   126,     8,
       9,    10,   169,    11,    26,     0,   119,     0,     0,    96,
     116,    97,   117,     0,    98,    46,    45,     0,    13,     0,
     129,   158,   157,     0,   132,   177,     0,     0,     0,     0,
     145,     0,     0,   159,     0,   161,   162,     0,     0,     0,
       0,     1,     5,     0,     0,    39,    38,     0,    47,    79,
      80,    81,    82,    83,    84,    85,    86,    78,    87,    88,
      89,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,   135,     0,   127,    16,     0,   106,   113,
       0,   111,     0,   109,     0,   120,     0,    24,    12,     0,
       0,     0,   123,     0,    44,     0,     0,     0,     0,     0,
       0,   160,     0,   130,     0,     0,    34,     0,    36,     0,
      27,    28,    29,    92,    93,    94,    50,    49,    51,    48,
      54,    53,    56,    57,    59,    61,    60,    62,    65,    64,
      67,    69,    71,    73,    75,     0,     0,   137,     0,     0,
       0,   114,     0,   139,     0,     0,     0,   121,   118,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     174,     0,   175,     0,     0,   131,     0,    35,    37,     0,
       0,   136,     0,     0,   107,   110,   115,   112,   146,   140,
       0,     0,   134,     0,     0,     0,     0,     0,     0,     0,
       0,   143,     0,   149,   173,   176,     0,   163,    30,    31,
      32,    77,   138,     0,   147,   141,     0,     0,   165,     0,
       0,     0,   167,     0,     0,   144,     0,     0,     0,     0,
     151,   108,   142,   164,   166,     0,   170,   168,   172,   148,
       0,   156,   150,   152,     0,   154,   155,   171,   153
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,   -14,   -20,   -99,   -79,  -151,    69,   164,  -151,
     185,    22,    28,    59,    31,   117,   115,   129,   118,   131,
    -151,  -151,  -151,  -102,    20,    -5,  -151,  -151,   -71,    43,
    -151,   -27,   102,  -151,  -151,  -150,  -151,   178,   -15,   -17,
     183,   105,   -24,  -151,   -26,  -151,  -151,   -16,  -151,  -151,
    -151,  -151,  -151,  -151
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    36,    37,    38,    39,    40,    41,   189,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   132,    56,    57,    80,    58,    59,    60,   161,
     162,    81,    82,    83,    61,    62,    63,    64,    65,    95,
      66,   226,    67,    68,    84,    69,   299,   300,    70,    71,
      72,    73,    74,    75
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      89,    96,   100,   105,   106,    94,   160,    98,    87,    94,
     101,   102,    94,    94,   225,   190,     2,   112,   173,   150,
     221,    79,   222,   169,   170,   133,   223,   225,   157,   223,
     193,   285,    90,    79,   158,     3,   169,   170,   113,   114,
     169,   170,   169,   170,   248,   153,   144,    94,   138,   249,
     104,   151,   312,   163,   136,   157,   139,   137,   260,   108,
     109,   158,     3,   261,   115,   145,   146,   116,    16,   112,
     224,   297,   272,   237,   134,   298,   135,   261,   190,   169,
     170,   159,   169,   170,   216,   169,   170,   147,   117,    91,
     191,   192,     1,   179,   232,    97,   235,   252,     2,     3,
     290,     4,     5,     6,     7,   194,   195,    93,   256,   172,
      92,   286,   172,    24,   172,     8,    99,     9,    10,   178,
      11,    34,   111,   275,    34,   258,    34,   182,   249,   184,
     185,   107,   177,    12,   187,   180,    24,   217,   271,    94,
      24,    13,   154,   155,    14,   165,   215,   278,    15,   166,
      16,   160,   110,   191,   192,   148,   140,   141,   200,   201,
      17,   284,   142,   143,   149,   241,   202,   203,   297,   152,
      20,    79,   298,   295,    22,   208,   209,   218,   154,   155,
     236,   172,   156,   164,    28,    29,    79,   167,   181,    32,
     230,    33,   171,    34,    85,   183,    86,   186,   163,   204,
     205,   206,   207,   219,   220,   229,   231,   245,   113,   114,
     239,   251,   244,   246,   254,   255,   266,   247,    94,   273,
     253,   112,   279,   280,   250,    14,   277,   259,   118,   267,
     262,   270,   276,   287,   115,   283,    79,   116,   289,    79,
      79,   296,   302,   291,   288,   281,   293,   282,   292,   243,
     294,   263,   265,   303,    79,   269,    79,   314,   117,   311,
     315,   174,   211,   210,   233,   257,   234,   213,   228,   304,
      79,   306,    79,   307,   308,   175,   309,   212,   301,     0,
     176,   214,   238,   313,     0,   305,     0,     0,     0,     0,
       0,     0,     0,     0,   317,     0,   112,   316,   112,     0,
       0,   318,     0,    79,     0,     0,     0,     0,     0,     0,
      79,     0,     0,     0,     0,     0,     0,   310,   196,   197,
     198,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,     1,     0,     0,     0,
       0,     0,     2,     3,     0,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     9,    10,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,    14,    88,
       0,     0,    15,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,    18,     0,     0,
       0,    19,     0,     0,    20,    21,     0,     0,    22,    23,
       0,    24,    25,     0,     0,    26,     0,    27,    28,    29,
       0,    30,    31,    32,     1,    33,     0,    34,    35,     0,
       2,     3,     0,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,    14,   168,     0,     0,
      15,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    18,     0,     0,     0,    19,
       0,     0,    20,    21,     0,     0,    22,    23,     0,    24,
      25,     0,     0,    26,     0,    27,    28,    29,     0,    30,
      31,    32,     1,    33,     0,    34,    35,     0,     2,     3,
       0,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,    14,   240,     0,     0,    15,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,    18,     0,     0,     0,    19,     0,     0,
      20,    21,     0,     0,    22,    23,     0,    24,    25,     0,
       0,    26,     0,    27,    28,    29,     0,    30,    31,    32,
       1,    33,     0,    34,    35,     0,     2,     3,     0,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     9,    10,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,   274,     0,     0,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    18,     0,     0,     0,    19,     0,     0,    20,    21,
       0,     0,    22,    23,     0,    24,    25,     0,     0,    26,
       0,    27,    28,    29,     0,    30,    31,    32,     1,    33,
       0,    34,    35,     0,     2,     3,     0,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,    13,     0,     0,
      14,     0,     0,     0,    15,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
       0,     0,     0,    19,     0,     0,    20,    21,     0,     0,
      22,    23,     0,    24,    25,     0,     0,    26,     0,    27,
      28,    29,     0,    30,    31,    32,     1,    33,     0,    34,
      35,     0,     2,     3,     0,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,   119,     0,     0,     8,
     120,     9,    10,   121,    11,     0,   122,     0,     0,   123,
       0,     0,     0,     0,   124,     0,     0,    12,     0,   125,
     126,     0,     0,     0,     0,    13,     0,    76,    77,     1,
       0,     0,     0,     0,    16,     2,     3,     0,     4,     5,
       6,     7,   127,     0,    17,   128,     0,   129,     0,   130,
       0,   131,     8,     0,     9,    10,     0,    11,    22,     0,
       0,    78,     0,     0,     0,     0,     0,     0,    28,    29,
      12,     0,     0,    32,     0,    33,     0,     0,    13,     0,
       0,    77,     1,     0,     0,   103,     0,    16,     2,     3,
       0,     4,     5,     6,     7,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,    22,     0,     0,    78,     0,     0,     0,     0,     0,
       0,    28,    29,    12,     0,     0,    32,     0,    33,     0,
       0,    13,   188,     0,    77,     1,     0,     0,     0,     0,
      16,     2,     3,     0,     4,     5,     6,     7,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    22,     0,     0,    78,     0,     0,
       0,     0,     0,     0,    28,    29,    12,     0,     0,    32,
       0,    33,     0,     0,    13,     0,   227,    77,     1,     0,
       0,     0,     0,    16,     2,     3,     0,     4,     5,     6,
       7,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,    22,     0,     0,
      78,     0,     0,     0,     0,     0,     0,    28,    29,    12,
       0,     0,    32,     0,    33,     0,     0,    13,     0,     0,
      14,     0,     0,     0,    15,     0,    16,     0,     1,     0,
       0,     0,     0,     0,     2,     3,    17,     4,     5,     6,
       7,     0,     0,     0,     0,     0,    20,     0,     0,     0,
      22,     8,     0,     9,    10,     0,    11,     0,     0,     0,
      28,    29,     0,     0,     0,    32,     0,    33,     0,    12,
       0,     0,     0,     0,     0,     0,     0,    13,   242,     0,
      77,     1,     0,     0,     0,     0,    16,     2,     3,     0,
       4,     5,     6,     7,     0,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     9,    10,     0,    11,
      22,     0,     0,    78,     0,     0,     0,     0,     0,     0,
      28,    29,    12,     0,     0,    32,     0,    33,     0,     0,
      13,     0,     0,    77,     1,     0,     0,     0,     0,    16,
       2,     3,     0,     4,     5,     6,     7,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     9,
      10,     0,    11,    22,     0,     0,    78,     0,     0,     0,
       0,     0,     0,    28,    29,    12,     0,     0,    32,     0,
      33,     0,     0,    13,   264,     0,     0,     1,     0,     0,
       0,     0,    16,     2,     3,     0,     4,     5,     6,     7,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,     0,    11,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    12,     0,
       0,    32,     0,    33,     0,     0,    13,   268,     0,     0,
       1,     0,     0,     0,     0,    16,     2,     3,     0,     4,
       5,     6,     7,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     9,    10,     0,    11,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,    12,     0,     0,    32,     0,    33,     0,     0,    13,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    29,     0,     0,     0,    32,     0,    33
};

static const yytype_int16 yycheck[] =
{
      14,    21,    26,    30,    30,    20,    77,    24,    13,    24,
      27,    28,    27,    28,   164,   117,    13,    37,    97,    29,
      60,     1,    62,     6,     7,    20,    13,   177,     7,    13,
     132,    13,    13,    13,    13,    14,     6,     7,     6,     7,
       6,     7,     6,     7,    57,    62,    49,    62,    38,    62,
      30,    61,    60,    77,    30,     7,    46,    33,    57,     6,
       7,    13,    14,    62,    32,    68,    24,    35,    65,    89,
      57,    79,    57,    57,    69,    83,    71,    62,   180,     6,
       7,    60,     6,     7,    67,     6,     7,    73,    56,    63,
     117,   117,     7,    59,   173,    56,   175,    67,    13,    14,
      64,    16,    17,    18,    19,   132,   132,   104,    60,    96,
      63,   261,    96,    92,    96,    30,    56,    32,    33,    99,
      35,   108,     0,    57,   108,   224,   108,   107,    62,   109,
     110,    56,    56,    48,   114,    56,    92,   154,   237,   154,
      92,    56,    62,    63,    59,    58,   151,   249,    63,    62,
      65,   222,    56,   180,   180,    27,    36,    37,   136,   137,
      75,   260,    42,    43,    26,   179,   138,   139,    79,    63,
      85,   151,    83,   272,    89,   144,   145,   157,    62,    63,
      64,    96,    63,    56,    99,   100,   166,    57,    63,   104,
     170,   106,   109,   108,     9,    13,    11,    13,   222,   140,
     141,   142,   143,    67,    64,    13,    56,    58,     6,     7,
      57,   216,    57,    57,   219,   220,   233,    58,   233,   239,
      58,   241,   249,   249,    64,    59,   246,    13,    43,   234,
      58,   236,    59,    57,    32,    67,   216,    35,    57,   219,
     220,     4,    13,    57,   264,   250,    57,   252,   268,   180,
      57,   231,   232,    63,   234,   235,   236,    57,    56,    64,
      64,    97,   147,   146,    62,   222,    64,   149,   166,   289,
     250,   291,   252,   293,   294,    97,   296,   148,   283,    -1,
      97,   150,   177,   299,    -1,   290,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   314,    -1,   316,   311,   318,    -1,
      -1,   315,    -1,   283,    -1,    -1,    -1,    -1,    -1,    -1,
     290,    -1,    -1,    -1,    -1,    -1,    -1,   297,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    -1,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    -1,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    60,
      -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    78,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    -1,    89,    90,
      -1,    92,    93,    -1,    -1,    96,    -1,    98,    99,   100,
      -1,   102,   103,   104,     7,   106,    -1,   108,   109,    -1,
      13,    14,    -1,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    59,    60,    -1,    -1,
      63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    -1,    96,    -1,    98,    99,   100,    -1,   102,
     103,   104,     7,   106,    -1,   108,   109,    -1,    13,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,    60,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    78,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    -1,    89,    90,    -1,    92,    93,    -1,
      -1,    96,    -1,    98,    99,   100,    -1,   102,   103,   104,
       7,   106,    -1,   108,   109,    -1,    13,    14,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    60,    -1,    -1,    63,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    -1,    89,    90,    -1,    92,    93,    -1,    -1,    96,
      -1,    98,    99,   100,    -1,   102,   103,   104,     7,   106,
      -1,   108,   109,    -1,    13,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      59,    -1,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    78,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    -1,
      89,    90,    -1,    92,    93,    -1,    -1,    96,    -1,    98,
      99,   100,    -1,   102,   103,   104,     7,   106,    -1,   108,
     109,    -1,    13,    14,    -1,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    30,
      25,    32,    33,    28,    35,    -1,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    48,    -1,    44,
      45,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,     7,
      -1,    -1,    -1,    -1,    65,    13,    14,    -1,    16,    17,
      18,    19,    67,    -1,    75,    70,    -1,    72,    -1,    74,
      -1,    76,    30,    -1,    32,    33,    -1,    35,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
      48,    -1,    -1,   104,    -1,   106,    -1,    -1,    56,    -1,
      -1,    59,     7,    -1,    -1,    63,    -1,    65,    13,    14,
      -1,    16,    17,    18,    19,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,
      35,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    99,   100,    48,    -1,    -1,   104,    -1,   106,    -1,
      -1,    56,    57,    -1,    59,     7,    -1,    -1,    -1,    -1,
      65,    13,    14,    -1,    16,    17,    18,    19,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    -1,    35,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   100,    48,    -1,    -1,   104,
      -1,   106,    -1,    -1,    56,    -1,    58,    59,     7,    -1,
      -1,    -1,    -1,    65,    13,    14,    -1,    16,    17,    18,
      19,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    -1,    35,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,    48,
      -1,    -1,   104,    -1,   106,    -1,    -1,    56,    -1,    -1,
      59,    -1,    -1,    -1,    63,    -1,    65,    -1,     7,    -1,
      -1,    -1,    -1,    -1,    13,    14,    75,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,
      89,    30,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      99,   100,    -1,    -1,    -1,   104,    -1,   106,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,
      59,     7,    -1,    -1,    -1,    -1,    65,    13,    14,    -1,
      16,    17,    18,    19,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      99,   100,    48,    -1,    -1,   104,    -1,   106,    -1,    -1,
      56,    -1,    -1,    59,     7,    -1,    -1,    -1,    -1,    65,
      13,    14,    -1,    16,    17,    18,    19,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    35,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,    48,    -1,    -1,   104,    -1,
     106,    -1,    -1,    56,    57,    -1,    -1,     7,    -1,    -1,
      -1,    -1,    65,    13,    14,    -1,    16,    17,    18,    19,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    -1,    35,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    99,   100,    48,    -1,
      -1,   104,    -1,   106,    -1,    -1,    56,    57,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    65,    13,    14,    -1,    16,
      17,    18,    19,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    -1,    35,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     100,    48,    -1,    -1,   104,    -1,   106,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,    -1,    -1,    -1,   104,    -1,   106
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    14,    16,    17,    18,    19,    30,    32,
      33,    35,    48,    56,    59,    63,    65,    75,    78,    82,
      85,    86,    89,    90,    92,    93,    96,    98,    99,   100,
     102,   103,   104,   106,   108,   109,   119,   120,   121,   122,
     123,   124,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   141,   142,   144,   145,
     146,   152,   153,   154,   155,   156,   158,   160,   161,   163,
     166,   167,   168,   169,   170,   171,    58,    59,    92,   142,
     143,   149,   150,   151,   162,   128,   128,   143,    60,   120,
      13,    63,    63,   104,   156,   157,   121,    56,   157,    56,
     160,   157,   157,    63,   142,   149,   162,    56,     6,     7,
      56,     0,   121,     6,     7,    32,    35,    56,   128,    21,
      25,    28,    31,    34,    39,    44,    45,    67,    70,    72,
      74,    76,   140,    20,    69,    71,    30,    33,    38,    46,
      36,    37,    42,    43,    49,    68,    24,    73,    27,    26,
      29,    61,    63,   157,    62,    63,    63,     7,    13,    60,
     146,   147,   148,   160,    56,    58,    62,    57,    60,     6,
       7,   109,    96,   123,   126,   155,   158,    56,   142,    59,
      56,    63,   142,    13,   142,   142,    13,   142,    57,   125,
     141,   149,   162,   141,   149,   162,   128,   128,   128,   128,
     129,   129,   130,   130,   131,   131,   131,   131,   132,   132,
     133,   134,   135,   136,   137,   143,    67,   157,   142,    67,
      64,    60,    62,    13,    57,   153,   159,    58,   150,    13,
     142,    56,   123,    62,    64,   123,    64,    57,   159,    57,
      60,   120,    57,   125,    57,    58,    57,    58,    57,    62,
      64,   143,    67,    58,   143,   143,    60,   147,   122,    13,
      57,    62,    58,   142,    57,   142,   157,   143,    57,   142,
     143,   122,    57,   121,    60,    57,    59,   121,   141,   149,
     162,   143,   143,    67,   122,    13,   153,    57,   121,    57,
      64,    57,   121,    57,    57,   122,     4,    79,    83,   164,
     165,   143,    13,    63,   121,   143,   121,   121,   121,   121,
     142,    64,    60,   165,    57,    64,   120,   121,   120
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   125,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     127,   127,   127,   127,   128,   128,   128,   128,   129,   129,
     129,   129,   130,   130,   130,   131,   131,   131,   132,   132,
     132,   132,   132,   133,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   141,   141,   142,   143,   143,   143,   144,
     144,   145,   145,   145,   145,   146,   147,   147,   147,   147,
     147,   148,   148,   149,   149,   149,   150,   151,   151,   152,
     152,   152,   153,   153,   154,   154,   154,   155,   156,   156,
     156,   156,   157,   157,   157,   158,   158,   158,   158,   159,
     159,   159,   159,   160,   160,   161,   162,   162,   163,   163,
     163,   164,   164,   165,   165,   165,   165,   166,   166,   166,
     166,   166,   166,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   168,   169,   169,   170,   170,   171
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     3,     4,     3,     4,     2,     2,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     1,
       3,     1,     3,     2,     3,     4,     1,     1,     3,     2,
       3,     4,     1,     1,     1,     1,     1,     2,     1,     2,
       3,     4,     1,     3,     4,     2,     4,     3,     5,     1,
       2,     3,     4,     5,     6,     2,     4,     5,     7,     5,
       7,     1,     2,     4,     3,     3,     2,     2,     2,     2,
       3,     2,     2,     5,     7,     6,     7,     6,     7,     1,
       7,     9,     7,     5,     4,     4,     5,     2
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
#line 176 "yyparser.y" /* yacc.c:1646  */
    { PARSER->setProgramBlockAST(NULL); }
#line 1825 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 177 "yyparser.y" /* yacc.c:1646  */
    { PARSER->setProgramBlockAST((yyvsp[0].block)); }
#line 1831 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 181 "yyparser.y" /* yacc.c:1646  */
    { (yyval.block) = new BlockAST(); PARSER->addNodeAST((yyval.block)); if((yyvsp[0].node) != NULL) (yyval.block)->m_statements.push_back((yyvsp[0].node)); }
#line 1837 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 182 "yyparser.y" /* yacc.c:1646  */
    { if((yyvsp[0].node) != NULL) (yyvsp[-1].block)->m_statements.push_back((yyvsp[0].node)); }
#line 1843 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 186 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1849 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 187 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1855 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 188 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1861 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 189 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1867 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 190 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1873 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 191 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1879 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 195 "yyparser.y" /* yacc.c:1646  */
    { (yyval.block) = (yyvsp[-1].block); }
#line 1885 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 196 "yyparser.y" /* yacc.c:1646  */
    { (yyval.block) = new BlockAST(); PARSER->addNodeAST((yyval.block)); }
#line 1891 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 200 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1897 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 201 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1903 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 202 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1909 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 203 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].block); }
#line 1915 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 207 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NullAST(); PARSER->addNodeAST((yyval.node)); }
#line 1921 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 208 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1927 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 209 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1933 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 210 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1939 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 212 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1945 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 213 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].getvar); }
#line 1951 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 215 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1957 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 216 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new GetVarAST(NULL, "this"); PARSER->addNodeAST((yyval.node)); }
#line 1963 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 217 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1969 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 221 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 1975 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 222 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 1981 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 223 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].func)); }
#line 1987 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 224 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 1993 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 225 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 1999 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 226 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].func)); }
#line 2005 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 230 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2011 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 231 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new GetVarAST((yyvsp[-2].node), (yyvsp[0].token).getRawString()); PARSER->addNodeAST((yyval.node)); }
#line 2017 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 232 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new GetVarAST((yyvsp[-3].node), (yyvsp[-1].node)); PARSER->addNodeAST((yyval.node)); }
#line 2023 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 233 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CallAST((yyvsp[-2].node), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2029 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 234 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CallAST((yyvsp[-3].node), (yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2035 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 235 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixIncrementAST((yyvsp[-1].node), TOK_PLUSPLUS); PARSER->addNodeAST((yyval.node)); }
#line 2041 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 236 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixIncrementAST((yyvsp[-1].node), TOK_MINUSMINUS); PARSER->addNodeAST((yyval.node)); }
#line 2047 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 247 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2053 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 248 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryAST((yyvsp[0].node), TOK_PLUSPLUS); PARSER->addNodeAST((yyval.node)); }
#line 2059 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 249 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryAST((yyvsp[0].node), TOK_MINUSMINUS); PARSER->addNodeAST((yyval.node)); }
#line 2065 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 250 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryAST((yyvsp[0].node), (yyvsp[-1].token).m_type); PARSER->addNodeAST((yyval.node)); }
#line 2071 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 254 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2077 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 255 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeAST((yyvsp[-2].node), TOK_MUL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2083 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 256 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeAST((yyvsp[-2].node), TOK_DIV, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2089 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 257 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeAST((yyvsp[-2].node), TOK_MOD, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2095 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 261 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2101 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 262 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AdditiveAST((yyvsp[-2].node), TOK_PLUS, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2107 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 263 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AdditiveAST((yyvsp[-2].node), TOK_MINUS, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2113 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 267 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2119 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 268 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ShiftAST((yyvsp[-2].node), TOK_SHL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2125 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 269 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ShiftAST((yyvsp[-2].node), TOK_SHR, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2131 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 273 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2137 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 274 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_LT, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2143 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 275 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_GT, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2149 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 276 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_LE, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2155 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 277 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalAST((yyvsp[-2].node), TOK_GE, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2161 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 281 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2167 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 282 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new EqualityAST((yyvsp[-2].node), TOK_EQUAL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2173 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 283 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new EqualityAST((yyvsp[-2].node), TOK_NOTEQUAL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2179 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 287 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2185 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 288 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AndAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2191 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 292 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2197 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 293 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ExclusiveOrAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2203 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 297 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2209 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 298 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new InclusiveOrAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2215 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 302 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2221 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 303 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new LogicalAndAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2227 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 307 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2233 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 308 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new LogicalOrAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2239 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 312 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2245 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 313 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ConditionalAST((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2251 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 333 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2257 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 334 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentAST((yyvsp[-2].node), (yyvsp[-1].token).m_type, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2263 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 335 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentAST((yyvsp[-2].node), (yyvsp[-1].token).m_type, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2269 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 336 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentAST((yyvsp[-2].node), (yyvsp[-1].token).m_type, (yyvsp[0].func)); PARSER->addNodeAST((yyval.node)); }
#line 2275 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 340 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2281 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 344 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2287 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 345 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2293 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 346 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].func); }
#line 2299 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 350 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new BooleanAST(1); PARSER->addNodeAST((yyval.node)); }
#line 2305 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 351 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new BooleanAST(0); PARSER->addNodeAST((yyval.node)); }
#line 2311 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 355 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new Int32AST((yyvsp[0].token).m_integerValue); PARSER->addNodeAST((yyval.node)); }
#line 2317 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 356 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new Int64AST((yyvsp[0].token).m_integerValue); PARSER->addNodeAST((yyval.node)); }
#line 2323 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 357 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new FloatAST((yyvsp[0].token).m_doubleValue); PARSER->addNodeAST((yyval.node)); }
#line 2329 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 358 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new DoubleAST((yyvsp[0].token).m_doubleValue); PARSER->addNodeAST((yyval.node)); }
#line 2335 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 362 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new StringAST((yyvsp[0].token).toUTF8String(), (yyvsp[0].token).m_postfix); PARSER->addNodeAST((yyval.node)); }
#line 2341 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 367 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST((yyvsp[0].token).getRawString(), NULL);
            PARSER->addNodeAST((yyval.node));
        }
#line 2350 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 372 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST((yyvsp[-2].token).getRawString(), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2359 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 377 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST((yyvsp[-3].node), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2368 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 382 "yyparser.y" /* yacc.c:1646  */
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
#line 2383 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 394 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new KeyValueAST(((StringAST*)(yyvsp[-2].node))->m_val, (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2392 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 401 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 2398 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 402 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 2404 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 406 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new TableAST(NULL); PARSER->addNodeAST((yyval.node)); }
#line 2410 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 407 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new TableAST((yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2416 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 408 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new TableAST((yyvsp[-2].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2422 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 412 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2428 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 416 "yyparser.y" /* yacc.c:1646  */
    { (yyval.nodelist) = new NodeASTList(); PARSER->addNodeAST((yyval.nodelist)); (yyval.nodelist)->push_back((yyvsp[0].node)); }
#line 2434 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 417 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[-2].nodelist)->push_back((yyvsp[0].node)); }
#line 2440 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 421 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ArrayAST(NULL); PARSER->addNodeAST((yyval.node)); }
#line 2446 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 422 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ArrayAST((yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2452 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 423 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ArrayAST((yyvsp[-2].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2458 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 434 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2464 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 435 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].func); }
#line 2470 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 436 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].func); }
#line 2476 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 440 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new VariableDeclarationListAST((yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2482 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 444 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[0].token).getRawString(), GetVarAST::NONE); PARSER->addNodeAST((yyval.getvar)); }
#line 2488 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 445 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[0].token).getRawString(), GetVarAST::GLOBAL); PARSER->addNodeAST((yyval.getvar)); }
#line 2494 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 446 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[0].token).getRawString(), GetVarAST::THIS); PARSER->addNodeAST((yyval.getvar)); }
#line 2500 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 447 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST(NULL, (yyvsp[-1].node), GetVarAST::THIS); PARSER->addNodeAST((yyval.getvar)); }
#line 2506 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 453 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = (yyvsp[0].getvar); }
#line 2512 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 454 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST((yyvsp[-2].getvar), (yyvsp[0].token).getRawString()); PARSER->addNodeAST((yyval.getvar)); }
#line 2518 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 455 "yyparser.y" /* yacc.c:1646  */
    { (yyval.getvar) = new GetVarAST((yyvsp[-3].getvar), (yyvsp[-1].node)); PARSER->addNodeAST((yyval.getvar)); }
#line 2524 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 460 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[0].getvar), NULL, ((yyvsp[-1].token).m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2536 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 468 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[-2].getvar), (yyvsp[0].node), ((yyvsp[-3].token).m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2548 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 476 "yyparser.y" /* yacc.c:1646  */
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyval.nodelist)->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[0].getvar), NULL, node0->m_isLocal);
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2559 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 483 "yyparser.y" /* yacc.c:1646  */
    {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)(yyval.nodelist)->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST((yyvsp[-2].getvar), (yyvsp[0].node), node0->m_isLocal);
            PARSER->addNodeAST(node);
            (yyval.nodelist)->push_back(node);
        }
#line 2570 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 493 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.arglist) = new StringList();
            PARSER->addNodeAST((yyval.arglist));
            (yyval.arglist)->push_back((yyvsp[0].token).getRawString());
        }
#line 2580 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 499 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.arglist) = new StringList();
            PARSER->addNodeAST((yyval.arglist));
            (yyval.arglist)->push_back((yyvsp[0].token).getRawString());
        }
#line 2590 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 505 "yyparser.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].arglist)->push_back((yyvsp[0].token).getRawString());
            if((yyvsp[-2].arglist)->m_hasDuplicateStr)
            {
                yyerror(parser, "argument name is duplicate");
                YYABORT;
            }
        }
#line 2603 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 514 "yyparser.y" /* yacc.c:1646  */
    {
            (yyvsp[-3].arglist)->push_back((yyvsp[0].token).getRawString());
            if((yyvsp[-3].arglist)->m_hasDuplicateStr)
            {
                yyerror(parser, "argument name is duplicate");
                YYABORT;
            }
        }
#line 2616 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 526 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST((yyvsp[-3].getvar), NULL, (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2625 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 531 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST((yyvsp[-4].getvar), (yyvsp[-2].arglist), (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2634 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 538 "yyparser.y" /* yacc.c:1646  */
    { (yyvsp[0].func)->m_isLocal = true; (yyval.func) = (yyvsp[0].func); }
#line 2640 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 543 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST(NULL, NULL, (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2649 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 548 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.func) = new FunctionAST(NULL, (yyvsp[-2].arglist), (yyvsp[0].block));
            PARSER->addNodeAST((yyval.func));
        }
#line 2658 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 556 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new IfElseAST((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2664 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 558 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new IfElseAST((yyvsp[-2].node), (yyvsp[0].node), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2670 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 560 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new SwitchAST((yyvsp[-4].node), (yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2676 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 565 "yyparser.y" /* yacc.c:1646  */
    {
            (yyval.nodelist) = new NodeASTList();
            PARSER->addNodeAST((yyval.nodelist));
            (yyval.nodelist)->add_case_ast((CaseAST*)((yyvsp[0].node)));
        }
#line 2686 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 571 "yyparser.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].nodelist)->add_case_ast((CaseAST*)((yyvsp[0].node)));
            if((yyvsp[-1].nodelist)->m_hasMultipleDefaultStmt)
            {
                yyerror(parser, "multiple default labels in one switch");
                YYABORT;
            }
        }
#line 2699 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 582 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST((yyvsp[-2].node), (yyvsp[0].block)); PARSER->addNodeAST((yyval.node)); }
#line 2705 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 583 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST((yyvsp[-1].node), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2711 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 584 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST(NULL, (yyvsp[0].block)); PARSER->addNodeAST((yyval.node)); }
#line 2717 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 585 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new CaseAST(NULL, NULL); PARSER->addNodeAST((yyval.node)); }
#line 2723 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 589 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ContinueAST(); PARSER->addNodeAST((yyval.node)); }
#line 2729 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 590 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new BreakAST(); PARSER->addNodeAST((yyval.node)); }
#line 2735 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 591 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST(NULL); PARSER->addNodeAST((yyval.node)); }
#line 2741 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 592 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST((yyvsp[-1].node)); PARSER->addNodeAST((yyval.node)); }
#line 2747 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 593 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST((yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2753 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 594 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnAST((yyvsp[0].func)); PARSER->addNodeAST((yyval.node)); }
#line 2759 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 598 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new WhileAST((yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2765 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 599 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new DoWhileAST((yyvsp[-2].node), (yyvsp[-5].node)); PARSER->addNodeAST((yyval.node)); }
#line 2771 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 600 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-3].node), (yyvsp[-2].node), NULL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2777 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 601 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2783 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 602 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-3].node), (yyvsp[-2].node), NULL, (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2789 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 603 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForAST((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); PARSER->addNodeAST((yyval.node)); }
#line 2795 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 604 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2801 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 609 "yyparser.y" /* yacc.c:1646  */
    {
            if((yyvsp[-4].node)->m_type != NodeAST::tGetVarAST)
            {
                yyerror(parser, "for-each expression is illegal");
                YYABORT;
            }
            (yyval.node) = new ForeachAST(0, NULL, (GetVarAST*)(yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2815 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 619 "yyparser.y" /* yacc.c:1646  */
    {
            if((yyvsp[-6].node)->m_type != NodeAST::tGetVarAST)
            {
                yyerror(parser, "for-each expression is illegal");
                YYABORT;
            }
            (yyval.node) = new ForeachAST(0, (GetVarAST*)(yyvsp[-6].node), (yyvsp[-4].getvar), (yyvsp[-2].node), (yyvsp[0].node));
            PARSER->addNodeAST((yyval.node));
        }
#line 2829 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 629 "yyparser.y" /* yacc.c:1646  */
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
#line 2866 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 664 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NamespaceAST((yyvsp[-3].getvar), (yyvsp[-1].block)); PARSER->addNodeAST((yyval.node)); }
#line 2872 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 665 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NamespaceAST((yyvsp[-2].getvar), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2878 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 669 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NewAST((yyvsp[-2].getvar), NULL); PARSER->addNodeAST((yyval.node)); }
#line 2884 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 670 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new NewAST((yyvsp[-3].getvar), (yyvsp[-1].nodelist)); PARSER->addNodeAST((yyval.node)); }
#line 2890 "yyparser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 674 "yyparser.y" /* yacc.c:1646  */
    { (yyval.node) = new DeleteAST((yyvsp[0].getvar)); PARSER->addNodeAST((yyval.node)); }
#line 2896 "yyparser.cpp" /* yacc.c:1646  */
    break;


#line 2900 "yyparser.cpp" /* yacc.c:1646  */
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
#line 677 "yyparser.y" /* yacc.c:1906  */


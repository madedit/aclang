%{
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

%}

%define api.pure full
%debug
%error-verbose

//to avoid if-else conflicts warning message
%nonassoc IFX
%nonassoc TOK_ELSE
//to avoid this, this.xxx, this[xxx] conflicts warning message
%nonassoc THISX
%nonassoc TOK_DOT
%nonassoc TOK_LBRACKET

%union
{
    acToken token;
    NodeAST* node;
    BlockAST* block;
    GetVarAST* getvar;
    FunctionAST* func;
    StringList* arglist;
    NodeASTList* nodelist;
}

/* literal tokens */
%token <token> TOK_UNKNOWN TOK_EOF TOK_EOL TOK_SPACE TOK_COMMENT
%token <token> TOK_IDENTIFIER TOK_STRING TOK_CHAR TOK_UNS32 TOK_UNS64 TOK_FLOAT32 TOK_FLOAT64
/* operators */
%token <token> TOK_DIV          // /
%token <token> TOK_DIVASS       // /=
%token <token> TOK_DOT          // .
%token <token> TOK_DOTDOT       // ..
%token <token> TOK_DOTDOTDOT    // ...
%token <token> TOK_AND          // &
%token <token> TOK_ANDASS       // &=
%token <token> TOK_ANDAND       // &&
%token <token> TOK_OR           // |
%token <token> TOK_ORASS        // |=
%token <token> TOK_OROR         // ||
%token <token> TOK_MINUS        // -
%token <token> TOK_MINUSASS     // -=
%token <token> TOK_MINUSMINUS   // --
%token <token> TOK_PLUS         // +
%token <token> TOK_PLUSASS      // +=
%token <token> TOK_PLUSPLUS     // ++
%token <token> TOK_LT           // <
%token <token> TOK_LE           // <=
%token <token> TOK_SHL          // <<
%token <token> TOK_SHLASS       // <<=
%token <token> TOK_LG           // <>
%token <token> TOK_LEG          // <>=
%token <token> TOK_GT           // >
%token <token> TOK_GE           // >=
%token <token> TOK_SHRASS       // >>=
%token <token> TOK_USHRASS      // >>>=
%token <token> TOK_SHR          // >>
%token <token> TOK_USHR         // >>>
%token <token> TOK_NOT          // !
%token <token> TOK_NOTEQUAL     // !=
%token <token> TOK_UE           // !<>
%token <token> TOK_UNORD        // !<>=
%token <token> TOK_UGE          // !<
%token <token> TOK_UG           // !<=
%token <token> TOK_ULE          // !>
%token <token> TOK_UL           // !>=
%token <token> TOK_LPAREN       // (
%token <token> TOK_RPAREN       // )
%token <token> TOK_LBRACKET     // [
%token <token> TOK_RBRACKET     // ]
%token <token> TOK_LCURLY       // {
%token <token> TOK_RCURLY       // }
%token <token> TOK_QUESTION     // ?
%token <token> TOK_COMMA        // ,
%token <token> TOK_SEMICOLON    // ;
%token <token> TOK_COLON        // :
%token <token> TOK_COLONCOLON   // ::
%token <token> TOK_DOLLAR       // $
%token <token> TOK_ASSIGN       // =
%token <token> TOK_EQUAL        // ==
%token <token> TOK_MUL          // *
%token <token> TOK_MULASS       // *=
%token <token> TOK_MOD          // %
%token <token> TOK_MODASS       // %=
%token <token> TOK_XOR          // ^
%token <token> TOK_XORASS       // ^=
%token <token> TOK_CAT          // ~
%token <token> TOK_CATASS       // ~=
/* keywords */
%token <token> TOK_BASE
%token <token> TOK_BREAK
%token <token> TOK_CASE
%token <token> TOK_CATCH
%token <token> TOK_CONST
%token <token> TOK_CONTINUE
%token <token> TOK_DEFAULT
%token <token> TOK_DELEGATE
%token <token> TOK_DELETE
%token <token> TOK_DO
%token <token> TOK_ELSE
%token <token> TOK_ENUM
%token <token> TOK_EXTENDS
%token <token> TOK_FALSE
%token <token> TOK_FOR
%token <token> TOK_FOREACH
%token <token> TOK_FUNCTION
%token <token> TOK_IF
%token <token> TOK_IN
%token <token> TOK_INT
%token <token> TOK_LOCAL
%token <token> TOK_METAFUNCTION
%token <token> TOK_NAMESPACE
%token <token> TOK_NEW
%token <token> TOK_NULL
%token <token> TOK_RESUME
%token <token> TOK_RETURN
%token <token> TOK_SWITCH
%token <token> TOK_THIS
%token <token> TOK_THROW
%token <token> TOK_TRUE
%token <token> TOK_TRY
//%token <token> TOK_TYPEOF
%token <token> TOK_VAR
%token <token> TOK_WHILE
%token <token> TOK_YIELD
/* special tokens */
%token <token> STOK_FILE
%token <token> STOK_LINE
%token <token> STOK_DATE
%token <token> STOK_TIME
%token <token> STOK_TIMESTAMP
%token <token> STOK_VENDOR
%token <token> STOK_VERSION

/* operator precedence */
//%left TOK_PLUS TOK_MINUS
//%left TOK_MUL TOK_DIV

/* ast types */
%type <block> stmts block
%type <node> stmt expr inner_expr namespace_block
%type <node> expr_stmt decl_stmt var_decl_stmt selection_stmt labeled_stmt jump_stmt iteration_stmt foreach_stmt
%type <node> boolean numeric string keyvalue table element array
%type <token> unary_op assignment_op type_specifier
%type <node> primary_expr
%type <node> postfix_expr unary_expr multiplicative_expr additive_expr shift_expr 
%type <node> relational_expr equality_expr and_expr exclusive_or_expr inclusive_or_expr 
%type <node> logical_and_expr logical_or_expr conditional_expr assignment_expr
%type <func> func_decl local_func_decl anony_func_decl
%type <arglist> func_decl_arglist
%type <nodelist> var_decl argument_expr_list labeled_stmts keyvalue_list element_list
%type <getvar> getvar_primary_expr getvar_postfix_expr

%start program

%%
program:
      /*empty*/ { PARSER->setProgramBlockAST(NULL); }
    | stmts     { PARSER->setProgramBlockAST($1); }
    ;

stmts:
      stmt          { $$ = new BlockAST(); PARSER->addNodeAST($$); if($1 != NULL) $$->m_statements.push_back($1); }
    | stmts stmt    { if($2 != NULL) $1->m_statements.push_back($2); }
    ;

stmt:
      expr_stmt         { $$ = $1; }
    | decl_stmt         { $$ = $1; }
    | selection_stmt    { $$ = $1; }
    | jump_stmt         { $$ = $1; }
    | iteration_stmt    { $$ = $1; }
    | namespace_block   { $$ = $1; }
    ;

block:
      TOK_LCURLY stmts TOK_RCURLY   { $$ = $2; }
    | TOK_LCURLY TOK_RCURLY         { $$ = new BlockAST(); PARSER->addNodeAST($$); }
    ;

expr_stmt:
      TOK_SEMICOLON         { $$ = NULL; }
    | expr TOK_SEMICOLON    { $$ = $1; }
    | block                 { $$ = $1; }
    ;

primary_expr:
      TOK_NULL                          { $$ = new NullAST(); PARSER->addNodeAST($$); }
    | boolean                           { $$ = $1; }
    | numeric                           { $$ = $1; }
    | string                            { $$ = $1; }
    //| table                             { $$ = $1; } //conflicts with block
    | array                             { $$ = $1; }
    | getvar_primary_expr               { $$ = $1; }
    //| anony_func_decl                   { $$ = $1; }
    | TOK_LPAREN inner_expr TOK_RPAREN  { $$ = $2; }
    | TOK_THIS %prec THISX              { $$ = new GetVarAST(NULL, "this"); PARSER->addNodeAST($$); }
    ;

argument_expr_list:
      assignment_expr                               { $$ = new NodeASTList(); PARSER->addNodeAST($$); $$->push_back($1); }
    | table                                         { $$ = new NodeASTList(); PARSER->addNodeAST($$); $$->push_back($1); }
    | anony_func_decl                               { $$ = new NodeASTList(); PARSER->addNodeAST($$); $$->push_back($1); }
    | argument_expr_list TOK_COMMA assignment_expr  { $1->push_back($3); }
    | argument_expr_list TOK_COMMA table            { $1->push_back($3); }
    | argument_expr_list TOK_COMMA anony_func_decl  { $1->push_back($3); }
    ;

postfix_expr:
      primary_expr                                          { $$ = $1; }
    | postfix_expr TOK_DOT TOK_IDENTIFIER                   { $$ = new GetVarAST($1, $3.getRawString()); PARSER->addNodeAST($$); }
    | postfix_expr TOK_LBRACKET expr TOK_RBRACKET           { $$ = new GetVarAST($1, $3); PARSER->addNodeAST($$); }
    | postfix_expr TOK_LPAREN TOK_RPAREN                    { $$ = new CallAST($1, NULL); PARSER->addNodeAST($$); }
    | postfix_expr TOK_LPAREN argument_expr_list TOK_RPAREN { $$ = new CallAST($1, $3); PARSER->addNodeAST($$); }
    | postfix_expr TOK_PLUSPLUS                             { $$ = new PostfixIncrementAST($1, TOK_PLUSPLUS); PARSER->addNodeAST($$); }
    | postfix_expr TOK_MINUSMINUS                           { $$ = new PostfixIncrementAST($1, TOK_MINUSMINUS); PARSER->addNodeAST($$); }
    ;

unary_op:
    //TOK_AND
      TOK_PLUS
    | TOK_MINUS
    | TOK_CAT
    | TOK_NOT
    ;

unary_expr:
      postfix_expr              { $$ = $1; }
    | TOK_PLUSPLUS unary_expr   { $$ = new UnaryAST($2, TOK_PLUSPLUS); PARSER->addNodeAST($$); }
    | TOK_MINUSMINUS unary_expr { $$ = new UnaryAST($2, TOK_MINUSMINUS); PARSER->addNodeAST($$); }
    | unary_op unary_expr       { $$ = new UnaryAST($2, $1.m_type); PARSER->addNodeAST($$); }
    ;

multiplicative_expr:
      unary_expr                                { $$ = $1; }
    | multiplicative_expr TOK_MUL unary_expr    { $$ = new MultiplicativeAST($1, TOK_MUL, $3); PARSER->addNodeAST($$); }
    | multiplicative_expr TOK_DIV unary_expr    { $$ = new MultiplicativeAST($1, TOK_DIV, $3); PARSER->addNodeAST($$); }
    | multiplicative_expr TOK_MOD unary_expr    { $$ = new MultiplicativeAST($1, TOK_MOD, $3); PARSER->addNodeAST($$); }
    ;

additive_expr:
      multiplicative_expr                           { $$ = $1; }
    | additive_expr TOK_PLUS multiplicative_expr    { $$ = new AdditiveAST($1, TOK_PLUS, $3); PARSER->addNodeAST($$); }
    | additive_expr TOK_MINUS multiplicative_expr   { $$ = new AdditiveAST($1, TOK_MINUS, $3); PARSER->addNodeAST($$); }
    ;

shift_expr:
      additive_expr                     { $$ = $1; }
    | shift_expr TOK_SHL additive_expr  { $$ = new ShiftAST($1, TOK_SHL, $3); PARSER->addNodeAST($$); }
    | shift_expr TOK_SHR additive_expr  { $$ = new ShiftAST($1, TOK_SHR, $3); PARSER->addNodeAST($$); }
    ;

relational_expr:
      shift_expr                        { $$ = $1; }
    | relational_expr TOK_LT shift_expr { $$ = new RelationalAST($1, TOK_LT, $3); PARSER->addNodeAST($$); }
    | relational_expr TOK_GT shift_expr { $$ = new RelationalAST($1, TOK_GT, $3); PARSER->addNodeAST($$); }
    | relational_expr TOK_LE shift_expr { $$ = new RelationalAST($1, TOK_LE, $3); PARSER->addNodeAST($$); }
    | relational_expr TOK_GE shift_expr { $$ = new RelationalAST($1, TOK_GE, $3); PARSER->addNodeAST($$); }
    ;

equality_expr:
      relational_expr                            { $$ = $1; }
    | equality_expr TOK_EQUAL relational_expr    { $$ = new EqualityAST($1, TOK_EQUAL, $3); PARSER->addNodeAST($$); }
    | equality_expr TOK_NOTEQUAL relational_expr { $$ = new EqualityAST($1, TOK_NOTEQUAL, $3); PARSER->addNodeAST($$); }
    ;

and_expr:
      equality_expr                     { $$ = $1; }
    | and_expr TOK_AND equality_expr    { $$ = new AndAST($1, $3); PARSER->addNodeAST($$); }
    ;

exclusive_or_expr:
      and_expr                              { $$ = $1; }
    | exclusive_or_expr TOK_XOR and_expr    { $$ = new ExclusiveOrAST($1, $3); PARSER->addNodeAST($$); }
    ;

inclusive_or_expr:
      exclusive_or_expr                             { $$ = $1; }
    | inclusive_or_expr TOK_OR exclusive_or_expr    { $$ = new InclusiveOrAST($1, $3); PARSER->addNodeAST($$); }
    ;

logical_and_expr:
      inclusive_or_expr                             { $$ = $1; }
    | logical_and_expr TOK_ANDAND inclusive_or_expr { $$ = new LogicalAndAST($1, $3); PARSER->addNodeAST($$); }
    ;

logical_or_expr:
      logical_and_expr                          { $$ = $1; }
    | logical_or_expr TOK_OROR logical_and_expr { $$ = new LogicalOrAST($1, $3); PARSER->addNodeAST($$); }
    ;

conditional_expr:
      logical_or_expr                                               { $$ = $1; }
    | logical_or_expr TOK_QUESTION inner_expr TOK_COLON inner_expr  { $$ = new ConditionalAST($1, $3, $5); PARSER->addNodeAST($$); }
    ;

assignment_op:
      TOK_ASSIGN
    | TOK_DIVASS
    | TOK_ANDASS
    | TOK_ORASS
    | TOK_MINUSASS
    | TOK_PLUSASS
    | TOK_SHLASS
    | TOK_SHRASS
    | TOK_USHRASS
    | TOK_MULASS
    | TOK_MODASS
    | TOK_XORASS
    | TOK_CATASS
    ;

assignment_expr:
      conditional_expr                          { $$ = $1; }
    | unary_expr assignment_op assignment_expr  { $$ = new AssignmentAST($1, $2.m_type, $3); PARSER->addNodeAST($$); }
    | unary_expr assignment_op table            { $$ = new AssignmentAST($1, $2.m_type, $3); PARSER->addNodeAST($$); }
    | unary_expr assignment_op anony_func_decl  { $$ = new AssignmentAST($1, $2.m_type, $3); PARSER->addNodeAST($$); }
    ;

expr:
      assignment_expr { $$ = $1; }
    ;

inner_expr:
      expr              { $$ = $1; }
    | table             { $$ = $1; }
    | anony_func_decl   { $$ = $1; }
    ;

boolean:
      TOK_TRUE  { $$ = new BooleanAST(1); PARSER->addNodeAST($$); }
    | TOK_FALSE { $$ = new BooleanAST(0); PARSER->addNodeAST($$); }
    ;

numeric:
      TOK_UNS32 { $$ = new Int32AST($1.m_integerValue); PARSER->addNodeAST($$); }
    | TOK_UNS64 { $$ = new Int64AST($1.m_integerValue); PARSER->addNodeAST($$); }
    | TOK_FLOAT32 { $$ = new FloatAST($1.m_doubleValue); PARSER->addNodeAST($$); }
    | TOK_FLOAT64 { $$ = new DoubleAST($1.m_doubleValue); PARSER->addNodeAST($$); }
    ;

string:
      TOK_STRING    { $$ = new StringAST($1.toUTF8String(), $1.m_postfix); PARSER->addNodeAST($$); }
    ;

keyvalue:
      TOK_IDENTIFIER                                        { $$ = new KeyValueAST($1.getRawString(), NULL); PARSER->addNodeAST($$); }
    | TOK_IDENTIFIER TOK_ASSIGN inner_expr                  { $$ = new KeyValueAST($1.getRawString(), $3); PARSER->addNodeAST($$); }
    | TOK_LBRACKET expr TOK_RBRACKET TOK_ASSIGN inner_expr  { $$ = new KeyValueAST($2, $5); PARSER->addNodeAST($$); }
    | func_decl                                             { $$ = new KeyValueAST("", $1); PARSER->addNodeAST($$); }
    //json format
    | string TOK_COLON inner_expr   { $$ = new KeyValueAST(((StringAST*)$1)->m_val, $3); PARSER->addNodeAST($$); }
    ;

keyvalue_list:
      keyvalue                          { $$ = new NodeASTList(); PARSER->addNodeAST($$); $$->push_back($1); }
    | keyvalue_list TOK_COMMA keyvalue  { $1->push_back($3); }
    ;

table:
      TOK_LCURLY TOK_RCURLY                         { $$ = new TableAST(NULL); PARSER->addNodeAST($$); }
    | TOK_LCURLY keyvalue_list TOK_RCURLY           { $$ = new TableAST($2); PARSER->addNodeAST($$); }
    | TOK_LCURLY keyvalue_list TOK_COMMA TOK_RCURLY { $$ = new TableAST($2); PARSER->addNodeAST($$); }
    ;

element:
      inner_expr    { $$ = $1; }
    ;

element_list:
      element                           { $$ = new NodeASTList(); PARSER->addNodeAST($$); $$->push_back($1); }
    | element_list TOK_COMMA element    { $1->push_back($3); }
    ;

array:
      TOK_LBRACKET TOK_RBRACKET                         { $$ = new ArrayAST(NULL); PARSER->addNodeAST($$); }
    | TOK_LBRACKET element_list TOK_RBRACKET            { $$ = new ArrayAST($2); PARSER->addNodeAST($$); }
    | TOK_LBRACKET element_list TOK_COMMA TOK_RBRACKET  { $$ = new ArrayAST($2); PARSER->addNodeAST($$); }
    ;

type_specifier:
      TOK_VAR
    | TOK_LOCAL
    //| TOK_INT
    //| TOK_FLOAT
    ;

decl_stmt:
      var_decl_stmt     { $$ = $1; }
    | func_decl         { $$ = $1; }
    | local_func_decl   { $$ = $1; }
    ;

var_decl_stmt:
      var_decl TOK_SEMICOLON    { $$ = new VariableDeclarationListAST($1); PARSER->addNodeAST($$); }
    ;
    
getvar_primary_expr:
      TOK_IDENTIFIER                            { $$ = new GetVarAST(NULL, $1.getRawString(), GetVarAST::NONE); PARSER->addNodeAST($$); }
    | TOK_COLONCOLON TOK_IDENTIFIER             { $$ = new GetVarAST(NULL, $2.getRawString(), GetVarAST::GLOBAL); PARSER->addNodeAST($$); }
    | TOK_THIS TOK_DOT TOK_IDENTIFIER           { $$ = new GetVarAST(NULL, $3.getRawString(), GetVarAST::THIS); PARSER->addNodeAST($$); }
    | TOK_THIS TOK_LBRACKET expr TOK_RBRACKET   { $$ = new GetVarAST(NULL, $3, GetVarAST::THIS); PARSER->addNodeAST($$); }
    //| table TOK_DOT TOK_IDENTIFIER              { $$ = new GetVarAST($1, $3.getRawString(), GetVarAST::NONE); PARSER->addNodeAST($$); }
    //| table TOK_LBRACKET expr TOK_RBRACKET      { $$ = new GetVarAST($1, $3, GetVarAST::NONE); PARSER->addNodeAST($$); }
    ;

getvar_postfix_expr:
      getvar_primary_expr                                   { $$ = $1; }
    | getvar_postfix_expr TOK_DOT TOK_IDENTIFIER            { $$ = new GetVarAST($1, $3.getRawString()); PARSER->addNodeAST($$); }
    | getvar_postfix_expr TOK_LBRACKET expr TOK_RBRACKET    { $$ = new GetVarAST($1, $3); PARSER->addNodeAST($$); }

var_decl:
      type_specifier getvar_postfix_expr                    
        {
            $$ = new NodeASTList();
            PARSER->addNodeAST($$);
            VariableDeclarationAST* node = new VariableDeclarationAST($2, NULL, ($1.m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            $$->push_back(node);
        }
    | type_specifier getvar_postfix_expr TOK_ASSIGN inner_expr
        {
            $$ = new NodeASTList();
            PARSER->addNodeAST($$);
            VariableDeclarationAST* node = new VariableDeclarationAST($2, $4, ($1.m_type == TOK_LOCAL));
            PARSER->addNodeAST(node);
            $$->push_back(node);
        }
    | var_decl TOK_COMMA getvar_postfix_expr
        {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)$$->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST($3, NULL, node0->m_isLocal);
            PARSER->addNodeAST(node);
            $$->push_back(node);
        }
    | var_decl TOK_COMMA getvar_postfix_expr TOK_ASSIGN inner_expr
        {
            VariableDeclarationAST* node0 = (VariableDeclarationAST*)$$->m_nodeASTVec[0];
            VariableDeclarationAST* node = new VariableDeclarationAST($3, $5, node0->m_isLocal);
            PARSER->addNodeAST(node);
            $$->push_back(node);
        }
    ;

func_decl_arglist:
      TOK_IDENTIFIER                                            { $$ = new StringList(); PARSER->addNodeAST($$); $$->push_back($1.getRawString()); }
    | type_specifier TOK_IDENTIFIER                             { $$ = new StringList(); PARSER->addNodeAST($$); $$->push_back($2.getRawString()); }
    | func_decl_arglist TOK_COMMA TOK_IDENTIFIER
        {
            $1->push_back($3.getRawString());
            if($1->m_hasDuplicateStr)
            {
                yyerror("argument name is duplicate");
                YYABORT;
            }
        }
    | func_decl_arglist TOK_COMMA type_specifier TOK_IDENTIFIER
        {
            $1->push_back($4.getRawString());
            if($1->m_hasDuplicateStr)
            {
                yyerror("argument name is duplicate");
                YYABORT;
            }
        }
    ;

func_decl:
      TOK_FUNCTION getvar_postfix_expr TOK_LPAREN TOK_RPAREN block
        {
            $$ = new FunctionAST($2, NULL, $5);
            PARSER->addNodeAST($$);
        }
    | TOK_FUNCTION getvar_postfix_expr TOK_LPAREN func_decl_arglist TOK_RPAREN block
        {
            $$ = new FunctionAST($2, $4, $6);
            PARSER->addNodeAST($$);
        }
    ;

local_func_decl:
      TOK_LOCAL func_decl   { $2->m_isLocal = true; $$ = $2; }

anony_func_decl:
      TOK_FUNCTION TOK_LPAREN TOK_RPAREN block
        {
            $$ = new FunctionAST(NULL, NULL, $4);
            PARSER->addNodeAST($$);
        }
    | TOK_FUNCTION TOK_LPAREN func_decl_arglist TOK_RPAREN block
        {
            $$ = new FunctionAST(NULL, $3, $5);
            PARSER->addNodeAST($$);
        }
    ;

selection_stmt:
      TOK_IF TOK_LPAREN expr TOK_RPAREN stmt TOK_ELSE stmt  { $$ = new IfElseAST($3, $5, $7); PARSER->addNodeAST($$); }
    | TOK_IF TOK_LPAREN expr TOK_RPAREN stmt %prec IFX      { $$ = new IfElseAST($3, $5, NULL); PARSER->addNodeAST($$); }
    | TOK_SWITCH TOK_LPAREN expr TOK_RPAREN TOK_LCURLY labeled_stmts TOK_RCURLY
        { $$ = new SwitchAST($3, $6); PARSER->addNodeAST($$); }
    ;

labeled_stmts:
      labeled_stmt                  { $$ = new NodeASTList(); PARSER->addNodeAST($$); $$->add_case_ast((CaseAST*)($1)); }
    | labeled_stmts labeled_stmt
        {
            $1->add_case_ast((CaseAST*)($2));
            if($1->m_hasMultipleDefaultStmt)
            {
                yyerror("multiple default labels in one switch");
                YYABORT;
            }
        }
    ;

labeled_stmt:
      TOK_CASE expr TOK_COLON stmts { $$ = new CaseAST($2, $4); PARSER->addNodeAST($$); }
    | TOK_CASE expr TOK_COLON       { $$ = new CaseAST($2, NULL); PARSER->addNodeAST($$); }
    | TOK_DEFAULT TOK_COLON stmts   { $$ = new CaseAST(NULL, $3); PARSER->addNodeAST($$); }
    | TOK_DEFAULT TOK_COLON         { $$ = new CaseAST(NULL, NULL); PARSER->addNodeAST($$); }
    ;

jump_stmt:
      TOK_CONTINUE TOK_SEMICOLON            { $$ = new ContinueAST(); PARSER->addNodeAST($$); }
    | TOK_BREAK TOK_SEMICOLON               { $$ = new BreakAST(); PARSER->addNodeAST($$); }
    | TOK_RETURN TOK_SEMICOLON              { $$ = new ReturnAST(NULL); PARSER->addNodeAST($$); }
    | TOK_RETURN expr TOK_SEMICOLON         { $$ = new ReturnAST($2); PARSER->addNodeAST($$); }
    | TOK_RETURN table                      { $$ = new ReturnAST($2); PARSER->addNodeAST($$); }
    | TOK_RETURN anony_func_decl            { $$ = new ReturnAST($2); PARSER->addNodeAST($$); }
    ;

iteration_stmt:
      TOK_WHILE TOK_LPAREN expr TOK_RPAREN stmt                         { $$ = new WhileAST($3, $5); PARSER->addNodeAST($$); }
    | TOK_DO stmt TOK_WHILE TOK_LPAREN expr TOK_RPAREN TOK_SEMICOLON    { $$ = new DoWhileAST($5, $2); PARSER->addNodeAST($$); }
    | TOK_FOR TOK_LPAREN expr_stmt expr_stmt TOK_RPAREN stmt            { $$ = new ForAST($3, $4, NULL, $6); PARSER->addNodeAST($$); }
    | TOK_FOR TOK_LPAREN expr_stmt expr_stmt expr TOK_RPAREN stmt       { $$ = new ForAST($3, $4, $5, $7); PARSER->addNodeAST($$); }
    | TOK_FOR TOK_LPAREN var_decl_stmt expr_stmt TOK_RPAREN stmt        { $$ = new ForAST($3, $4, NULL, $6); PARSER->addNodeAST($$); }
    | TOK_FOR TOK_LPAREN var_decl_stmt expr_stmt expr TOK_RPAREN stmt   { $$ = new ForAST($3, $4, $5, $7); PARSER->addNodeAST($$); }
    | foreach_stmt                                                      { $$ = $1; }
    ;

foreach_stmt:
      TOK_FOREACH TOK_LPAREN getvar_postfix_expr TOK_IN inner_expr TOK_RPAREN stmt
        {
            $$ = new ForeachAST(0, NULL, $3, $5, $7);
            PARSER->addNodeAST($$);
        }
    | TOK_FOREACH TOK_LPAREN getvar_postfix_expr TOK_COMMA getvar_postfix_expr TOK_IN inner_expr TOK_RPAREN stmt
        {
            $$ = new ForeachAST(0, $3, $5, $7, $9);
            PARSER->addNodeAST($$);
        }
    | TOK_FOREACH TOK_LPAREN TOK_VAR getvar_postfix_expr TOK_IN inner_expr TOK_RPAREN stmt
        {
            $$ = new ForeachAST(TOK_VAR, NULL, $4, $6, $8);
            PARSER->addNodeAST($$);
        }
    | TOK_FOREACH TOK_LPAREN TOK_VAR getvar_postfix_expr TOK_COMMA getvar_postfix_expr TOK_IN inner_expr TOK_RPAREN stmt
        {
            $$ = new ForeachAST(TOK_VAR, $4, $6, $8, $10);
            PARSER->addNodeAST($$);
        }
    | TOK_FOREACH TOK_LPAREN TOK_LOCAL getvar_postfix_expr TOK_IN inner_expr TOK_RPAREN stmt
        {
            $$ = new ForeachAST(TOK_LOCAL, NULL, $4, $6, $8);
            PARSER->addNodeAST($$);
        }
    | TOK_FOREACH TOK_LPAREN TOK_LOCAL getvar_postfix_expr TOK_COMMA getvar_postfix_expr TOK_IN inner_expr TOK_RPAREN stmt
        {
            $$ = new ForeachAST(TOK_LOCAL, $4, $6, $8, $10);
            PARSER->addNodeAST($$);
        }
    ;

namespace_block:
      TOK_NAMESPACE getvar_postfix_expr TOK_LCURLY stmts TOK_RCURLY { $$ = new NamespaceAST($2, $4); PARSER->addNodeAST($$); }
    | TOK_NAMESPACE getvar_postfix_expr TOK_LCURLY TOK_RCURLY       { $$ = new NamespaceAST($2, NULL); PARSER->addNodeAST($$); }
    ;

%%

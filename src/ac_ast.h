/* see copyright notice in aclang.h */

#ifndef AC_AST_H
#define AC_AST_H

#include "ac_config.h"
#include <llvm/IR/Value.h>
#include <vector>
#include <stdio.h>

using namespace llvm;

typedef int acTokenType;
class acCodeGenerator;
struct acCodeGenBlock;

extern const char* getTokenString(acTokenType type);

class NodeAST
{
public:
    enum NodeASTType
    {
        tNodeAST,
        tNodeASTList,
        tStringList,
        tNullAST,
        tBooleanAST,
        tInt32AST,
        tInt64AST,
        tFloatAST,
        tDoubleAST,
        tStringAST,
        tKeyValueAST,
        tTableAST,
        tArrayAST,
        tGetVarAST,
        tVariableDeclarationAST,
        tVariableDeclarationListAST,
        tCallAST,
        tFunctionAST,
        tReturnAST,
        tBlockAST,
        tPostfixIncrementAST,
        tUnaryAST,
        tMultiplicativeAST,
        tAdditiveAST,
        tShiftAST,
        tRelationalAST,
        tEqualityAST,
        tAndAST,
        tExclusiveOrAST,
        tInclusiveOrAST,
        tLogicalAndAST,
        tLogicalOrAST,
        tConditionalAST,
        tAssignmentAST,
        tIfElseAST,
        tSwitchAST,
        tCaseAST,
        tContinueAST,
        tBreakAST,
        tWhileAST,
        tDoWhileAST,
        tForAST,
        tForeachAST,
        tNamespaceAST,
    };
    NodeASTType m_type;

    NodeAST() : m_type(tNodeAST) {}
    virtual ~NodeAST() {}
    virtual Value* codeGen(acCodeGenerator* cg) = 0;
    virtual void print(int indent) = 0;
    void printIndent(int indent)
    {
        while(indent-- > 0)
        {
            printf(" ");
        }
    }
};

typedef std::vector<NodeAST*> NodeASTVec;
typedef std::vector<std::string> StringVec;
class CaseAST;

class NodeASTList : public NodeAST
{
public:
    NodeASTVec m_nodeASTVec;
    bool m_hasMultipleDefaultStmt;

    NodeASTList()
    {
        m_type = tNodeASTList;
        m_hasMultipleDefaultStmt = false;
    }
    virtual ~NodeASTList()
    {
        m_nodeASTVec.clear();
    }
    virtual Value* codeGen(acCodeGenerator* cg) { return 0; }
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[NodeASTList]:\n");
        NodeASTVec::iterator it = m_nodeASTVec.begin();
        for(; it != m_nodeASTVec.end(); ++it)
        {
            (*it)->print(indent+2);
        }
    }
    void push_back(NodeAST* node) { m_nodeASTVec.push_back(node); }

    //for switch-case ast only;
    void add_case_ast(CaseAST* node);
};

class StringList : public NodeAST
{
public:
    StringVec m_stringVec;
    bool m_hasDuplicateStr;

    StringList()
    {
        m_type = tStringList;
        m_hasDuplicateStr = false;
    }
    virtual ~StringList()
    {
        m_stringVec.clear();
    }
    virtual Value* codeGen(acCodeGenerator* cg) { return 0; }
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[StringList]:\n");
        StringVec::iterator it = m_stringVec.begin();
        for(; it != m_stringVec.end(); ++it)
        {
            printIndent(indent+2);
            printf("%s\n", it->c_str());
        }
    }
    void push_back(const std::string& str)
    {
        for(size_t i = 0; i < m_stringVec.size(); ++i)
        {
            if(str.compare(m_stringVec[i]) == 0)
            {
                m_hasDuplicateStr = true;
                break;
            }
        }
        m_stringVec.push_back(str);
    }

};

class NullAST : public NodeAST
{
public:
    NullAST()
    {
        m_type = tNullAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[NullAST]\n");
    }
};

class BooleanAST : public NodeAST
{
public:
    int m_val;
    BooleanAST(int val)
        : m_val(val)
    {
        m_type = tBooleanAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[BooleanAST]: m_val=%d\n", m_val);
    }
};

class Int32AST : public NodeAST
{
public:
    acUInt32 m_val;
    Int32AST(acUInt32 val)
        : m_val(val)
    {
        m_type = tInt32AST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[Int32AST]: m_val=%d\n", m_val);
    }
};

class Int64AST : public NodeAST
{
public:
    acUInt64 m_val;
    Int64AST(acUInt64 val)
        : m_val(val)
    {
        m_type = tInt64AST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[Int64AST]: m_val=%llu\n", m_val);
    }
};

class FloatAST : public NodeAST
{
public:
    acFloat m_val;
    FloatAST(acFloat val)
        : m_val(val)
    {
        m_type = tFloatAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[FloatAST]: m_val=%f\n", m_val);
    }
};

class DoubleAST : public NodeAST
{
public:
    acDouble m_val;
    DoubleAST(acDouble val)
        : m_val(val)
    {
        m_type = tDoubleAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[DoubleAST]: m_val=%f\n", m_val);
    }
};

class StringAST : public NodeAST
{
public:
    std::string m_val;
    char m_postfix;
    StringAST(const std::string& str, char postfix)
        : m_val(str)
        , m_postfix(postfix)
    {
        m_type = tStringAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[StringAST]: m_val=%s, m_postfix=%c\n", m_val.c_str(), m_postfix);
    }
};

class KeyValueAST : public NodeAST
{
public:
    std::string m_key;
    NodeAST* m_keyExpr;
    NodeAST* m_value;

    KeyValueAST(const std::string& key, NodeAST* value)
        : m_key(key)
        , m_keyExpr(0)
        , m_value(value)
    {
        m_type = tKeyValueAST;
    }
    KeyValueAST(NodeAST* key, NodeAST* value)
        : m_key()
        , m_keyExpr(key)
        , m_value(value)
    {
        m_type = tKeyValueAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg){return 0;}
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[KeyValueAST]:\n");
        if(m_key.length() > 0)
        {
            printIndent(indent+2);
            printf("m_key: %s\n", m_key.c_str());
        }
        else
        {
            printIndent(indent+2);
            printf("m_keyExpr:\n");
            m_keyExpr->print(indent+2);
        }
        if(m_value != 0)
        {
            printIndent(indent+2);
            printf("m_value:\n");
            m_value->print(indent+2);
        }
    }
};

class TableAST : public NodeAST
{
public:
    NodeASTList* m_keyValueList;
    TableAST(NodeASTList* keyValueList)
        : m_keyValueList(keyValueList)
    {
        m_type = tTableAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        if(m_keyValueList == 0)
        {
            printf("[TableAST]: {} \n");
        }
        else
        {
            printf("[TableAST]:\n");
            m_keyValueList->print(indent+2);
        }
    }
};

class ArrayAST : public NodeAST
{
public:
    NodeASTList* m_elementList;
    ArrayAST(NodeASTList* elementList)
        : m_elementList(elementList)
    {
        m_type = tArrayAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        if(m_elementList == 0)
        {
            printf("[ArrayAST]: [] \n");
        }
        else
        {
            printf("[ArrayAST]:\n");
            m_elementList->print(indent+2);
        }
    }
};

//key or table.key or table[key] or array[index]
class GetVarAST : public NodeAST
{
public:
    NodeAST* m_parentExpr;
    std::string m_keyIdentifier;
    NodeAST* m_keyExpr;
    enum Scope
    {
        NONE,   //not specified
        GLOBAL, //::key
        THIS,   //this.key or this[key]
    };
    Scope m_scope;
    int m_isFuncCall;
    //for codegen
    Value* m_parent;
    
    GetVarAST(NodeAST* parentExpr, const std::string& key, Scope scope = NONE)
        : m_parentExpr(parentExpr)
        , m_keyIdentifier(key)
        , m_keyExpr(0)
        , m_scope(scope)
        , m_isFuncCall(0)
        , m_parent(0)
    {
        m_type = tGetVarAST;
    }
    GetVarAST(NodeAST* parentExpr, NodeAST* key, Scope scope = NONE)
        : m_parentExpr(parentExpr)
        , m_keyIdentifier()
        , m_keyExpr(key)
        , m_scope(scope)
        , m_isFuncCall(0)
        , m_parent(0)
    {
        m_type = tGetVarAST;
    }

    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[GetVarAST]:\n");

        printIndent(indent+2);
        printf("m_parentExpr:\n");
        if(m_parentExpr!=0) m_parentExpr->print(indent+2);

        printIndent(indent+2);
        printf("m_scope: ");
        switch(m_scope)
        {
        case NONE: printf("NONE\n"); break;
        case GLOBAL: printf("GLOBAL\n"); break;
        case THIS: printf("THIS\n"); break;
        }

        printIndent(indent+2);
        if(!m_keyIdentifier.empty())
        {
            printf("m_keyIdentifier: %s\n", m_keyIdentifier.c_str());
        }
        else
        {
            printf("m_keyExpr:\n");
            m_keyExpr->print(indent+2);
        }
    }
};

class VariableDeclarationAST : public NodeAST
{
public:
    GetVarAST* m_varExpr;
    NodeAST* m_assignmentExpr;
    bool m_isLocal;

    VariableDeclarationAST(GetVarAST* varExpr, NodeAST* expr, bool isLocal = false)
        : m_varExpr(varExpr)
        , m_assignmentExpr(expr)
        , m_isLocal(isLocal)
    {
        m_type = tVariableDeclarationAST;
    }

    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[VariableDeclarationAST]:\n");
        printIndent(indent+2);
        printf("m_varExpr:\n");
        m_varExpr->print(indent+2);
        printIndent(indent+2);
        printf("m_isLocal: %d\n", (int)m_isLocal);
        if(m_assignmentExpr != 0)
        {
            printIndent(indent+2);
            printf("m_assignmentExpr:\n");
            m_assignmentExpr->print(indent+2);
        }
    }
};

class VariableDeclarationListAST : public NodeAST
{
public:
    NodeASTList* m_varDeclList;

    VariableDeclarationListAST(NodeASTList* varDeclList)
        : m_varDeclList(varDeclList)
    {
        m_type = tVariableDeclarationListAST;
    }

    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[VariableDeclarationListAST]:\n");
        m_varDeclList->print(indent+2);
    }
};

class FunctionAST : public NodeAST
{
public:
    GetVarAST* m_nameExpr;
    StringList* m_args;
    NodeAST* m_body;
    bool m_isLocal;
    bool m_isVarArg;//TODO:Variable-Length Argument

    //for codegen
    acCodeGenBlock* m_upblock;
    Instruction* m_buildUpValueTableInsertPoint;
    acCodeGenBlock* m_localblock;
    Instruction* m_localUpValueInsertPoint;
    Value* m_upValueTable;
    Value* m_localUpValueTable;
    Value* m_funcVar;

    FunctionAST(GetVarAST* name, StringList* args, NodeAST* body, bool isLocal = false)
        : m_nameExpr(name)
        , m_args(args)
        , m_body(body)
        , m_isLocal(isLocal)
        , m_isVarArg(false)
        , m_upblock(0)
        , m_buildUpValueTableInsertPoint(0)
        , m_localblock(0)
        , m_localUpValueInsertPoint(0)
        , m_upValueTable(0)
        , m_localUpValueTable(0)
        , m_funcVar(0)
    {
        m_type = tFunctionAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    Value* codeGenForUpValue(acCodeGenerator* cg, const std::string& name, Value* upValue);

    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[FunctionAST]:\n");
        printIndent(indent+2);
        printf("m_isLocal: %d\n", (int)m_isLocal);
        printIndent(indent+2);
        printf("m_nameExpr:\n");
        if(m_nameExpr == 0)
        {
            printIndent(indent+2);
            printf("anonymous function\n");
        }
        else
        {
            m_nameExpr->print(indent+2);
        }
        if(m_args != 0)
        {
            printIndent(indent+2);
            printf("m_args: ");
            for(size_t i = 0; i < m_args->m_stringVec.size(); ++i)
            {
                printf("%s ", (m_args->m_stringVec)[i].c_str());
            }
            printf("\n");
        }
        printIndent(indent+2);
        printf("m_body:\n");
        m_body->print(indent+2);
    }
};

class CallAST : public NodeAST
{
public:
    NodeAST* m_callee;
    NodeASTList* m_args;

    CallAST(NodeAST* callee, NodeASTList* args)
        : m_callee(callee)
        , m_args(args)
    {
        m_type = tCallAST;
    }

    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[CallAST]:\n");
        printIndent(indent+2);
        printf("m_callee:\n");
        m_callee->print(indent+2);
        if(m_args != 0)
        {
            printIndent(indent+2);
            printf("m_args:\n");
            m_args->print(indent+4);
        }
    }
};

class ReturnAST : public NodeAST
{
public:
    NodeAST* m_expr;
    ReturnAST(NodeAST* expr)
        : m_expr(expr)
    {
        m_type = tReturnAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ReturnAST]:\n");
        if(m_expr != 0)
        {
            printIndent(indent+2);
            printf("m_expr:\n");
            m_expr->print(indent+2);
        }
        else
        {
            printIndent(indent+2);
            printf("return;\n");
        }
    }
};

class BlockAST : public NodeAST
{
public:
    NodeASTVec m_statements;
    BlockAST()
    {
        m_type = tBlockAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[BlockAST]:\n");
        NodeASTVec::iterator it = m_statements.begin();
        for(int i = 0; it != m_statements.end(); ++it, ++i)
        {
            printIndent(indent+2);
            printf("m_statements[%d]:\n", i);
            (*it)->print(indent+2);
        }
    }
};

class PostfixIncrementAST : public NodeAST
{
public:
    NodeAST* m_expr;
    acTokenType m_op;
    PostfixIncrementAST(NodeAST* expr, acTokenType op)
        : m_expr(expr)
        , m_op(op)
    {
        m_type = tPostfixIncrementAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[PostfixIncrementAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr:\n");
        m_expr->print(indent+2);
    }
};

class UnaryAST : public NodeAST
{
public:
    NodeAST* m_expr;
    acTokenType m_op;
    UnaryAST(NodeAST* expr, acTokenType op)
        : m_expr(expr)
        , m_op(op)
    {
        m_type = tUnaryAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[UnaryAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr:\n");
        m_expr->print(indent+2);
    }
};

class MultiplicativeAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    acTokenType m_op;
    MultiplicativeAST(NodeAST* expr1, acTokenType op, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
        , m_op(op)
    {
        m_type = tMultiplicativeAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[MultiplicativeAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class AdditiveAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    acTokenType m_op;
    AdditiveAST(NodeAST* expr1, acTokenType op, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
        , m_op(op)
    {
        m_type = tAdditiveAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[AdditiveAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class ShiftAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    acTokenType m_op;
    ShiftAST(NodeAST* expr1, acTokenType op, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
        , m_op(op)
    {
        m_type = tShiftAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ShiftAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class RelationalAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    acTokenType m_op;
    RelationalAST(NodeAST* expr1, acTokenType op, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
        , m_op(op)
    {
        m_type = tRelationalAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[RelationalAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class EqualityAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    acTokenType m_op;
    EqualityAST(NodeAST* expr1, acTokenType op, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
        , m_op(op)
    {
        m_type = tEqualityAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[EqualityAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class AndAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    AndAST(NodeAST* expr1, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
    {
        m_type = tAndAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[AndAST]: m_op: &\n");
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class ExclusiveOrAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    ExclusiveOrAST(NodeAST* expr1, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
    {
        m_type = tExclusiveOrAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ExclusiveOrAST]: m_op: ^\n");
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class InclusiveOrAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    InclusiveOrAST(NodeAST* expr1, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
    {
        m_type = tInclusiveOrAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[InclusiveOrAST]: m_op: |\n");
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class LogicalAndAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    LogicalAndAST(NodeAST* expr1, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
    {
        m_type = tLogicalAndAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[LogicalAndAST]: m_op: &&\n");
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class LogicalOrAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    LogicalOrAST(NodeAST* expr1, NodeAST* expr2)
        : m_expr1(expr1)
        , m_expr2(expr2)
    {
        m_type = tLogicalOrAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[LogicalAndAST]: m_op: ||\n");
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class ConditionalAST : public NodeAST
{
public:
    NodeAST* m_operand1;
    NodeAST* m_operand2;
    NodeAST* m_operand3;
    ConditionalAST(NodeAST* oprd1, NodeAST* oprd2, NodeAST* oprd3)
        : m_operand1(oprd1)
        , m_operand2(oprd2)
        , m_operand3(oprd3)
    {
        m_type = tConditionalAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ConditionalAST]: m_op: ?:\n");
        printIndent(indent+2);
        printf("m_operand1:\n");
        m_operand1->print(indent+2);
        printIndent(indent+2);
        printf("m_operand2:\n");
        m_operand2->print(indent+2);
        printIndent(indent+2);
        printf("m_operand3:\n");
        m_operand3->print(indent+2);
    }
};

class AssignmentAST : public NodeAST
{
public:
    NodeAST* m_expr1;
    NodeAST* m_expr2;
    acTokenType m_op;
    AssignmentAST(NodeAST* lhs, acTokenType op, NodeAST* rhs)
        : m_expr1(lhs)
        , m_expr2(rhs)
        , m_op(op)
    {
        m_type = tAssignmentAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[AssignmentAST]: m_op: %s\n", getTokenString(m_op));
        printIndent(indent+2);
        printf("m_expr1:\n");
        m_expr1->print(indent+2);
        printIndent(indent+2);
        printf("m_expr2:\n");
        m_expr2->print(indent+2);
    }
};

class IfElseAST : public NodeAST
{
public:
    NodeAST* m_cond;
    NodeAST* m_thenStmt;
    NodeAST* m_elseStmt;
    IfElseAST(NodeAST* cond, NodeAST* thenStmt, NodeAST* elseStmt)
        : m_cond(cond)
        , m_thenStmt(thenStmt)
        , m_elseStmt(elseStmt)
    {
        m_type = tIfElseAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[IfElseAST]:\n");
        printIndent(indent+2);
        printf("m_cond:\n");
        m_cond->print(indent+2);
        printIndent(indent+2);
        printf("m_thenStmt:\n");
        m_thenStmt->print(indent+2);
        if(m_elseStmt != 0)
        {
            printIndent(indent+2);
            printf("m_elseStmt:\n");
            m_elseStmt->print(indent+2);
        }
    }
};

class SwitchAST : public NodeAST
{
public:
    NodeAST* m_cond;
    NodeASTList* m_labeledStmts;
    SwitchAST(NodeAST* cond, NodeASTList* labeledStmts)
        : m_cond(cond)
        , m_labeledStmts(labeledStmts)
    {
        m_type = tSwitchAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[SwitchAST]:\n");
        printIndent(indent+2);
        printf("m_cond:\n");
        m_cond->print(indent+2);
        printIndent(indent+2);
        printf("m_labeledStmts:\n");
        m_labeledStmts->print(indent+2);
    }
};

class CaseAST : public NodeAST
{
public:
    NodeAST* m_expr;//if expr is NULL, this is 'default:' statement.
    BlockAST* m_stmts;
    //for codegen
    BasicBlock* m_swcase;
    BasicBlock* m_swblock;

    CaseAST(NodeAST* expr, BlockAST* stmts)
        : m_expr(expr)
        , m_stmts(stmts)
        , m_swcase(0)
        , m_swblock(0)
    {
        m_type = tCaseAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[CaseAST]: %s\n", m_expr==0? "default" : "case");
        if(m_expr != 0)
        {
            printIndent(indent+2);
            printf("m_expr:\n");
            m_expr->print(indent+2);
        }
        printIndent(indent+2);
        if(m_stmts==0)
        {
            printf("m_stmts: null\n");
        }
        else
        {
            printf("m_stmts:\n");
            m_stmts->print(indent+2);
        }
    }
};

class BreakAST : public NodeAST
{
public:
    BreakAST()
    {
        m_type = tBreakAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[BreakAST]: break;\n");
    }
};

class ContinueAST : public NodeAST
{
public:
    ContinueAST()
    {
        m_type = tContinueAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ContinueAST]: continue;\n");
    }
};

class WhileAST : public NodeAST
{
public:
    NodeAST* m_cond;
    NodeAST* m_stmt;
    BasicBlock* m_condblock;
    WhileAST(NodeAST* cond, NodeAST* stmt)
        : m_cond(cond)
        , m_stmt(stmt)
        , m_condblock(0)
    {
        m_type = tWhileAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[WhileAST]:\n");
        printIndent(indent+2);
        printf("m_cond:\n");
        m_cond->print(indent+2);
        printIndent(indent+2);
        printf("m_stmt:\n");
        m_stmt->print(indent+2);
    }
};

class DoWhileAST : public NodeAST
{
public:
    NodeAST* m_cond;
    NodeAST* m_stmt;
    BasicBlock* m_condblock;
    DoWhileAST(NodeAST* cond, NodeAST* stmt)
        : m_cond(cond)
        , m_stmt(stmt)
    {
        m_type = tDoWhileAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[DoWhileAST]:\n");
        printIndent(indent+2);
        printf("m_cond:\n");
        m_cond->print(indent+2);
        printIndent(indent+2);
        printf("m_stmt:\n");
        m_stmt->print(indent+2);
    }
};

class ForAST : public NodeAST
{
public:
    NodeAST* m_init;
    NodeAST* m_cond;
    NodeAST* m_inc;
    NodeAST* m_stmt;
    BasicBlock* m_incblock;
    ForAST(NodeAST* init, NodeAST* cond, NodeAST* inc, NodeAST* stmt)
        : m_init(init)
        , m_cond(cond)
        , m_inc(inc)
        , m_stmt(stmt)
        , m_incblock(0)
    {
        m_type = tForAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ForAST]:\n");
        printIndent(indent+2);
        printf("m_init:\n");
        if(m_init != 0)
        {
            printf("m_init:\n");
            m_init->print(indent+2);
        }
        else
        {
            printf("m_init: NULL\n");
        }
        printIndent(indent+2);
        if(m_cond != 0)
        {
            printf("m_cond:\n");
            m_cond->print(indent+2);
        }
        else
        {
            printf("m_cond: NULL\n");
        }
        printIndent(indent+2);
        if(m_inc != 0)
        {
            printf("m_inc:\n");
            m_inc->print(indent+2);
        }
        else
        {
            printf("m_inc: NULL\n");
        }
        printIndent(indent+2);
        printf("m_stmt:\n");
        m_stmt->print(indent+2);
    }
};

class ForeachAST : public NodeAST
{
public:
    int m_declTok;
    GetVarAST* m_var1;
    GetVarAST* m_var2;
    NodeAST* m_container;
    NodeAST* m_stmt;
    BasicBlock* m_condblock;
    ForeachAST(int declTok, GetVarAST* var1, GetVarAST* var2, NodeAST* container, NodeAST* stmt)
        : m_declTok(declTok)
        , m_var1(var1)
        , m_var2(var2)
        , m_container(container)
        , m_stmt(stmt)
        , m_condblock(0)
    {
        m_type = tForeachAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[ForeachAST]:\n");
        printIndent(indent+2);
        printf("m_m_declTok: %s\n", (m_declTok==0? "NULL": getTokenString(m_declTok)) );
        if(m_var1 != 0)
        {
            printIndent(indent+2);
            printf("m_var1:\n");
            m_var1->print(indent+2);
        }
        printIndent(indent+2);
        printf("m_var2:\n");
        m_var2->print(indent+2);
        printIndent(indent+2);
        printf("m_container:\n");
        m_container->print(indent+2);
        printIndent(indent+2);
        if(m_stmt != 0)
        {
            printf("m_stmt:\n");
            m_stmt->print(indent+2);
        }
        else
        {
            printf("m_stmt: NULL\n");
        }
    }
};

class NamespaceAST : public NodeAST
{
public:
    GetVarAST* m_name;
    BlockAST* m_block;
    NamespaceAST(GetVarAST* name, BlockAST* block)
        : m_name(name)
        , m_block(block)
    {
        m_type = tNamespaceAST;
    }
    virtual Value* codeGen(acCodeGenerator* cg);
    virtual void print(int indent)
    {
        printIndent(indent);
        printf("[NamespaceAST]:\n");
        printIndent(indent+2);
        printf("m_name:\n");
        m_name->print(indent+2);
        if(m_block != 0)
        {
            printIndent(indent+2);
            printf("m_block:\n");
            m_block->print(indent+2);
        }
    }
};

#endif //AC_AST_H

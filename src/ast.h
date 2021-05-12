#ifndef H_AST
#define H_AST

#include "werror.h"
#include <string>
#include <vector>

namespace AST
{
    WError werror;

    class Id
    {
        std::string id;
        int size;

    public:
        Id(std::string id, int size);
        Id(std::string id);
        ~Id();
    };

    // Expression
    class Expression
    {
    public:
        Expression();
        ~Expression();
    };

    class LiteralExpression : Expression
    {
    public:
        LiteralExpression();
        ~LiteralExpression();
    };

    class IntegerLiteralExpression : LiteralExpression
    {
    public:
        IntegerLiteralExpression(int value, int size);
        int value;
        int size;
        ~IntegerLiteralExpression();
    };

    class FloatLiteralExpression : LiteralExpression
    {
    public:
        FloatLiteralExpression(double value, int size);
        double value;
        int size;
        ~FloatLiteralExpression();
    };

    class BoolLiteralExpression : LiteralExpression
    {
    public:
        BoolLiteralExpression(bool value);
        bool value;
        ~BoolLiteralExpression();
    };

    class ByteLiteralExpression : LiteralExpression
    {
    public:
        ByteLiteralExpression(unsigned char value);
        unsigned char value;
        ~ByteLiteralExpression();
    };

    class StringLiteralExpression : LiteralExpression
    {
    public:
        StringLiteralExpression(std::string value);
        std::string value;
        ~StringLiteralExpression();
    };

    // Statement
    class Statement
    {
    public:
        Statement();
        ~Statement();
    };

    class BlockStatement : Statement
    {
    public:
        BlockStatement(std::vector<Statement *> *statementList, std::vector<IdentifierDeclaration *> *idList);
        std::vector<IdentifierDeclaration *> *idList;
        std::vector<Statement *> *statementList;
        ~BlockStatement();
    };

    class AssignStatement : Statement
    {
    public:
        AssignStatement(AssignOperations op, Expression *expr);
        AssignOperations op;
        Expression *expr;
        ~AssignStatement();
    };

    class IfStatement : Statement
    {
    public:
        IfStatement(Expression *condition, BlockStatement *if_block, BlockStatement *else_block);
        Expression *condition;
        BlockStatement *if_block;
        BlockStatement *else_block;
        ~IfStatement();
    };

    class LoopStatement : Statement
    {
    public:
        LoopStatement(Expression *, Expression *, BlockStatement *, std::string id);
        BlockStatement *block;
        ~LoopStatement();
    };

    class LoopForStatement : LoopStatement
    {
    public:
        LoopForStatement(Expression *initCondition, Expression *endCondition, BlockStatement *block, std::string id);
        std::string id;
        Expression *initCondition;
        Expression *endCondition;
        ~LoopForStatement();
    };

    class LoopWhileStatement : LoopStatement
    {
    public:
        LoopWhileStatement(Expression *condition, BlockStatement *block);
        Expression *condition;
        ~LoopWhileStatement();
    };

    class LoopCounterStatement : LoopStatement
    {
    public:
        LoopCounterStatement(Expression *condition, BlockStatement *block, std::string id);
        std::string id;
        Expression *condition;
        ~LoopCounterStatement();
    };

    class ReturnStatement : Statement
    {
    public:
        ReturnStatement();
        ~ReturnStatement();
    };

    class ContinueStatement : Statement
    {
    public:
        ContinueStatement();
        ~ContinueStatement();
    };

    class BreakStatement : Statement
    {
    public:
        BreakStatement();
        ~BreakStatement();
    };

    class ImportStatement : Statement
    {
    public:
        ImportStatement();
        ~ImportStatement();
    };

    // Operation
    class Operation
    {
    public:
        Operation();
        ~Operation();
    };

    class BinaryOperation : Operation
    {
    public:
        BinaryOperation(Expression *left, Expression *right, BinaryOperations op);
        Expression *left;
        Expression *right;
        BinaryOperations op;
        ~BinaryOperation();
    };

    class UnaryOperation : Operation
    {
    public:
        UnaryOperation(Expression *expr, UnaryOperations op);
        Expression *expr;
        UnaryOperations op;
        ~UnaryOperation();
    };

    // Declaration
    class Declaration
    {
    public:
        Declaration();
        ~Declaration();
    };

    class IdentifierDeclaration : Declaration
    {
    public:
        IdentifierDeclaration();
        ~IdentifierDeclaration();
    };

    class StructDeclaration : Declaration
    {
    public:
        StructDeclaration();
        ~StructDeclaration();
    };

    class FunctionDeclaration : Declaration
    {
    public:
        FunctionDeclaration();
        ~FunctionDeclaration();
    };

    // Call
    class Call
    {
    public:
        Call();
        ~Call();
    };

    class StructCall : Call
    {
    public:
        StructCall();
        ~StructCall();
    };

    class FunctionCall : Call
    {
    public:
        FunctionCall();
        ~FunctionCall();
    };

    enum class DataTypes
    {
        I8,
        I16,
        I32,
        I64,
        U8,
        U16,
        U32,
        U64,
        F8,
        F16,
        F32,
        F64,
        BOOL,
        BYTE,
        STRING
    };

    enum class AssignOperations
    {
        PLUS_EQUAL,
        MINUS_EQUAL,
        EQUAL
    };

    enum class BinaryOperations
    {
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        LESS_THAN,
        GREATER_THAN,
        LESS_EQUAL,
        GREATER_EQUAL,
        NOT_EQUAL,
        EQUAL_EQUAL,
        AND,
        OR
    };

    enum class UnaryOperations
    {
        MINUS,
        NOT
    };
}
#endif
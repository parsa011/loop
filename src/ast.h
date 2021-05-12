#ifndef H_AST
#define H_AST

#include <iostream>
#include <string>
#include <vector>

namespace AST
{
    class Id
    {
    public:
        Id();
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
        IntegerLiteralExpression();
        ~IntegerLiteralExpression();
    };

    class FloatLiteralExpression : LiteralExpression
    {
    public:
        FloatLiteralExpression();
        ~FloatLiteralExpression();
    };

    class BoolLiteralExpression : LiteralExpression
    {
    public:
        BoolLiteralExpression();
        ~BoolLiteralExpression();
    };

    class ByteLiteralExpression : LiteralExpression
    {
    public:
        ByteLiteralExpression();
        ~ByteLiteralExpression();
    };

    class StringLiteralExpression : LiteralExpression
    {
    public:
        StringLiteralExpression();
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
        BlockStatement();
        ~BlockStatement();
    };

    class AssignStatement : Statement
    {
    public:
        AssignStatement();
        ~AssignStatement();
    };

    class IfStatement : Statement
    {
    public:
        IfStatement();
        ~IfStatement();
    };

    class LoopStatement : Statement
    {
    public:
        LoopStatement();
        ~LoopStatement();
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
        BinaryOperation();
        ~BinaryOperation();
    };

    class UnaryOperation : Operation
    {
    public:
        UnaryOperation();
        ~UnaryOperation();
    };

    // Declaration
    class Declaration
    {
    public:
        Declaration();
        ~Declaration();
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
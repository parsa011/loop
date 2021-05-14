#ifndef H_AST
#define H_AST
#include "global.h"
#include <string>
#include <vector>

namespace AST
{

    class Id;
    class Expression;
    class LiteralExpression;
    class IntegerLiteralExpression;
    class FloatLiteralExpression;
    class BoolLiteralExpression;
    class ByteLiteralExpression;
    class StringLiteralExpression;
    class Statement;
    class BlockStatement;
    class AssignStatement;
    class IfStatement;
    class LoopStatement;
    class LoopForStatement;
    class LoopWhileStatement;
    class LoopCounterStatement;
    class ReturnStatement;
    class ContinueStatement;
    class BreakStatement;
    class ImportStatement;
    class Operation;
    class BinaryOperation;
    class UnaryOperation;
    class Declaration;
    class IdentifierDeclaration;
    class StructDeclaration;
    class EnumDeclaration;
    class FunctionDeclaration;
    class Call;
    class StructCall;
    class FunctionCall;

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

    class Id
    {
    public:
        Id(std::string id, int size);
        Id(std::string id);
        std::string id;
        int size;
        ~Id() {}
    };

    // Expression
    class Expression
    {
    };

    class LiteralExpression : Expression
    {
    };

    class IntegerLiteralExpression : LiteralExpression
    {
    public:
        IntegerLiteralExpression(int value, int size);
        IntegerLiteralExpression(int value);
        int value;
        int size;
        ~IntegerLiteralExpression() {}
    };

    class FloatLiteralExpression : LiteralExpression
    {
    public:
        FloatLiteralExpression(double value, int size);
        FloatLiteralExpression(double value);
        double value;
        int size;
        ~FloatLiteralExpression() {}
    };

    class BoolLiteralExpression : LiteralExpression
    {
    public:
        BoolLiteralExpression(bool value);
        bool value;
        ~BoolLiteralExpression() {}
    };

    class ByteLiteralExpression : LiteralExpression
    {
    public:
        ByteLiteralExpression(unsigned char value);
        unsigned char value;
        ~ByteLiteralExpression() {}
    };

    class StringLiteralExpression : LiteralExpression
    {
    public:
        StringLiteralExpression(std::string value);
        std::string value;
        ~StringLiteralExpression() {}
    };

    // Statement
    class Statement
    {
    };

    class BlockStatement : Statement
    {
    public:
        BlockStatement(std::vector<Statement *> *statementList, std::vector<IdentifierDeclaration *> *idList);
        std::vector<IdentifierDeclaration *> *idList;
        std::vector<Statement *> *statementList;
        ~BlockStatement() {}
    };

    class AssignStatement : Statement
    {
    public:
        AssignStatement(AssignOperations op, Expression *expr);
        AssignOperations op;
        Expression *expr;
        ~AssignStatement() {}
    };

    class IfStatement : Statement
    {
    public:
        IfStatement(Expression *condition, BlockStatement *ifBlock, BlockStatement *elseBlock);
        Expression *condition;
        BlockStatement *ifBlock;
        BlockStatement *elseBlock;
        ~IfStatement() {}
    };

    class LoopStatement : Statement
    {
    public:
        LoopStatement(BlockStatement *block);
        BlockStatement *block;
        ~LoopStatement() {}
    };

    class LoopForStatement : LoopStatement
    {
    public:
        LoopForStatement(Expression *initCondition, Expression *endCondition, BlockStatement *block, std::string id);
        std::string id;
        Expression *initCondition;
        Expression *endCondition;
        ~LoopForStatement() {}
    };

    class LoopWhileStatement : LoopStatement
    {
    public:
        LoopWhileStatement(Expression *condition, BlockStatement *block);
        Expression *condition;
        ~LoopWhileStatement() {}
    };

    class LoopCounterStatement : LoopStatement
    {
    public:
        LoopCounterStatement(Expression *condition, BlockStatement *block, std::string id);
        std::string id;
        Expression *condition;
        ~LoopCounterStatement() {}
    };

    class ReturnStatement : Statement
    {
    public:
        ReturnStatement(Expression *condition);
        Expression *condition;
        ~ReturnStatement() {}
    };

    class ContinueStatement : Statement
    {
    };

    class BreakStatement : Statement
    {
    };

    class ImportStatement : Statement
    {
    public:
        ImportStatement(Id *id);
        Id *id;
        ~ImportStatement() {}
    };

    // Operation
    class Operation
    {
    };

    class BinaryOperation : Operation
    {
    public:
        BinaryOperation(Expression *left, Expression *right, BinaryOperations op);
        Expression *left;
        Expression *right;
        AST::BinaryOperations op;
        ~BinaryOperation() {}
    };

    class UnaryOperation : Operation
    {
    public:
        UnaryOperation(Expression *expr, UnaryOperations op);
        Expression *expr;
        AST::UnaryOperations op;
        ~UnaryOperation() {}
    };

    // Declaration
    class Declaration
    {
    };

    class IdentifierDeclaration : Declaration
    {
    public:
        IdentifierDeclaration(DataTypes type, std::vector<Id *> *idList);
        DataTypes type;
        std::vector<Id *> *idList;
        ~IdentifierDeclaration() {}
    };

    class StructDeclaration : Declaration
    {
    public:
        StructDeclaration(std::string id, std::vector<Id *> *arguments, std::vector<FunctionDeclaration *> *functions);
        std::string id;
        std::vector<Id *> *arguments;
        std::vector<FunctionDeclaration *> *functions;
        ~StructDeclaration() {}
    };

    class EnumDeclaration : Declaration
    {
    public:
        EnumDeclaration(std::string id, std::vector<Id *> *constants);
        std::string id;
        std::vector<Id *> *constants;
        ~EnumDeclaration() {}
    };

    class FunctionDeclaration : Declaration
    {
    public:
        FunctionDeclaration(std::string id, DataTypes returnType, std::vector<Id *> *arguments, BlockStatement *block);
        std::string id;
        DataTypes returnType;
        std::vector<Id *> *arguments;
        BlockStatement *block;
        ~FunctionDeclaration() {}
    };

    // Call
    class Call
    {
    };

    class StructCall : Call
    {
    public:
        StructCall(std::string id, std::vector<Expression *> *arguments);
        std::string id;
        std::vector<Expression *> *arguments;
        ~StructCall() {}
    };

    class FunctionCall : Call
    {
    public:
        FunctionCall(std::string id, std::vector<Expression *> *arguments);
        std::string id;
        std::vector<Expression *> *arguments;
        ~FunctionCall() {}
    };
}
#endif
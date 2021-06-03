#ifndef H_AST
#define H_AST
#include <string>
#include <vector>

#include "global.hpp"

namespace AST {

struct Id;
struct Expression;
struct LiteralExpression;
struct IntegerLiteralExpression;
struct FloatLiteralExpression;
struct BoolLiteralExpression;
struct ByteLiteralExpression;
struct StringLiteralExpression;
struct Statement;
struct BlockStatement;
struct AssignStatement;
struct IfStatement;
struct LoopStatement;
struct LoopForStatement;
struct LoopWhileStatement;
struct LoopCounterStatement;
struct ReturnStatement;
struct ContinueStatement;
struct BreakStatement;
struct ImportStatement;
struct Operation;
struct BinaryOperation;
struct UnaryOperation;
struct Declaration;
struct IdentifierDeclaration;
struct StructDeclaration;
struct EnumDeclaration;
struct FunctionDeclaration;
struct Call;
struct StructCall;
struct FunctionCall;

enum class DataTypes { I8, I16, I32, I64, U8, U16, U32, U64, F8, F16, F32, F64, BOOL, BYTE, STRING };

enum class AssignOperations { PLUS_EQUAL, MINUS_EQUAL, EQUAL };

enum class BinaryOperations {
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

enum class UnaryOperations { MINUS, NOT };

struct Id {
    Id(std::string id, int size);
    Id(std::string id);
    std::string id;
    int size;
    ~Id() {}
};

// Expression
struct Expression {};

struct LiteralExpression : Expression {};

struct IntegerLiteralExpression : LiteralExpression {
    int value;
    int size;
    IntegerLiteralExpression(int value, int size);
    IntegerLiteralExpression(int value);
    ~IntegerLiteralExpression() {}
};

struct FloatLiteralExpression : LiteralExpression {
    double value;
    int size;
    FloatLiteralExpression(double value, int size);
    FloatLiteralExpression(double value);
    ~FloatLiteralExpression() {}
};

struct BoolLiteralExpression : LiteralExpression {
    bool value;
    BoolLiteralExpression(bool value);
    ~BoolLiteralExpression() {}
};

struct ByteLiteralExpression : LiteralExpression {
    unsigned char value;
    ByteLiteralExpression(unsigned char value);
    ~ByteLiteralExpression() {}
};

struct StringLiteralExpression : LiteralExpression {
    std::string value;
    StringLiteralExpression(std::string value);
    ~StringLiteralExpression() {}
};

// Statement
struct Statement {};

struct BlockStatement : Statement {
    std::vector<IdentifierDeclaration *> *idList;
    std::vector<Statement *> *statementList;
    BlockStatement(std::vector<Statement *> *statementList, std::vector<IdentifierDeclaration *> *idList);
    ~BlockStatement() {}
};

struct AssignStatement : Statement {
    AssignOperations op;
    Expression *expr;
    AssignStatement(AssignOperations op, Expression *expr);
    ~AssignStatement() {}
};

struct IfStatement : Statement {
    Expression *condition;
    BlockStatement *ifBlock;
    BlockStatement *elseBlock;
    IfStatement(Expression *condition, BlockStatement *ifBlock, BlockStatement *elseBlock);
    ~IfStatement() {}
};

struct LoopStatement : Statement {
    BlockStatement *block;
    LoopStatement(BlockStatement *block);
    ~LoopStatement() {}
};

struct LoopForStatement : LoopStatement {
    std::string id;
    Expression *initCondition;
    Expression *endCondition;
    LoopForStatement(Expression *initCondition, Expression *endCondition, BlockStatement *block, std::string id);
    ~LoopForStatement() {}
};

struct LoopWhileStatement : LoopStatement {
    Expression *condition;
    LoopWhileStatement(Expression *condition, BlockStatement *block);
    ~LoopWhileStatement() {}
};

struct LoopCounterStatement : LoopStatement {
    std::string id;
    Expression *condition;
    LoopCounterStatement(Expression *condition, BlockStatement *block, std::string id);
    ~LoopCounterStatement() {}
};

struct ReturnStatement : Statement {
    Expression *condition;
    ReturnStatement(Expression *condition);
    ~ReturnStatement() {}
};

struct ContinueStatement : Statement {};

struct BreakStatement : Statement {};

struct ImportStatement : Statement {
    Id *id;
    ImportStatement(Id *id);
    ~ImportStatement() {}
};

// Operation
struct Operation {};

struct BinaryOperation : Operation {
    Expression *left;
    Expression *right;
    AST::BinaryOperations op;
    BinaryOperation(Expression *left, Expression *right, BinaryOperations op);
    ~BinaryOperation() {}
};

struct UnaryOperation : Operation {
    Expression *expr;
    AST::UnaryOperations op;
    UnaryOperation(Expression *expr, UnaryOperations op);
    ~UnaryOperation() {}
};

// Declaration
struct Declaration {};

struct IdentifierDeclaration : Declaration {
    DataTypes type;
    std::vector<Id *> *idList;
    IdentifierDeclaration(DataTypes type, std::vector<Id *> *idList);
    ~IdentifierDeclaration() {}
};

struct StructDeclaration : Declaration {
    std::string id;
    std::vector<Id *> *arguments;
    std::vector<FunctionDeclaration *> *functions;
    StructDeclaration(std::string id, std::vector<Id *> *arguments, std::vector<FunctionDeclaration *> *functions);
    ~StructDeclaration() {}
};

struct EnumDeclaration : Declaration {
    std::string id;
    std::vector<Id *> *constants;
    EnumDeclaration(std::string id, std::vector<Id *> *constants);
    ~EnumDeclaration() {}
};

struct FunctionDeclaration : Declaration {
    std::string id;
    DataTypes returnType;
    std::vector<Id *> *arguments;
    BlockStatement *block;
    FunctionDeclaration(std::string id, DataTypes returnType, std::vector<Id *> *arguments, BlockStatement *block);
    ~FunctionDeclaration() {}
};

// Call
struct Call {};

struct StructCall : Call {
    std::string id;
    std::vector<Expression *> *arguments;
    StructCall(std::string id, std::vector<Expression *> *arguments);
    ~StructCall() {}
};

struct FunctionCall : Call {
    std::string id;
    std::vector<Expression *> *arguments;
    FunctionCall(std::string id, std::vector<Expression *> *arguments);
    ~FunctionCall() {}
};
}  // namespace AST
#endif

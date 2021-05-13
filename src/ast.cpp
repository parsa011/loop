#include "ast.h"

AST::Id::Id(std::string id, int size)
{
    if (size <= 0)
    {
        werror.compilerError(E_INVALID_IDENTIFIER_SIZE, "Invalid Size, has to be greater than zero");
    }
    auto astId = id;
    auto astSz = size;
    this->id = astId, this->size = astSz;
}

AST::Id::Id(std::string id)
{
    auto astId = id;
    this->id = astId, this->size = 0;
}

AST::IntegerLiteralExpression::IntegerLiteralExpression(int value, int size)
{
    this->value = value;
    this->size = size;
}

AST::IntegerLiteralExpression::IntegerLiteralExpression(int value)
{
    this->value = value;
    this->size = 16;
}

AST::FloatLiteralExpression::FloatLiteralExpression(double value, int size)
{
    this->value = value;
    this->size = size;
}

AST::FloatLiteralExpression::FloatLiteralExpression(double value)
{
    this->value = value;
    this->size = 16;
}

AST::BoolLiteralExpression::BoolLiteralExpression(bool value)
{
    this->value = value;
}

AST::ByteLiteralExpression::ByteLiteralExpression(unsigned char value)
{
    this->value = value;
}

AST::StringLiteralExpression::StringLiteralExpression(std::string value)
{
    this->value = value;
}

AST::BlockStatement::BlockStatement(std::vector<Statement *> *statementList, std::vector<IdentifierDeclaration *> *idList)
{
    this->idList = idList;
    this->statementList = statementList;
}

AST::AssignStatement::AssignStatement(AssignOperations op, Expression *expr)
{
    this->op = op;
    this->expr = expr;
}

AST::IfStatement::IfStatement(Expression *condition, BlockStatement *ifBlock, BlockStatement *elseBlock)
{
    this->condition = condition;
    this->ifBlock = ifBlock;
    this->elseBlock = elseBlock;
}

AST::LoopStatement::LoopStatement(BlockStatement *block)
{
    this->block = block;
}

AST::LoopForStatement::LoopForStatement(Expression *initCondition, Expression *endCondition, BlockStatement *block, std::string id) : LoopStatement(block)
{
    this->id = id;
    this->initCondition = initCondition;
    this->endCondition = endCondition;
}

AST::LoopWhileStatement::LoopWhileStatement(Expression *condition, BlockStatement *block) : LoopStatement(block)
{
    this->condition = condition;
}

AST::LoopCounterStatement::LoopCounterStatement(Expression *condition, BlockStatement *block, std::string id) : LoopStatement(block)
{
    this->id = id;
    this->condition = condition;
}

AST::ReturnStatement::ReturnStatement(Expression *condition)
{
    this->condition = condition;
}

AST::ImportStatement::ImportStatement(Id *id)
{
    this->id = id;
}

AST::BinaryOperation::BinaryOperation(Expression *left, Expression *right, BinaryOperations op)
{
    this->left = left;
    this->right = right;
    this->op = op;
}

AST::UnaryOperation::UnaryOperation(Expression *expr, UnaryOperations op)
{
    this->expr = expr;
    this->op = op;
}

AST::StructDeclaration::StructDeclaration(std::string id, std::vector<Id *> *arguments, std::vector<FunctionDeclaration *> *functions)
{
    this->id = id;
    this->arguments = arguments;
    this->functions = functions;
}

AST::EnumDeclaration::EnumDeclaration(std::string id, std::vector<Id *> *constants)
{
    this->id = id;
    this->constants = constants;
}

AST::FunctionDeclaration::FunctionDeclaration(std::string id, DataTypes returnType, std::vector<Id *> *arguments, BlockStatement *block)
{
    this->id = id;
    this-> returnType = returnType;
    this->arguments = arguments;
    this->block = block;
}
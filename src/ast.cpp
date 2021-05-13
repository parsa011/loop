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
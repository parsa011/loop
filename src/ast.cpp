#include <loop/ast.hpp>

AST::Id::Id(std::string id, int size) {
    if (size <= 0) { werror.compileError(E_INVALID_IDENTIFIER_SIZE, "Invalid Size, has to be greater than zero"); }
    std::string astId = id;
    this->id = astId;
    this->size = size;
}

AST::Id::Id(std::string id) : id{id}, size{0} {}

AST::IntegerLiteralExpression::IntegerLiteralExpression(int value, int size) : value{value}, size{size} {}

AST::IntegerLiteralExpression::IntegerLiteralExpression(int value) : value{value}, size{0} {}

AST::FloatLiteralExpression::FloatLiteralExpression(double value, int size) : value{value}, size{size} {}

AST::FloatLiteralExpression::FloatLiteralExpression(double value) : value{value}, size{16} {}

AST::BoolLiteralExpression::BoolLiteralExpression(bool value) : value{value} {}

AST::ByteLiteralExpression::ByteLiteralExpression(unsigned char value) : value{value} {}

AST::StringLiteralExpression::StringLiteralExpression(std::string value) : value{value} {}

AST::BlockStatement::BlockStatement(std::vector<Statement *> *statementList,
                                    std::vector<IdentifierDeclaration *> *idList)
    : idList{idList}, statementList{statementList} {}

AST::AssignStatement::AssignStatement(AssignOperations op, Expression *expr) : op{op}, expr{expr} {}

AST::IfStatement::IfStatement(Expression *condition, BlockStatement *ifBlock, BlockStatement *elseBlock)
    : condition{condition}, ifBlock{ifBlock}, elseBlock{elseBlock} {}

AST::LoopStatement::LoopStatement(BlockStatement *block) : block{block} {}

AST::LoopForStatement::LoopForStatement(Expression *initCondition, Expression *endCondition, BlockStatement *block,
                                        std::string id)
    : LoopStatement(block), id{id}, initCondition{initCondition}, endCondition{endCondition} {}

AST::LoopWhileStatement::LoopWhileStatement(Expression *condition, BlockStatement *block)
    : LoopStatement(block), condition{condition} {}

AST::LoopCounterStatement::LoopCounterStatement(Expression *condition, BlockStatement *block, std::string id)
    : LoopStatement(block), id{id}, condition{condition} {}

AST::ReturnStatement::ReturnStatement(Expression *condition) : condition{condition} {}

AST::ImportStatement::ImportStatement(Id *id) : id{id} {}

AST::BinaryOperation::BinaryOperation(Expression *left, Expression *right, BinaryOperations op)
    : left{left}, right{right}, op{op} {}

AST::UnaryOperation::UnaryOperation(Expression *expr, UnaryOperations op) : expr{expr}, op{op} {}

AST::StructDeclaration::StructDeclaration(std::string id, std::vector<Id *> *arguments,
                                          std::vector<FunctionDeclaration *> *functions)
    : id{id}, arguments{arguments}, functions{functions} {}

AST::EnumDeclaration::EnumDeclaration(std::string id, std::vector<Id *> *constants) : id{id}, constants{constants} {}

AST::FunctionDeclaration::FunctionDeclaration(std::string id, DataTypes returnType, std::vector<Id *> *arguments,
                                              BlockStatement *block)
    : id{id}, returnType{returnType}, arguments{arguments}, block{block} {}

AST::StructCall::StructCall(std::string id, std::vector<Expression *> *arguments) : id{id}, arguments{arguments} {}

AST::FunctionCall::FunctionCall(std::string id, std::vector<Expression *> *arguments) : id{id}, arguments{arguments} {}

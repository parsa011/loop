#include "ast.h"

AST::Id::Id(std::string id, int size)
{
    if (size <= 0) {
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

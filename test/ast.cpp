#include <loop/test/ast.hpp>
#include <cstring>
#include <iostream>

void AstTest::runAll() {
    test(ThrowInvalidIdentifierSize());
}

bool AstTest::ThrowInvalidIdentifierSize() {
    werror.errors.clear();
    testName = "Throw Invalid Identifier Size Error";
    AST::Id id("Test", -1);
    assert(werror.errors.size() == 1, "test identifire size error size");
    assert(werror.errors[0].code == E_INVALID_IDENTIFIER_SIZE, "test identifire size error kind");
    assert(std::strcmp(werror.errors[0].message, "Invalid Size, has to be greater than zero") == 0, "test identifire size error message");
    return verify();
}


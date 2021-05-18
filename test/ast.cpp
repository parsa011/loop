#include "ast.h"
#include <string.h>
#include <iostream>

void AstTest::runAll()
{
    test(ThrowInvalidIdentifierSize());
}

bool AstTest::ThrowInvalidIdentifierSize()
{
    werror.errors.clear();
    testName = "Throw Invalid Identifier Size Error";
    AST::Id id("Test", -1);
    assert(werror.errors.size() == 1);
    assert(werror.errors[0].code == E_INVALID_IDENTIFIER_SIZE);
    assert(strcmp(werror.errors[0].message, "Invalid Size, has to be greater than zero") == 0);
    return verify();
}


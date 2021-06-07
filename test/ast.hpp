#ifndef AST_TEST_H
#define AST_TEST_H

#include <loop/ast.hpp>
#include <loop/global.hpp>
#include <loop/tokenizer.hpp>

#include "unit_test.hpp"

struct AstTest : UnitTest {
    Tokenizer tokenizer;
    AstTest() {
        runAll();
    }
    void runAll();
    TOKEN getTokenizerToken(const char *token);

    bool tokenizeKeywords();

    bool ThrowInvalidIdentifierSize();
};

#endif

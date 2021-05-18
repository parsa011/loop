#ifndef AST_TEST_H
#define AST_TEST_H

#include "unit_test.h"
#include "../src/global.h"
#include "../src/tokenizer.h"
#include "../src/ast.h"

class AstTest : public UnitTest
{
public:
    Tokenizer tokenizer;
    AstTest()
    {
        runAll();
    }
    void runAll();
    TOKEN getTokenizerToken(const char *token);

    bool tokenizeKeywords();

    bool ThrowInvalidIdentifierSize();
};

#endif
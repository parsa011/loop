#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include "unit_test.h"
#include "../src/error.h"
#include "../src/tokenizer.h"

class TokenizerTest : public UnitTest
{
public:
    Error eh;
    Tokenizer tokenizer{eh};
    TokenizerTest()
    {
        runAll();
    }
    void runAll();
    TOKENS getTokenizerToken(const char *token);
    bool tokenizeKeywords();
    bool tokenizeOperators();
    bool tokenizeDataTypes();
};

#endif
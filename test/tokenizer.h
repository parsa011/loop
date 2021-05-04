#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include "unit_test.h"
#include "../src/error.h"
#include "../src/tokenizer.h"

class TokenizerTest : public UnitTest
{

public:
    TokenizerTest()
    {
        runAll();
    }
    void runAll();
    bool tokenizeKeywords();
    bool tokenizeOperators();
};

#endif
#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include "unit_test.h"

class TokenizerTest : public UnitTest
{

public:
    TokenizerTest() : UnitTest("Tokenizer")
    {
        this->runAll();
        this->result();
    }
    void runAll();

    // Tests
    bool shouldWork();
    bool shouldFail();
};

#endif
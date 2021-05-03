#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include "unit_test.h"

class TokenizerTest : public UnitTest {

    public:
        TokenizerTest() : UnitTest("Tokenizer"){}
        void runAll();
};

#endif
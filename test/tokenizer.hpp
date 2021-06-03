#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include <loop/global.hpp>
#include <loop/tokenizer.hpp>

#include "unit_test.h"

class TokenizerTest : public UnitTest {
   public:
    Tokenizer tokenizer;
    TokenizerTest() {
        runAll();
    }
    void runAll();
    TOKEN getTokenizerToken(const char *token);

    bool tokenizeKeywords();
    bool tokenizeOperators();
    bool tokenizeDataTypes();

    bool ThrowCloseCommentError();
    bool ThrowMissingQuotationMarkError();
    bool ThrowOutOfRangeHexError();
    bool ThrowInvalidHexError();
    bool ThrowInvalidHexAndOutOfRangeHexError();
    bool ThrowOutOfRangeBinaryError();
    bool ThrowInvalidBinaryError();
    bool ThrowInvalidUnicodeError();
    bool ThrowInvalidNumberError();
    bool ThrowUnrecognizedTokenError();
};

#endif

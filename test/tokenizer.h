#ifndef TOKENIZER_TEST_H
#define TOKENIZER_TEST_H

#include "unit_test.h"
#include "../src/werror.h"
#include "../src/tokenizer.h"

class TokenizerTest : public UnitTest
{
public:
    WError eh;
    Tokenizer tokenizer{eh};
    TokenizerTest()
    {
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
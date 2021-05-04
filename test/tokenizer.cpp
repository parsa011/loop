#include "tokenizer.h"
Error errorHandler;

void TokenizerTest::runAll()
{
    test(tokenizeKeywords());
    test(tokenizeOperators());
}

bool TokenizerTest::tokenizeKeywords()
{
    testName = "Tokenize Keywords";
    Tokenizer tokenizer("if", errorHandler);
    assert(tokenizer.lastToken.kind == T_IF);
    return verify();
}

bool TokenizerTest::tokenizeOperators()
{
    testName = "Tokenize Operators";
    Tokenizer tokenizer("+", errorHandler);
    assert(tokenizer.lastToken.kind == T_PLUS);
    return verify();
}
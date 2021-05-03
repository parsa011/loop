#include "tokenizer.h"
#include "../src/tokenizer.h"
#include "../src/error.h"
Error errorHandler;

void TokenizerTest::runAll()
{
    test(shouldTokenizeKeywords());
}

bool TokenizerTest::shouldTokenizeKeywords(){
    Tokenizer tokenizer("if", errorHandler);
    assert(tokenizer.lastToken.kind == T_IF);
    return verify();
}
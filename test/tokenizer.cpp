#include "tokenizer.h"

void TokenizerTest::runAll()
{
    test(shouldWork());
    test(shouldFail());
}

bool TokenizerTest::shouldFail(){
    assert(1 == 1);
    assert(1 == 1);
    assert(1 == 2);
    return verify();
}

bool TokenizerTest::shouldWork(){
    assert(1 == 1);
    assert(1 == 1);
    assert(1 == 1);
    return verify();
}
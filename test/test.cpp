#include <iostream>
#include "../src/global.h"
#include "tokenizer.h"

WError werror;
int main()
{
    TokenizerTest tokenizerTest;
    int totalPassed = tokenizerTest.totalPassed;
    int totalFailed = tokenizerTest.totalFailed;
    std::cout << "\x1b[0mTotally \x1b[93;1m"
              << totalFailed + totalPassed << "\x1b[0m Tests Done. \x1b[92;1m"
              << totalPassed << " Passed\x1b[0m and \x1b[91;1m" 
              << totalFailed << " Failed" << std::endl;
    if (totalFailed)
        exit(1);
    return 0;
}
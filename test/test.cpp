#include <iostream>
#include "tokenizer.h"

int main()
{
    std::cout << "\x1b[0;1m-----------------------" << std::endl;
    TokenizerTest tokenizerTest;
    int totalPassed = tokenizerTest.totalPassed;
    int totalFailed = tokenizerTest.totalFailed;
    std::cout << "Totally \x1b[93;1m" << totalFailed + totalPassed << "\x1b[0m Tests Done. \x1b[92;1m" << totalPassed << " Passed\x1b[0m and \x1b[91;1m" << totalFailed << " Failed" << std::endl;
    return 0;
}
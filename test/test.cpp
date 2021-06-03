#include </src/console.hpp>
#include <iostream>
#include <loop/global.hpp>

#include "ast.h"
#include "tokenizer.h"

WError werror;
int main() {
    int totalPassed = 0;
    int totalFailed = 0;

    TokenizerTest tokenizerTest;
    totalPassed += tokenizerTest.totalPassed;
    totalFailed += tokenizerTest.totalFailed;

    AstTest astTest;
    totalPassed += astTest.totalPassed;
    totalFailed += astTest.totalFailed;

    out << "\x1b[0mTotally \x1b[93;1m" << totalFailed + totalPassed << "\x1b[0m Tests Done. \x1b[92;1m" << totalPassed
        << " Passed\x1b[0m and \x1b[91;1m" << totalFailed << " Failed\n";
    if (totalFailed) exit(1);
    return 0;
}

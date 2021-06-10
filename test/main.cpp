#include <iostream>
#include <loop/global.hpp>
#include <loop/test/ast.hpp>
#include <loop/test/lexer.hpp>

WError werror;
int main()
{
    int totalPassedTests = 0;
    int totalfailedTests = 0;

    LexerTest lexerTest;
    totalPassedTests += lexerTest.passedTests;
    totalfailedTests += lexerTest.failedTests;

    AstTest astTest;
    totalPassedTests += astTest.passedTests;
    totalfailedTests += astTest.failedTests;

    std::cout << "\x1b[0mTotally \x1b[93;1m" << totalfailedTests + totalPassedTests << "\x1b[0m Tests Done. \x1b[92;1m" << totalPassedTests
        << " Passed\x1b[0m and \x1b[91;1m" << totalfailedTests << " Failed\n";
    if (totalfailedTests)
        exit(1);
    return 0;
}

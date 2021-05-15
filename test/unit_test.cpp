#include "../src/console.h"
#include "unit_test.h"
#include <iostream>

void UnitTest::test(bool passed)
{
    totalPassed += passedTests;
    totalFailed += failedTests;
    const char *lineColor = "\x1b[0;92m";
    if (!passed)
        lineColor = "\x1b[0;91m";

    out << lineColor
        << "┌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┐\n"
        << "  "
        << "\x1b[0;1m" << testName << '\n'
        << "  "
        << "\x1b[0;92mPassed:\x1b[0m " << passedTests
        << "\x1b[0;91m Failed:\x1b[0m " << failedTests << '\n'
        << lineColor
        << "└╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┘\n";
    passedTests = 0;
    failedTests = 0;
}

void UnitTest::assert(bool passed)
{
    if (passed)
    {
        passedTests++;
    }
    else
    {
        failedTests++;
    }
}

bool UnitTest::verify()
{
    bool result = failedTests == 0;
    return result;
}
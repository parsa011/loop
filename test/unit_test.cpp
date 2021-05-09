#include "unit_test.h"
#include <sstream>

void UnitTest::test(bool passed)
{
    totalPassed += passedTests;
    totalFailed += failedTests;
    const char *lineColor = "\x1b[0;92m";
    if (!passed)
        lineColor = "\x1b[0;91m";

    std::cout
        << lineColor
        << "┌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┐" << std::endl
        << "  "
        << "\x1b[0;1m" << testName << std::endl
        << "  "
        << "\x1b[0;92mPassed:\x1b[0m " << passedTests
        << "\x1b[0;91m Failed:\x1b[0m " << failedTests << std::endl
        << lineColor
        << "└╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┘" << std::endl;
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
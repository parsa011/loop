#include "unit_test.h"

void UnitTest::test(bool passed)
{
    totalPassed += passedTests;
    totalFailed += failedTests;
    std::cout << "\x1b[93;1m" << testName << std::endl;
    std::cout << "\x1b[92;1mPassed:\x1b[0;1m " << passedTests << "\x1b[91;1m Failed:\x1b[0;1m " << failedTests << std::endl;
    std::cout << "-----------------------" << std::endl;
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
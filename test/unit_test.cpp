#include "unit_test.h"

void UnitTest::test(bool Passed)
{
    if (Passed)
    {
        totalPassed += PassedTests;
    }
    else
    {
        totalFailed += failedTests;
    }
    std::cout << "\x1b[92;1mPassed:\x1b[0;1m " << PassedTests << "\x1b[91;1m Failed:\x1b[0;1m " << failedTests << std::endl;
    std::cout << "-----------------------" << std::endl;
    PassedTests = 0;
    failedTests = 0;
}

void UnitTest::assert(bool Passed)
{
    if (!Passed)
    {
        failedTests++;
    }
    else
    {
        PassedTests++;
    }
}

bool UnitTest::verify()
{
    bool result = failedTests == 0;
    failedTests = 0;
    return result;
}
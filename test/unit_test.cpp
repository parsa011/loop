#include "unit_test.h"

void UnitTest::test(bool success)
{
    if (success)
    {
        totalSuccess += successTests;
    }
    else
    {
        totalFailed += failedTests;
    }
    std::cout << "--------------------------------------------------\n";
    std::cout << "Name: " << testName << "\n";
    std::cout << "Successful: " << successTests << "\n";
    std::cout << "Failed: " << failedTests << "\n";
    std::cout << "--------------------------------------------------\n\n";
    successTests = 0;
    failedTests = 0;
}

void UnitTest::assert(bool success)
{
    if (!success)
    {
        failedTests++;
    }
    else {
        successTests++;
    }
}

bool UnitTest::verify()
{
    bool result = failedTests == 0;
    failedTests = 0;
    return result;
}

void UnitTest::result()
{
    std::cout << "--------------------------------------------------\n";
    std::cout << "Successful: " << totalSuccess << "\n";
    std::cout << "Failed: " << totalFailed << "\n";
    std::cout << "--------------------------------------------------\n\n";
}
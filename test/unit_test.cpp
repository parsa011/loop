#include "unit_test.h"

void UnitTest::test(bool success)
{
    if (success)
    {
        ++this->successfulTests;
    }
    else
    {
        ++this->failedTests;
    }
}
void UnitTest::assert(bool success)
{
    if (!success)
    {
        ++this->currentRunErrors;
    }
}

bool UnitTest::verify()
{
    bool result = this->currentRunErrors == 0;
    this->currentRunErrors = 0;
    return result;
}

void UnitTest::result() const
{
    std::cout << "--------------------------------------------------\n";
    std::cout << this->testName << "\n";
    std::cout << "Successful: " << this->successfulTests << "\n";
    std::cout << "Failed: " << this->failedTests << "\n";
    std::cout << "--------------------------------------------------\n\n";
}
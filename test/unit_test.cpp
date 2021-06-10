#include <loop/test/unit_test.hpp>
#include <iostream>

void UnitTest::test(bool passed)
{
    passedTests += currentTestCount - currentFaileds.size();
    failedTests += currentFaileds.size();
    const char *lineColor = "\x1b[0;92m";
    if (!passed)
        lineColor = "\x1b[0;91m";

    std::cout
        << lineColor << "┌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┐" << std::endl
        << "  "
        << "\x1b[0;1m" << testName << std::endl
        << "  \x1b[0;92mPassed:\x1b[0m " << currentTestCount - currentFaileds.size() << "\x1b[0;91m Failed:\x1b[0m " << currentFaileds.size() << std::endl;
    for (const char *name : currentFaileds)
    {
        std::cout << ' ' << name << std::endl;
    }
    std::cout
        << lineColor << "└╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┘" << std::endl;
    currentTestCount = 0;
    currentFaileds.clear();
}

void UnitTest::assert(bool passed, const char *name)
{
    if (!passed)
    {
        currentFaileds.push_back(name);
    }
    currentTestCount++;
}

bool UnitTest::verify()
{
    bool result = currentFaileds.size() == 0;
    return result;
}

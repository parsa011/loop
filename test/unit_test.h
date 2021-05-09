#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>
#include <sstream>
#include "../src/utils.h"

class UnitTest
{
private:
    int failedTests = 0;
    int passedTests = 0;

public:
    const char *testName;
    int totalPassed = 0;
    int totalFailed = 0;
    void assert(bool passed);
    bool verify();
    void test(bool passed);
    virtual void runAll() = 0;
};

#endif
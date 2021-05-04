#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>

class UnitTest
{
private:
    int failedTests = 0;
    int PassedTests = 0;

public:
    const char *testName;
    int totalPassed = 0;
    int totalFailed = 0;
    void assert(bool Passed);
    bool verify();
    void test(bool Passed);
    virtual void runAll() = 0;
};

#endif
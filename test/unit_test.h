#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>

class UnitTest
{
private:
    int failedTests = 0;
    int successTests = 0;
    int totalSuccess = 0;
    int totalFailed = 0;

public:
    const char *testName;
    UnitTest(const char *testName) : testName(testName) {}
    void assert(bool success);
    bool verify();
    void test(bool success);
    void result();
    virtual void runAll() = 0;
};

#endif
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>

class UnitTest
{
private:
    const char *testName = "";
    int failedTests = 0;
    int successfulTests = 0;

public:
    UnitTest(const char *testName) { this->testName = testName; }
    void assert(bool success);
    virtual void runAll() = 0;
    void result() const;
};

#endif
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>

class UnitTest{
    private:
        const char* testName = "";
        int failedTests = 0;
        int successfulTests = 0;
    public:
        UnitTest(const char* testName){ this->testName = testName; }
        template <typename T>
        void assertThat(T a, T b);
        void assert(bool success);
        void runAll();
        void result() const;
};

#endif
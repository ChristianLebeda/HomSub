#ifndef TEST_RUNNER_h
#define TEST_RUNNER_h

#include "test/test.h"
class TestRunner
{
public:
    static void RunTestFromMask(int mask);
    static void RunTest(int testNum);
    static void RunTest(Test test);
};

#endif /* test_runner_h */

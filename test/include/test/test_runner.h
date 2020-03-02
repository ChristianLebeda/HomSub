#ifndef TEST_RUNNER_h
#define TEST_RUNNER_h

#include "test/test.h"
#include "test/test_settings.h"
class TestRunner
{
public:
    TestRunner(TestSettings ts) : settings_(ts) {};
    void Run();
    static void PrintHelp();
    static void PrintTests();
private:
    TestSettings settings_;
    static void RunTestFromMask(int mask);
    static void RunTest(int testNum);
    static void RunTest(Test test);
    
};

#endif /* test_runner_h */

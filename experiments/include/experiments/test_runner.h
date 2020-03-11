#ifndef TEST_RUNNER_h
#define TEST_RUNNER_h

#include "experiments/test_settings.h"
#include "experiments/test-logger.h"
class TestRunner
{
public:
    TestRunner(TestSettings ts, TestLogger& tl) : settings_(ts), logger_(tl) {};
    void Run();
    static void PrintHelp();
private:
    TestSettings settings_;
    TestLogger& logger_;
    void RunTestFromMask(int mask);
    void RunTest(int testNum);
};

#endif /* test_runner_h */

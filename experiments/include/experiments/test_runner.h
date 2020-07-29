#ifndef EXPERIMENTS_TEST_RUNNER_H
#define EXPERIMENTS_TEST_RUNNER_H

#include <vector>

#include "experiments/test_settings.h"
#include "experiments/test_logger.h"

class TestRunner {
 public:
    TestRunner(TestSettings ts, TestLogger& tl) : settings_(ts), logger_(tl) {}
    void Run();
    static void PrintHelp();
 private:
    TestSettings settings_;
    TestLogger& logger_;
    void RunTestFromMask(int mask);
    void RunTest(int testNum);
    void RunTestFromList(const std::vector<std::function<void(TestSettings&, TestLogger&)>>& tests);
};

#endif /* test_runner_h */

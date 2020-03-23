#include <iostream>
#include "experiments/test_runner.h"
#include "experiments/test_factory.h"
#include <chrono>
#include "experiments/sanity_test_factory.h"


void TestRunner::Run() {
    logger_.NotifyRunStart();

    if(settings_.GetRunSanity()) {
        SanityTestFactory::runAllTests(settings_, logger_);
        logger_.NotifyFailed();
    }

    if(settings_.GetRunPerformance()) {
        srand(settings_.GetRandomSeed());
        if (settings_.ShouldRunSingleTest()) {
            RunTest(settings_.GetSingleTest());
        }

        if (settings_.GetRunAll()) {
            RunTestFromList(TestFactory::GetAllTests());
        }
    }
}

void TestRunner::RunTestFromMask(int mask)
{
    for(int i = 0; i < 32; i++) {
        if((1 << i) & mask) {
            RunTest(i);
        }
    }
}

void TestRunner::RunTest(int testNum)
{
    std::function<void(TestSettings&, TestLogger&)> t = TestFactory::GetTest(testNum);
    if(t) {
        t(settings_, logger_);
    }
}

void TestRunner::RunTestFromList(const std::vector<std::function<void (TestSettings &, TestLogger &)>>& tests) {
    for(auto t : tests) {
        t(settings_, logger_);
    }
}

void TestRunner::PrintHelp()
{
    std::cout
        << "Give the program a sequence of parameters in order to adjust execution. Supported parameters are described here:\n" << std::endl
        << "-help     | Get this help screen" << std::endl
        //<< "-list     | List all tests" << std::endl
        << "-test t   | Run a specific test based on its number" << std::endl
        << "-group g  | Runs a test group: correctness (c), performance (p) or all (a)" << std::endl
        << "            Performance group is default" << std::endl
        << "-csv      | Output test results formatted as csv" << std::endl
        << "-seed     | Specify the seed used by the random graphs" << std::endl
        << "-time     | Set the timout limit for incremental tests" << std::endl
        //<< "-mask m   | Run several tests masked by given signed integer (-1 runs all)" << std::endl
        //<< "-run h g | Count occurences of pattern h in host g" << std::endl
        << std::endl;
}

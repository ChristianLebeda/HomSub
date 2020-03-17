#include <iostream>
#include "experiments/test_runner.h"
#include "experiments/test_factory.h"
#include <chrono>


void TestRunner::Run() {
    logger_.NotifyRunStart();
    
    srand(settings_.GetRandomSeed());
    if(settings_.ShouldRunSingleTest()) {
        RunTest(settings_.GetSingleTest());
    }
    
    if(settings_.GetRunAll()) {
        RunTestFromList(TestFactory::GetAllTests());
    }

    logger_.NotifyFailed();
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

void TestRunner::RunTestFromList(std::vector<std::function<void (TestSettings &, TestLogger &)> > tests) {
    for(int i = 0 ; i < tests.size(); i++) {
        std::function<void(TestSettings&, TestLogger&)> t = tests[i];
        t(settings_, logger_);
    }
}

void TestRunner::PrintHelp()
{
    std::cout << "Give the program a sequence of parameters in order to adjust execution. Supported parameters are described here:\n" << std::endl;
    std::cout << "-help     | Get this help screen" << std::endl;
    //std::cout << "-list     | List all tests" << std::endl;
    std::cout << "-test t   | Run a specific test" << std::endl;
    std::cout << "-group g  | Runs a test group: correctness (c), performance (p) or all (a)" << std::endl;
    std::cout << "-csv      | Test results formatted as csv" << std::endl;
    std::cout << "-seed     | Specify the seed used by the random graphs";
    //std::cout << "-mask m   | Run several tests masked by given signed integer (-1 runs all)" << std::endl;
    //std::cout << "-run h g | Count occurences of pattern h in host g" << std::endl;
    
    std::cout << std::endl;
}

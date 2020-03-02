//
//  test_runner.cpp
//  test
//
//  Created by Jonas Mortensen on 26/02/2020.
//

#include <iostream>
#include "test/test_runner.h"
#include "test/test_factory.h"
#include "test/test.h"
#include <chrono>


void TestRunner::Run() {
    srand(settings_.GetRandomSeed());
    if(settings_.ShouldRunSingleTest()) {
        RunTest(settings_.GetSingleTest());
    }
    
    if(settings_.ShouldRunTestMask()) {
        RunTestFromMask(settings_.GetTestMask());
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

void TestRunner::RunTest(Test test)
{
    std::cout << test.GetName() << ":\t";
    
    auto start = std::chrono::high_resolution_clock::now();
    test.Run();
    auto stop = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    
    std::cout << duration.count() << "ms" << std::endl;
}

void TestRunner::RunTest(int testNum)
{
    std::unique_ptr<Test> t = TestFactory::GetTest(testNum);
    if(t) {
        RunTest(*t);
    }
}

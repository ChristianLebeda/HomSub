//
//  test_factory.h
//  test
//
//  Created by Jonas Mortensen on 26/02/2020.
//

#ifndef TEST_FACTORY_h
#define TEST_FACTORY_h
#include "experiments/test_settings.h"
#include "experiments/test-logger.h"

#include <chrono>
#include <functional>
#include <memory>

class TestFactory
{
public:
    static std::function<void(TestSettings&, TestLogger&)> GetTest(int i);
    static int TestCount();
private:
    static void Test1(TestSettings& settings, TestLogger& logger);
    static void Test2(TestSettings& settings, TestLogger& logger);
    static int microSecondDifferene(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> stop);
};

#endif /* test_factory_h */

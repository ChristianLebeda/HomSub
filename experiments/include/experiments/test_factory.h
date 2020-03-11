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
    static void Test3(TestSettings& settings, TestLogger& logger);
    static void Test4(TestSettings& settings, TestLogger& logger);
    static void Test5(TestSettings& settings, TestLogger& logger);
    static int milliSecondDifferene(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> stop);
};

#endif /* test_factory_h */

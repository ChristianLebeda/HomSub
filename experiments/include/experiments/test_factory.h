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
    static std::vector<std::function<void(TestSettings&, TestLogger&)>> GetAllTests();
private:
    static void SquaresInGrid(TestSettings& settings, TestLogger& logger);
    static void BinaryTreeInBinaryTree(TestSettings& settings, TestLogger& logger);
    static void CliquesInClique(TestSettings& settings, TestLogger& logger);
    static void EdgesInPath(TestSettings& settings, TestLogger& logger);
    static void PathInRandomGraph(TestSettings& settings, TestLogger& logger);
    static void RandomPatternsInRandomGraph(TestSettings& settings, TestLogger& logger);
    static void ForgetLeastSignificant(TestSettings& settings, TestLogger& logger);
    //static void ForgetMostSignificant(TestSettings& settings, TestLogger& logger);
    static void joinHandler(TestSettings& settings, TestLogger& logger);
    static void InsertClosedForm(TestSettings& settings, TestLogger& logger);
    static void ExtractClosedForm(TestSettings& settings, TestLogger& logger);
    static void InsertIterator(TestSettings& settings, TestLogger& logger);
    static void ExtractIterator(TestSettings& settings, TestLogger& logger);
    static int milliSecondDifferene(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> stop);
    static void fillVector(std::vector<size_t> data);
};

#endif /* test_factory_h */

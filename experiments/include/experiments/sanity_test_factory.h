#ifndef EXPERIMENTS_SANITY_TEST_FACTORY_H
#define EXPERIMENTS_SANITY_TEST_FACTORY_H

#include <functional>

#include "homomorphism/homomorphism_counter.h"
#include "experiments/test_logger.h"
#include "experiments/test_settings.h"
#include "homomorphism/remapper.h"

#define TESTCASES \
    SQUARE_PATTERN, REMAPPER_CALCULATION, REMAPPER_ITERATOR, \
    FORGET_HANDLER, INTRODUCE_HANDLER_CONSISTENCY, INTRODUCE_HANDLER_COMPLETE, \
    HOMOMORPHISM_LOOP_DEFAULT, HOMOMORPHISM_HANDCRAFTED_DEFAULT, \
    HOMOMORPHISM_LOOP_ITERATOR, HOMOMORPHISM_HANDCRAFTED_ITERATOR

#define COMPOSITETESTCASES \
    HOMOMORPHISM_COUNTER_DEFAULT, HOMOMORPHISM_COUNTER_ITERATOR, \
    INTRODUCE_HANDLER_TEST, ALL_TESTS

enum TestCase { TESTCASES, COMPOSITETESTCASES };

class SanityTestFactory {
public:
    static std::function<void(TestSettings&, TestLogger&)> getTest(TestCase t);
    static std::vector<TestCase> allTests();
    static void runAllTests(TestSettings& settings, TestLogger& logger);
private:
    static void squarePatternTest(TestSettings& settings, TestLogger& logger);
    static void calculationRemapperTest(TestSettings& settings, TestLogger& logger);
    static void iteratorRemapperTest(TestSettings& settings, TestLogger& logger);
    static void remapperTest(TestSettings& settings, TestLogger& logger, Remapper& mapper, std::string name);
    static void forgetLastTest(TestSettings& settings, TestLogger& logger);
    static void prepareForgetTest(std::vector<size_t>& input, std::vector<size_t>& expected,
                    std::vector<size_t>& result, size_t n, size_t b);
    static void introduceLastTest(TestSettings& settings, TestLogger& logger);
    static void introduceLastEdgeConsistencyTest(TestSettings& settings, TestLogger& logger);
    static void introduceLastCompleteTest(TestSettings& settings, TestLogger& logger);
    static void prepareIntroduceCompleteTest(std::vector<size_t>& input, std::vector<size_t>& expected,
                                             std::vector<size_t>& result, std::vector<size_t>& bag,
                                             size_t n, size_t b);
    static void defaultHomomorphismTest(TestSettings& settings, TestLogger& logger);
    static void iteratorHomomorphismTest(TestSettings& settings, TestLogger& logger);
    static void homomorphismTest(TestSettings& settings, TestLogger& logger,
                    HomomorphismSettings hom, const std::string& settingsName);
    static void defaultHomomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger);
    static void defaultHomomorphismLoopTest(TestSettings& settings, TestLogger& logger);
    static void iteratorHomomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger);
    static void iteratorHomomorphismLoopTest(TestSettings& settings, TestLogger& logger);
    static void homomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger,
                    HomomorphismSettings hom, const std::string& settingsName);
    static void homomorphismLoopTest(TestSettings& settings, TestLogger& logger,
                    HomomorphismSettings hom, const std::string& settingsName);
};

#endif

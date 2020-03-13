#ifndef EXPERIMENTS_SANITY_TEST_FACTORY_H
#define EXPERIMENTS_THESIS_SANITY_TEST_FACTORY_H

#include <functional>

#include "homomorphism/homomorphism_counter.h"
#include "experiments/test-logger.h"
#include "experiments/test_settings.h"
#include "homomorphism/remapper.h"

enum TestCase {SQUARE_PATTERN, REMAPPER_CALCULATION, REMAPPER_ITERATOR, FORGET_HANDLER,
            INTRODUCE_HANDLER_COMPLETE, HOMOMORPHISM_COUNTER_DEFAULT};

class SanityTestFactory {
public:
    static std::function<void(TestSettings&, TestLogger&)> getTest(TestCase t);
    static std::vector<std::function<void(TestSettings&, TestLogger&)>> allTests();
private:
    static void squarePatternTest(TestSettings& settings, TestLogger& logger);
    static void calculationRemapperTest(TestSettings& settings, TestLogger& logger);
    static void iteratorRemapperTest(TestSettings& settings, TestLogger& logger);
    static void remapperTest(TestSettings& settings, TestLogger& logger, Remapper& mapper);
    static void forgetLastTest(TestSettings& settings, TestLogger& logger);
    static void prepareForgetTest(std::vector<size_t>& input, std::vector<size_t>& expected,
                    std::vector<size_t>& result, size_t n, size_t b);
    static void introduceLastCompleteTest(TestSettings& settings, TestLogger& logger);
    static void prepareIntroduceCompleteTest(std::vector<size_t>& input, std::vector<size_t>& expected,
                                             std::vector<size_t>& result, std::vector<size_t>& bag,
                                             size_t n, size_t b);
    static void defaultHomomorphismTest(TestSettings& settings, TestLogger& logger);
    static void homomorphismTest(TestSettings& settings, TestLogger& logger, HomomorphismSettings hom);
    static void homomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger, HomomorphismSettings hom);
    static void homomorphismLoopTest(TestSettings& settings, TestLogger& logger, HomomorphismSettings hom);
};

#endif

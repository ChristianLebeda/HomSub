#ifndef EXPERIMENTS_SANITY_TEST_FACTORY_H
#define EXPERIMENTS_THESIS_SANITY_TEST_FACTORY_H

#include <functional>

#include "experiments/test-logger.h"
#include "experiments/test_settings.h"
#include "homomorphism/remapper.h"

enum TestCase {SQUARE_PATTERN, REMAPPER_CALCULATION, REMAPPER_ITERATOR};

class SanityTestFactory {
public:
    static std::function<void(TestSettings, TestLogger)> getTest(TestCase t);
    static std::vector<std::function<void(TestSettings, TestLogger)>> allTests();
private:
    static void squarePatternTest(TestSettings settings, TestLogger logger);
    static void calculationRemapperTest(TestSettings settings, TestLogger logger);
    static void iteratorRemapperTest(TestSettings settings, TestLogger logger);
    static void remapperTest(TestSettings settings, TestLogger logger, Remapper& mapper);
};

#endif

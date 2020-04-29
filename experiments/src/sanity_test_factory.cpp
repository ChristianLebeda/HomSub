#include "experiments/sanity_test_factory.h"

#include "experiments/graph_generator.h"
#include "homomorphism/forget_handler_last.h"
#include "homomorphism/forget_handler_first.h"
#include "homomorphism/forget_handler_any.h"
#include "homomorphism/introduce_handler_compute.h"
#include "homomorphism/introduce_handler_least_precomputed.h"
#include "homomorphism/iterator_introduce_handler.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/iterator_remapper.h"
#include "homomorphism/main.h"
#include "homomorphism/configuration_factory.h"
#include "homomorphism/tamaki_runner.h"
#include "homomorphism/traversal_homomorphism_counter.h"

#define BEGIN_TEST(name, type) logger.NotifyTestStart(name);type exp;

#define END_TEST logger.NotifyTestEnd(0);

#define ASSERT_START(expected) exp = expected;

#define ASSERT_END(note, result) logger.NotifyTestAssert(note,exp == result);

#define BEGIN_LOOP_TEST(name, type) BEGIN_TEST(name, type) bool allPassed;

#define LOOP_START allPassed = true;

#define LOOP_ASSERT_START(expected) if(!allPassed) continue; ASSERT_START(expected)

#define LOOP_ASSERT_END(note, result) if(exp != result) { logger.NotifyTestAssert(note,exp == result); allPassed = false; }

#define LOOP_END(note) logger.NotifyTestAssert(note, allPassed)

std::function<void(TestSettings&, TestLogger&)> SanityTestFactory::getTest(TestCase t) {
    switch (t) {
        case SQUARE_PATTERN:
            return squarePatternTest;
        case REMAPPER_CALCULATION:
            return calculationRemapperTest;
        case REMAPPER_ITERATOR:
            return iteratorRemapperTest;
        case FORGET_HANDLER_LAST:
            return forgetLastTest;
        case FORGET_HANDLER_FIRST:
            return forgetFirstTest;
        case FORGET_HANDLER_ANY:
            return forgetAnyTest;
        case INTRODUCE_HANDLER_COMPUTE:
            return introduceLastComputeTest;
        case INTRODUCE_HANDLER_ITERATOR:
            return introduceLastIteratorTest;
        case INTRODUCE_HANDLER_PRECOMPUTED:
            return introduceLastPrecomputedTest;
        case HOMOMORPHISM_HANDCRAFTED_DEFAULT:
            return defaultHomomorphismHandcraftedTest;
        case HOMOMORPHISM_LOOP_DEFAULT:
            return defaultHomomorphismLoopTest;
        case HOMOMORPHISM_HANDCRAFTED_ITERATOR:
            return iteratorHomomorphismHandcraftedTest;
        case HOMOMORPHISM_LOOP_ITERATOR:
            return iteratorHomomorphismLoopTest;
        case HOMOMORPHISM_HANDCRAFTED_PRECOMPUTED:
            return HomomorphismPrecomputedHandcraftedTest;
        case HOMOMORPHISM_LOOP_PRECOMPUTED:
            return HomomorphismPrecomputedLoopTest;
        case HOMOMORPHISM_COUNTER_DEFAULT:
            return defaultHomomorphismTest;
        case HOMOMORPHISM_COUNTER_ITERATOR:
            return iteratorHomomorphismTest;
        case PATHDECOMPCOUNTER_DEFAULT:
            return DefaultPathdecompHomomorphismTest;
        case MAX_DEGREE_TEST:
            return maxDegreeTest;
        case ALL_TESTS:
            return runAllTests;
        default:
            return nullptr;
    }
}

std::vector<TestCase> SanityTestFactory::allTests() {
    return std::vector<TestCase> { TESTCASES };
}

void SanityTestFactory::runAllTests(TestSettings &settings, TestLogger &logger) {
    for(auto& tc : allTests()) {
        auto next = getTest(tc);
        next(settings, logger);
    }
}

void SanityTestFactory::squarePatternTest(TestSettings& settings, TestLogger& logger) {
    BEGIN_TEST("SquareSanity", long);
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();

    GraphGenerator::CompleteGrid(h, 2, 2);
    GraphGenerator::CompleteGrid(g, 2, 2);
    ASSERT_START(1);
    long result = Main::subgraphsGraph(h, g);
    ASSERT_END("InSquare", result)

    GraphGenerator::CompleteGrid(g, 3, 3);
    ASSERT_START(4);
    result = Main::subgraphsGraph(h, g);
    ASSERT_END("In3x3", result)

    GraphGenerator::CompleteGrid(g, 4, 3);
    ASSERT_START(6);
    result = Main::subgraphsGraph(h, g);
    ASSERT_END("In4x3", result)
    END_TEST;
}

void SanityTestFactory::calculationRemapperTest(TestSettings& settings, TestLogger& logger) {
    CalculationRemapper mapper;
    remapperTest(settings, logger, mapper, "CalculationRemapperSanity");
}

void SanityTestFactory::iteratorRemapperTest(TestSettings& settings, TestLogger& logger) {
    IteratorRemapper mapper;
    remapperTest(settings, logger, mapper, "IteratorRemapperSanity");
}

void SanityTestFactory::remapperTest(TestSettings& settings, TestLogger& logger, Remapper& mapper, std::string name) {
    BEGIN_TEST(name, std::vector<size_t>);
    std::vector<size_t> input(8), result(8), expected;

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i;
    }

    mapper.SetSizes(2, 3);

    expected = std::vector<size_t> {0, 1, 2, 3, 4, 5, 6, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 0);
    ASSERT_END("ExtractLeast", result)

    expected = std::vector<size_t> {0, 2, 1, 3, 4, 6, 5, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 1);
    ASSERT_END("ExtractMiddle", result)

    expected = std::vector<size_t> {0, 4, 1, 5, 2, 6, 3, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 2);
    ASSERT_END("ExtractMost", result)

    expected = std::vector<size_t> {0, 1, 2, 3, 4, 5, 6, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 0);
    ASSERT_END("InsertLeast", result)

    expected = std::vector<size_t> {0, 2, 1, 3, 4, 6, 5, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 1);
    ASSERT_END("InsertMiddle", result)

    expected = std::vector<size_t> {0, 2, 4, 6, 1, 3, 5, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 2);
    ASSERT_END("insertMost", result)

    END_TEST;
}

void SanityTestFactory::forgetLastTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("ForgetHandlerLastSanity", std::vector<size_t>);

    std::vector<size_t> input, expected, result;

    LOOP_START

    for(size_t n = 1; n < 10; n++) {
        ForgetHandlerLast handler(n, 5);
        for(size_t b = 1; b < 5; b++) {
            prepareForgetTest(input, expected, result, n, b, true);
            LOOP_ASSERT_START(expected)
            result = handler.forget(input, result, b, 0);
            std::stringstream str;
            str << "ForgetHandlerN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }

    LOOP_END("ForgetLastVaryingSizes");

    END_TEST;
}


void SanityTestFactory::forgetFirstTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("ForgetHandlerFirstSanity", std::vector<size_t>);

    std::vector<size_t> input, expected, result;

    LOOP_START

    for(size_t n = 1; n < 10; n++) {
        ForgetHandlerFirst handler(n, 5);
        for(size_t b = 1; b < 5; b++) {
            prepareForgetTest(input, expected, result, n, b, false);
            LOOP_ASSERT_START(expected)
            result = handler.forget(input, result, b, b - 1);
            std::stringstream str;
            str << "ForgetHandlerFirstN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }

    LOOP_END("ForgetFirstVaryingSizes");

    END_TEST;
}

void SanityTestFactory::forgetAnyTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("ForgetHandlerAnySanity", std::vector<size_t>);

    std::vector<size_t> input, expected, result;

    LOOP_START

    for(size_t n = 1; n < 10; n++) {
        ForgetHandlerAny handler(n, 5);
        for(size_t b = 1; b < 5; b++) {
            prepareForgetTest(input, expected, result, n, b, true);
            LOOP_ASSERT_START(expected)
            result = handler.forget(input, result, b, 0);
            std::stringstream str;
            str << "ForgetHandlerFirstN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }

    LOOP_END("ForgetAnyIndex0VaryingSizes");

    LOOP_START

    for(size_t n = 1; n < 10; n++) {
        ForgetHandlerAny handler(n, 5);
        for(size_t b = 1; b < 5; b++) {
            prepareForgetTest(input, expected, result, n, b, false);
            LOOP_ASSERT_START(expected)
            result = handler.forget(input, result, b, b - 1);
            std::stringstream str;
            str << "ForgetHandlerFirstN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }

    LOOP_END("ForgetAnyIndexLastVaryingSizes");

    //TODO: Could add test for index in the middle

    END_TEST;
}

void SanityTestFactory::prepareForgetTest(std::vector<size_t>& input, std::vector<size_t>& expected, std::vector<size_t>& result, size_t n, size_t b, bool last) {
    size_t size = HelperFunctions::pow(n, b);

    input.resize(size);
    expected.resize(size / n);
    result.resize(size / n);

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i;
    }

    size_t sum = n * (n - 1) / 2;
    if(last) {
        size_t offset = n * n;
        for (size_t i = 0; i < expected.size(); ++i) {
            expected[i] = sum + i * offset;
        }
    } else {
        for (size_t i = 0; i < expected.size(); ++i) {
            expected[i] = sum * expected.size() + i * n;
        }
    }
}

void SanityTestFactory::introduceLastComputeTest(TestSettings &settings, TestLogger &logger) {
    logger.NotifyTestStart("IntroduceHandlerComputeSanity");

    IntroduceHandlerCompute ih;

    introduceLastCompleteTest(settings, logger, ih);
    introduceLastEdgeConsistencyTest(settings, logger, ih);
}

void SanityTestFactory::introduceLastIteratorTest(TestSettings &settings, TestLogger &logger) {
    logger.NotifyTestStart("IntroduceHandlerIteratorSanity");

    IteratorIntroduceHandler ih;

    introduceLastCompleteTest(settings, logger, ih);
    introduceLastEdgeConsistencyTest(settings, logger, ih);
}

void SanityTestFactory::introduceLastEdgeConsistencyTest(TestSettings &settings, TestLogger &logger, IntroduceHandlerLeast &ih) {
    // Some small handcrafted examples for introduce with 3 vertices
    BEGIN_TEST("IntroduceHandlerEdgeConsistencySanity", std::vector<size_t>)

    std::vector<size_t> input(9), expected(27), result(27), bag {1, 0};
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();

    // G has no edge 0-2
    g->clear(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i + 1;
    }

    h->clear(3);
    expected = std::vector<size_t> {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9};
    ASSERT_START(expected);
    result = ih.introduceLast(input, result, bag, h, g, 3, 2);
    ASSERT_END("IntroduceNonEdgesH", result)

    h->addEdge(0, 2);
    expected = std::vector<size_t> {0, 1, 0, 0, 2, 0, 0, 3, 0, 4, 0, 4, 5, 0, 5, 6, 0, 6, 0, 7, 0, 0, 8, 0, 0, 9, 0};
    ASSERT_START(expected);
    result = ih.introduceLast(input, result, bag, h, g, 3, 2);
    ASSERT_END("IntroduceEdgeAndNonEdgeH", result)

    h->addEdge(1, 2);
    expected = std::vector<size_t> {0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 9, 0};
    ASSERT_START(expected);
    result = ih.introduceLast(input, result, bag, h, g, 3, 2);
    ASSERT_END("IntroduceBothEdgesH", result)

    END_TEST
}

void SanityTestFactory::introduceLastCompleteTest(TestSettings &settings, TestLogger &logger, IntroduceHandlerLeast &ih) {
    BEGIN_LOOP_TEST("IntroduceHandlerCompleteGraphSanity", std::vector<size_t>)

    std::vector<size_t> input, expected, result, bag;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    size_t x = 0;
    GraphGenerator gen;

    LOOP_START
    bag.clear();
    gen.Path(h, 3);
    for(size_t n = 1; n < 10; n++) {
        input = std::vector<size_t>(1, 42);
        expected = std::vector<size_t>(n, 42);
        result.resize(n);
        gen.Clique(g, n);
        LOOP_ASSERT_START(expected)
        result = ih.introduceLast(input, result, bag, h, g, n, x);
        LOOP_ASSERT_END("IntroduceHandlerEmpty", result)
    }
    LOOP_END("IntroduceHandlerEmpty");


    LOOP_START
    gen.Clique(h, 5);
    for(size_t n = 1; n < 10; n++) {
        gen.Clique(g, n);
        for(size_t i = 0; i < n; i++) {
            g->addEdge(i, i);
        }
        for(size_t b = 0; b < 5; b++) {
            prepareIntroduceCompleteTest(input, expected, result, bag, n, b);
            LOOP_ASSERT_START(expected)
            result = ih.introduceLast(input, result, bag, h, g, n, x);
            std::stringstream str;
            str << "IntroduceHandlerCompleteN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }
    LOOP_END("IntroduceHandlerCliquePattern");

    LOOP_START
    gen.Cycle(h, 5);
    for(size_t n = 1; n < 10; n++) {
        gen.Clique(g, n);
        for(size_t i = 0; i < n; i++) {
            g->addEdge(i, i);
        }
        for(size_t b = 0; b < 5; b++) {
            prepareIntroduceCompleteTest(input, expected, result, bag, n, b);
            LOOP_ASSERT_START(expected)
            result = ih.introduceLast(input, result, bag, h, g, n, x);
            std::stringstream str;
            str << "IntroduceHandlerCycleN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }
    LOOP_END("IntroduceHandlerCyclePattern");

    END_TEST;
}

void SanityTestFactory::introduceLastPrecomputedTest(TestSettings &settings, TestLogger &logger) {
    logger.NotifyTestStart("IntroduceHandlerPrecomputedSanity");
    introduceLastEdgeConsistencyPrecomputedTest(settings, logger);
    introduceLastCompletePrecomputedTest(settings, logger);
}

void SanityTestFactory::introduceLastEdgeConsistencyPrecomputedTest(TestSettings &settings, TestLogger &logger) {
    // Some small handcrafted examples for introduce with 3 vertices
    BEGIN_TEST("IntroduceHandlerPrecomputedEdgeConsistencySanity", std::vector<size_t>)

    std::vector<size_t> input(9), expected(27), result(27), bag {1, 0};
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();

    // G has no edge 0-2
    g->clear(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i + 1;
    }

    auto pre = EdgeConsistencyPrecomputation::InitializeLeast(g, 2);
    IntroduceHandlerLeastPrecomputed ih(pre);

    h->clear(3);
    expected = std::vector<size_t> {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9};
    ASSERT_START(expected);
    result = ih.introduceLast(input, result, bag, h, g, 3, 2);
    ASSERT_END("IntroduceNonEdgesH", result)

    h->addEdge(0, 2);
    expected = std::vector<size_t> {0, 1, 0, 0, 2, 0, 0, 3, 0, 4, 0, 4, 5, 0, 5, 6, 0, 6, 0, 7, 0, 0, 8, 0, 0, 9, 0};
    ASSERT_START(expected);
    result = ih.introduceLast(input, result, bag, h, g, 3, 2);
    ASSERT_END("IntroduceEdgeAndNonEdgeH", result)

    h->addEdge(1, 2);
    expected = std::vector<size_t> {0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 9, 0};
    ASSERT_START(expected);
    result = ih.introduceLast(input, result, bag, h, g, 3, 2);
    ASSERT_END("IntroduceBothEdgesH", result)

    END_TEST
}

void SanityTestFactory::introduceLastCompletePrecomputedTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("IntroduceHandlerPrecomputedCompleteGraphSanity", std::vector<size_t>)

    std::vector<size_t> input, expected, result, bag;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    size_t x = 0;
    GraphGenerator gen;

    LOOP_START
    bag.clear();
    gen.Path(h, 3);
    for(size_t n = 1; n < 10; n++) {
        input = std::vector<size_t>(1, 42);
        expected = std::vector<size_t>(n, 42);
        result.resize(n);
        gen.Clique(g, n);
        auto pre = EdgeConsistencyPrecomputation::InitializeLeast(g, 0);
        IntroduceHandlerLeastPrecomputed ih(pre);
        LOOP_ASSERT_START(expected)
        result = ih.introduceLast(input, result, bag, h, g, n, x);
        LOOP_ASSERT_END("IntroduceHandlerEmpty", result)
    }
    LOOP_END("IntroduceHandlerEmpty");


    LOOP_START
    gen.Clique(h, 5);
    for(size_t n = 1; n < 10; n++) {
        gen.Clique(g, n);
        for(size_t i = 0; i < n; i++) {
            g->addEdge(i, i);
        }
        auto pre = EdgeConsistencyPrecomputation::InitializeLeast(g, 4);
        IntroduceHandlerLeastPrecomputed ih(pre);

        for(size_t b = 0; b < 5; b++) {
            prepareIntroduceCompleteTest(input, expected, result, bag, n, b);
            LOOP_ASSERT_START(expected)
            result = ih.introduceLast(input, result, bag, h, g, n, x);
            std::stringstream str;
            str << "IntroduceHandlerCompleteN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }
    LOOP_END("IntroduceHandlerCliquePattern");

    LOOP_START
    gen.Cycle(h, 5);
    for(size_t n = 1; n < 10; n++) {
        gen.Clique(g, n);
        for(size_t i = 0; i < n; i++) {
            g->addEdge(i, i);
        }
        auto pre = EdgeConsistencyPrecomputation::InitializeLeast(g, 4);
        IntroduceHandlerLeastPrecomputed ih(pre);

        for(size_t b = 0; b < 5; b++) {
            prepareIntroduceCompleteTest(input, expected, result, bag, n, b);
            LOOP_ASSERT_START(expected)
            result = ih.introduceLast(input, result, bag, h, g, n, x);
            std::stringstream str;
            str << "IntroduceHandlerCycleN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }
    LOOP_END("IntroduceHandlerCyclePattern");

    END_TEST;
}

void SanityTestFactory::prepareIntroduceCompleteTest(std::vector<size_t>& input, std::vector<size_t>& expected,
        std::vector<size_t>& result, std::vector<size_t>& bag, size_t n, size_t b) {
    size_t size = HelperFunctions::pow(n, b);

    input.resize(size);
    expected.resize(size * n);
    result.resize(size * n);

    bag.clear();

    for (size_t i = 1; i <= b; ++i) {
        bag.push_back(i);
    }

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i + 1;
    }

    for (size_t i = 0; i < expected.size(); ++i) {
        expected[i] = (i / n) + 1;
    }
}

void SanityTestFactory::defaultHomomorphismTest(TestSettings& settings, TestLogger& logger) {
    logger.NotifyTestStart("Default homomorphism configuration");
    homomorphismTest(settings, logger, ConfigurationFactory::defaultSettings, "DefaultHomomorphism");
}

void SanityTestFactory::iteratorHomomorphismTest(TestSettings& settings, TestLogger& logger) {
    logger.NotifyTestStart("Iterator homomorphism configuration");
    homomorphismTest(settings, logger, ConfigurationFactory::iteratorRemapper, "IteratorHomomorphism");
}

void SanityTestFactory::homomorphismTest(TestSettings& settings, TestLogger& logger,
        HomomorphismSettings (*hom)(size_t, size_t), const std::string& settingsName) {
    homomorphismHandcraftedTest(settings, logger, hom, settingsName);
    homomorphismLoopTest(settings, logger, hom, settingsName);
}

void SanityTestFactory::defaultHomomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger) {
    homomorphismHandcraftedTest(settings, logger,
            ConfigurationFactory::defaultSettings, "DefaultHomomorphism");
}

void SanityTestFactory::defaultHomomorphismLoopTest(TestSettings& settings, TestLogger& logger) {
    homomorphismLoopTest(settings, logger,
            ConfigurationFactory::defaultSettings, "DefaultHomomorphism");
}

void SanityTestFactory::iteratorHomomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger) {
    homomorphismHandcraftedTest(settings, logger,
            ConfigurationFactory::iteratorRemapper, "IteratorRemappingHomomorphism");
}

void SanityTestFactory::iteratorHomomorphismLoopTest(TestSettings& settings, TestLogger& logger) {
    homomorphismLoopTest(settings, logger,
            ConfigurationFactory::iteratorRemapper, "IteratorRemappingHomomorphism");
}

void SanityTestFactory::homomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger,
        HomomorphismSettings (*hom)(size_t, size_t), const std::string& settingsName) {
    BEGIN_TEST(settingsName + "Handcrafted", long)

    TamakiRunner tam;
    GraphGenerator gen;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NiceTreeDecomposition> ntd;
    HomomorphismSettings homSet;
    long result;

    gen.Cycle(h, 4);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    homSet = hom(h->vertCount(), ntd->getWidth());
    ASSERT_START(32);
    result = HomomorphismCounter(h, h, ntd, homSet).compute();
    ASSERT_END("SquareToSquare", result)

    gen.Cycle(h, 4);
    h->addEdge(0, 2);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    homSet = hom(h->vertCount(), ntd->getWidth());
    ASSERT_START(16);
    result = HomomorphismCounter(h, h, ntd, homSet).compute();
    ASSERT_END("SquareWithDiagonalToSelf", result)

    END_TEST
}

void SanityTestFactory::homomorphismLoopTest(TestSettings& settings, TestLogger& logger,
        HomomorphismSettings (*hom)(size_t, size_t), const std::string& settingsName) {
    BEGIN_LOOP_TEST(settingsName + "Loop", long)

    TamakiRunner tam;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NiceTreeDecomposition> ntd;
    HomomorphismSettings homSet;
    long result;

    LOOP_START
    for(size_t k = 3; k < 10; k += 2) {
        GraphGenerator::Cycle(h, k);
        ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
        for(size_t r = 2; r < 10; r += 2) {
            for(size_t c = 2; c < 5; c++) {
                GraphGenerator::CompleteGrid(g, r, c);
                homSet = hom(g->vertCount(), ntd->getWidth());
                LOOP_ASSERT_START(0)
                result = HomomorphismCounter(h, g, ntd, homSet).compute();
                std::stringstream str;
                str << "OddCycleInGridK" << k << "R" << r << "C" << c;
                LOOP_ASSERT_END(str.str(), result)
            }
        }
    }
    LOOP_END("NoOddCycleInGrid");

    LOOP_START
    GraphGenerator::Path(h, 4);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    for(size_t n = 2; n < 10; n++) {
        GraphGenerator::Clique(g, n);
        homSet = hom(g->vertCount(), ntd->getWidth());
        LOOP_ASSERT_START(n * (n - 1) * (n - 1) * (n - 1))
        result = HomomorphismCounter(h, g, ntd, homSet).compute();
        std::stringstream str;
        str << "PathInCompleteGraphN" << n;
        LOOP_ASSERT_END(str.str(), result)
    }
    LOOP_END("PathInCompleteGraph");

    END_TEST
}

void SanityTestFactory::HomomorphismPrecomputedHandcraftedTest(TestSettings& settings, TestLogger& logger) {
    BEGIN_TEST("HomomorphismPrecomputedHandcrafted", long)

    TamakiRunner tam;
    GraphGenerator gen;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NiceTreeDecomposition> ntd;
    DynamicProgrammingSettings homSet;
    long result;

    gen.Cycle(h, 4);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(h, ntd->getWidth());
    auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(h, ntd->getWidth());
    homSet = ConfigurationFactory::DefaultDynamicSettings(h->vertCount(), h->vertCount(), pre1, pre2);
    ASSERT_START(32);
    result = DynamicProgrammingCounter(h, h, ntd, homSet).compute();
    ASSERT_END("SquareToSquare", result)

    gen.Cycle(h, 4);
    h->addEdge(0, 2);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    pre1 = EdgeConsistencyPrecomputation::InitializeLeast(h, ntd->getWidth());
    pre2 = EdgeConsistencyPrecomputation::InitializeSecond(h, ntd->getWidth());
    homSet = ConfigurationFactory::DefaultDynamicSettings(h->vertCount(), h->vertCount(), pre1, pre2);
    ASSERT_START(16);
    result = DynamicProgrammingCounter(h, h, ntd, homSet).compute();
    ASSERT_END("SquareWithDiagonalToSelf", result)

    END_TEST
}

void SanityTestFactory::HomomorphismPrecomputedLoopTest(TestSettings& settings, TestLogger& logger) {
    BEGIN_LOOP_TEST("HomomorphismPrecomputedLoop", long)

    TamakiRunner tam;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NiceTreeDecomposition> ntd;
    DynamicProgrammingSettings homSet;
    long result;

    LOOP_START
    for(size_t k = 3; k < 10; k += 2) {
        GraphGenerator::Cycle(h, k);
        ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
        for(size_t r = 2; r < 10; r += 2) {
            for(size_t c = 2; c < 5; c++) {
                GraphGenerator::CompleteGrid(g, r, c);
                auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g, ntd->getWidth());
                auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g, ntd->getWidth());
                homSet = ConfigurationFactory::DefaultDynamicSettings(g->vertCount(), ntd->getWidth(), pre1, pre2);
                LOOP_ASSERT_START(0)
                result = DynamicProgrammingCounter(h, g, ntd, homSet).compute();
                std::stringstream str;
                str << "OddCycleInGridK" << k << "R" << r << "C" << c;
                LOOP_ASSERT_END(str.str(), result)
            }
        }
    }
    LOOP_END("NoOddCycleInGrid");

    LOOP_START
    GraphGenerator::Path(h, 4);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    for(size_t n = 2; n < 10; n++) {
        GraphGenerator::Clique(g, n);
        auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g, ntd->getWidth());
        auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g, ntd->getWidth());
        homSet = ConfigurationFactory::DefaultDynamicSettings(g->vertCount(), ntd->getWidth(), pre1, pre2);
        LOOP_ASSERT_START(n * (n - 1) * (n - 1) * (n - 1))
        result = DynamicProgrammingCounter(h, g, ntd, homSet).compute();
        std::stringstream str;
        str << "PathInCompleteGraphN" << n;
        LOOP_ASSERT_END(str.str(), result)
    }
    LOOP_END("PathInCompleteGraph");

    END_TEST
}

void SanityTestFactory::DefaultPathdecompHomomorphismTest(TestSettings& settings, TestLogger& logger) {
    logger.NotifyTestStart("Default path decomposition homomorphism configuration");
    PathdecompHomomorphismTest(settings, logger, ConfigurationFactory::DefaultPathSettings, "DefaultPathDecomp");
}

void SanityTestFactory::PathdecompHomomorphismTest(TestSettings& settings, TestLogger& logger,
                PathdecompotisionSettings (*hom)(size_t, size_t), const std::string& settingsName) {
    PathDecompHomomorphismHandcraftedTest(settings, logger, hom, settingsName);
    PathdecompHomomorphismLoopTest(settings, logger, hom, settingsName);
}

void SanityTestFactory::PathDecompHomomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger,
                PathdecompotisionSettings (*hom)(size_t, size_t), const std::string& settingsName) {
    BEGIN_TEST(settingsName + "Handcrafted", long)

    TamakiRunner tam;
    GraphGenerator gen;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NicePathDecomposition> npd;
    PathdecompotisionSettings homSet;
    long result;

    gen.Cycle(h, 4);
    npd = NicePathDecomposition::FromTd(tam.decompose(h));
    homSet = hom(h->vertCount(), npd->getWidth());
    ASSERT_START(32);
    result = PathdecompositionCounter(h, h, npd, homSet).compute();
    ASSERT_END("SquareToSquare", result)

    gen.Cycle(h, 4);
    h->addEdge(0, 2);
    npd = NicePathDecomposition::FromTd(tam.decompose(h));
    homSet = hom(h->vertCount(), npd->getWidth());
    ASSERT_START(16);
    result = PathdecompositionCounter(h, h, npd, homSet).compute();
    ASSERT_END("SquareWithDiagonalToSelf", result)

    END_TEST
}

void SanityTestFactory::PathdecompHomomorphismLoopTest(TestSettings& settings, TestLogger& logger,
                PathdecompotisionSettings (*hom)(size_t, size_t), const std::string& settingsName) {
    BEGIN_LOOP_TEST(settingsName + "Loop", long)

    TamakiRunner tam;
    GraphGenerator gen;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NicePathDecomposition> npd;
    PathdecompotisionSettings homSet;
    long result;

    LOOP_START
    for(size_t k = 3; k < 10; k += 2) {
        gen.Cycle(h, k);
        npd = NicePathDecomposition::FromTd(tam.decompose(h));
        for(size_t r = 2; r < 10; r += 2) {
            for(size_t c = 2; c < 5; c++) {
                GraphGenerator::CompleteGrid(g, r, c);
                homSet = hom(g->vertCount(), npd->getWidth());
                LOOP_ASSERT_START(0)
                result = PathdecompositionCounter(h, g, npd, homSet).compute();
                std::stringstream str;
                str << "OddCycleInGridK" << k << "R" << r << "C" << c;
                LOOP_ASSERT_END(str.str(), result)
            }
        }
    }
    LOOP_END("NoOddCycleInGrid");

    LOOP_START
    gen.Path(h, 4);
    npd = NicePathDecomposition::FromTd(tam.decompose(h));
    for(size_t n = 2; n < 10; n++) {
        gen.Clique(g, n);
        homSet = hom(g->vertCount(), npd->getWidth());
        LOOP_ASSERT_START(n * (n - 1) * (n - 1) * (n - 1))
        result = PathdecompositionCounter(h, g, npd, homSet).compute();
        std::stringstream str;
        str << "PathInCompleteGraphN" << n;
        LOOP_ASSERT_END(str.str(), result)
    }
    LOOP_END("PathInCompleteGraph");

    END_TEST
}

void SanityTestFactory::maxDegreeTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("MaxDegreeTest", long);
    
    std::shared_ptr<EdgeSetGraph> h = std::make_shared<EdgeSetGraph>(1);
    GraphGenerator::Clique(h, 3);
    
    std::shared_ptr<EdgeSetGraph> g = std::make_shared<EdgeSetGraph>(1);
    long result;
    
    LOOP_START
    for(size_t r = 2; r < 10; r += 2) {
        for(size_t c = 2; c < 5; c++) {
            GraphGenerator::CompleteGrid(g, r, c);
            LOOP_ASSERT_START(0)
            result = TraversalHomomorphismCounter::Count(h, g);//HomomorphismCounter(h, g, ntd, hom).compute();
            std::stringstream str;
            str << "TriangleInGrid" << "R" << r << "C" << c;
            LOOP_ASSERT_END(str.str(), result)
        }
    }
    LOOP_END("NoTriangleInGrid");
    
    LOOP_START
    GraphGenerator::Path(h, 4);
    for(size_t n = 1; n < 10; n++) {
        GraphGenerator::Clique(g, n);
        LOOP_ASSERT_START(n * (n - 1) * (n - 1) * (n - 1))
        result = TraversalHomomorphismCounter::Count(h, g);
        std::stringstream str;
        str << "PathInCompleteGraphN" << n;
        LOOP_ASSERT_END(str.str(), result)
    }
    LOOP_END("PathInCompleteGraph");
    
    END_TEST;
}


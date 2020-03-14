#include "experiments/sanity_test_factory.h"

#include "experiments/graph_generator.h"
#include "homomorphism/forget_handler.h"
#include "homomorphism/introduce_handler.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/iterator_remapper.h"
#include "homomorphism/main.h"
#include "homomorphism/configuration_factory.h"
#include "homomorphism/tamaki_runner.h"

#define BEGIN_TEST(name, type) logger.NotifyTestStart(name);type exp;

#define END_TEST //logger.NotifyTestEnd(duration);

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
        case FORGET_HANDLER:
            return forgetLastTest;
        case INTRODUCE_HANDLER_CONSISTENCY:
            return introduceLastEdgeConsistencyTest;
        case INTRODUCE_HANDLER_COMPLETE:
            return introduceLastCompleteTest;
        case HOMOMORPHISM_HANDCRAFTED_DEFAULT:
            return defaultHomomorphismHandcraftedTest;
        case HOMOMORPHISM_LOOP_DEFAULT:
            return defaultHomomorphismLoopTest;
        case INTRODUCE_HANDLER_TEST:
            return introduceLastTest;
        case HOMOMORPHISM_COUNTER_DEFAULT:
            return defaultHomomorphismTest;
        default:
            return nullptr;
    }
}

std::vector<TestCase> SanityTestFactory::allTests() {
    return std::vector<TestCase> { TESTCASES };
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
    remapperTest(settings, logger, mapper);
}

void SanityTestFactory::iteratorRemapperTest(TestSettings& settings, TestLogger& logger) {
    IteratorRemapper mapper;
    remapperTest(settings, logger, mapper);
}

void SanityTestFactory::remapperTest(TestSettings& settings, TestLogger& logger, Remapper& mapper) {
    BEGIN_TEST("CalculationRemapperSanity", std::vector<size_t>);
    std::vector<size_t> input(8), result(8), expected;

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i;
    }

    mapper.SetSizes(2, 3);

    expected = std::vector<size_t> {0, 2, 1, 3, 4, 6, 5, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 1);
    ASSERT_END("ExtractMiddle", result)

    expected = std::vector<size_t> {0, 4, 1, 5, 2, 6, 3, 7};
    ASSERT_START(expected);
    mapper.Extract(input, result, 0);
    ASSERT_END("ExtractFirst", result)

    expected = std::vector<size_t> {0, 2, 1, 3, 4, 6, 5, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 1);
    ASSERT_END("InsertMiddle", result)

    expected = std::vector<size_t> {0, 2, 4, 6, 1, 3, 5, 7};
    ASSERT_START(expected);
    mapper.Insert(input, result, 0);
    ASSERT_END("insertFirst", result)

    END_TEST;
}

void SanityTestFactory::forgetLastTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("ForgetHandlerSanity", std::vector<size_t>);

    std::vector<size_t> input, expected, result;

    ForgetHandler handler;

    LOOP_START

    for(size_t n = 1; n < 10; n++) {
        for(size_t b = 1; b < 5; b++) {
            prepareForgetTest(input, expected, result, n, b);
            LOOP_ASSERT_START(expected)
            result = handler.forgetLast(input, result, n);
            std::stringstream str;
            str << "ForgetHandlerN" << n << "B" << b;
            LOOP_ASSERT_END(str.str(), result)
        }
    }

    LOOP_END("ForgetLastVaryingSizes");

    END_TEST;
}

void SanityTestFactory::prepareForgetTest(std::vector<size_t>& input, std::vector<size_t>& expected, std::vector<size_t>& result, size_t n, size_t b) {
    size_t size = HelperFunctions::pow(n, b);

    input.resize(size);
    expected.resize(size / n);
    result.resize(size / n);

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i;
    }

    size_t sum = n * (n - 1) / 2;
    size_t offset = n * n;
    for (size_t i = 0; i < expected.size(); ++i) {
        expected[i] = sum + i * offset;
    }
}

void SanityTestFactory::introduceLastTest(TestSettings &settings, TestLogger &logger) {
    logger.NotifyTestStart("IntroduceHandlerSanity");
    introduceLastCompleteTest(settings, logger);
    introduceLastEdgeConsistencyTest(settings, logger);
}

void SanityTestFactory::introduceLastEdgeConsistencyTest(TestSettings &settings, TestLogger &logger) {
    // Some small handcrafted examples for introduce with 3 vertices
    BEGIN_TEST("IntroduceHandlerEdgeConsistencySanity", std::vector<size_t>)

    std::vector<size_t> input(9), expected(27), result(27), bag {0, 1};
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();

    // G has no edge 0-2
    g->clear(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);

    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = i + 1;
    }

    IntroduceHandler ih;

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

void SanityTestFactory::introduceLastCompleteTest(TestSettings &settings, TestLogger &logger) {
    BEGIN_LOOP_TEST("IntroduceHandlerCompleteGraphSanity", std::vector<size_t>)

    std::vector<size_t> input, expected, result, bag;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    size_t x = 0;
    GraphGenerator gen;

    IntroduceHandler handler;

    LOOP_START
    bag.clear();
    gen.Path(h, 3);
    for(size_t n = 1; n < 10; n++) {
        input = std::vector<size_t>(1, 42);
        expected = std::vector<size_t>(n, 42);
        result.resize(n);
        gen.Clique(g, n);
        LOOP_ASSERT_START(expected)
        result = handler.introduceLast(input, result, bag, h, g, n, x);
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
            result = handler.introduceLast(input, result, bag, h, g, n, x);
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
            result = handler.introduceLast(input, result, bag, h, g, n, x);
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
        input[i] = i;
    }

    for (size_t i = 0; i < expected.size(); ++i) {
        expected[i] = i / n;
    }
}

void SanityTestFactory::defaultHomomorphismTest(TestSettings& settings, TestLogger& logger) {
    logger.NotifyTestStart("Default homomorphism configuration");
    homomorphismTest(settings, logger, ConfigurationFactory::defaultSettings());
}

void SanityTestFactory::homomorphismTest(TestSettings& settings, TestLogger& logger, HomomorphismSettings hom) {
    homomorphismHandcraftedTest(settings, logger, hom);
    homomorphismLoopTest(settings, logger, hom);
}

void SanityTestFactory::defaultHomomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger) {
    homomorphismHandcraftedTest(settings, logger, ConfigurationFactory::defaultSettings());
}

void SanityTestFactory::defaultHomomorphismLoopTest(TestSettings& settings, TestLogger& logger) {
    homomorphismLoopTest(settings, logger, ConfigurationFactory::defaultSettings());
}

void SanityTestFactory::homomorphismHandcraftedTest(TestSettings& settings, TestLogger& logger, HomomorphismSettings hom) {
    BEGIN_TEST("Handcrafted", long)

    TamakiRunner tam;
    GraphGenerator gen;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NiceTreeDecomposition> ntd;
    long result;

    gen.Cycle(h, 4);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    ASSERT_START(32);
    result = HomomorphismCounter(h, h, ntd, hom).compute();
    ASSERT_END("SquareToSquare", result)

    gen.Cycle(h, 4);
    h->addEdge(0, 2);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    ASSERT_START(16);
    result = HomomorphismCounter(h, h, ntd, hom).compute();
    ASSERT_END("ExtractMiddle", result)

    END_TEST
}

void SanityTestFactory::homomorphismLoopTest(TestSettings& settings, TestLogger& logger, HomomorphismSettings hom) {
    BEGIN_LOOP_TEST("Loop", long)

    TamakiRunner tam;
    GraphGenerator gen;
    std::shared_ptr<Graph> h = AdjacencyMatrixGraph::testGraph(), g = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<NiceTreeDecomposition> ntd;
    long result;

    LOOP_START
    for(size_t k = 3; k < 10; k += 2) {
        gen.Cycle(h, k);
        ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
        for(size_t r = 2; r < 10; r += 2) {
            for(size_t c = 2; c < 5; c++) {
                GraphGenerator::CompleteGrid(g, r, c);
                LOOP_ASSERT_START(0)
                result = HomomorphismCounter(h, g, ntd, hom).compute();
                std::stringstream str;
                str << "OddCycleInGridK" << k << "R" << r << "C" << c;
                LOOP_ASSERT_END(str.str(), result)
            }
        }
    }
    LOOP_END("NoOddCycleInGrid");

    LOOP_START
    gen.Path(h, 4);
    ntd = NiceTreeDecomposition::FromTd(tam.decompose(h));
    for(size_t n = 1; n < 10; n++) {
        gen.Clique(g, n);
        LOOP_ASSERT_START(n * (n - 1) * (n - 1) * (n - 1))
        result = HomomorphismCounter(h, g, ntd, hom).compute();
        std::stringstream str;
        str << "PathInCompleteGraphN" << n;
        LOOP_ASSERT_END(str.str(), result)
    }
    LOOP_END("PathInCompleteGraph");

    END_TEST
}

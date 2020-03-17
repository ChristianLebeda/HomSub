//
//  test_factory.cpp
//  test
//
//  Created by Jonas Mortensen on 26/02/2020.
//

#include <stdio.h>
#include "experiments/test_factory.h"
#include "homomorphism/tamaki-2017.h"
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/nice_tree_decomposition.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/main.h"
#include "experiments/graph_generator.h"
#include "experiments/test_settings.h"
#include <memory>
#include "homomorphism/configuration_factory.h"

#define BEGIN_TEST(name) logger.NotifyTestStart(name);int duration = 0;auto start = std::chrono::steady_clock::now();auto stop = start;SubStep step;long exp = 0;int n = 1;

#define END_TEST logger.NotifyTestEnd(duration);

#define SUBSTEP_START(substep) step = substep;

#define SUBSTEP_END(note) logger.NotifyTestSubstep(step, note, duration);

#define ASSERT_START(expected) exp = expected;

#define ASSERT_END(note, result) logger.NotifyTestAssert(note,exp == result);

#define START_CLOCK start = std::chrono::steady_clock::now();

#define STOP_CLOCK stop = std::chrono::steady_clock::now();duration = milliSecondDifferene(start, stop);

#define ITERATIVE_START n = 1; while( ((float)duration/1000.0) < settings.GetPrTestTime()) {

#define ITERATIVE_END n++;} logger.NotifyTestIterative(n, "", duration);

#define STEPLOOP_START \
    for(int k = 2; k <= 5; k++) { \
        for(int logn = 3; logn <= 10; logn++) { \
            int n = 1 << logn; \
            int c = k * logn; \
            // Skip too small or too large cases \
            if(15 > c || c > 28) { continue; }

#define STEPLOOP_END } }

std::function<void(TestSettings&, TestLogger&)> TestFactory::GetTest(int i) {
    auto tests = GetAllTests();
    if(i < tests.size()) {
        return tests[i];
    } else {
        return nullptr;
    }
}

std::vector<std::function<void(TestSettings&, TestLogger&)>> TestFactory::GetAllTests() {
    std::vector<std::function<void(TestSettings&, TestLogger&)>> tests
        {Test1, Test2, Test3, Test4, Test5};
    return tests;
}

int TestFactory::TestCount() {
    return 0;
}

void TestFactory::Test1(TestSettings& settings, TestLogger& logger)
{
    BEGIN_TEST("DecomposeSquare");
    
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    START_CLOCK;
    auto spasm = Main::spasmFromGraph(h);
    STOP_CLOCK;
    SUBSTEP_END("");
    
    SUBSTEP_START(SubStep::DECOMPOSE_SPASM);
    START_CLOCK;
    Main::decomposedSpasmFromSpasm(spasm);
    STOP_CLOCK;
    SUBSTEP_END("");
    
    END_TEST;
}

void TestFactory::Test2(TestSettings& settings, TestLogger& logger)
{
    BEGIN_TEST("SpasmFromSquare");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2); //Should h be initialised between steps?
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    START_CLOCK;
    Main::spasmFromGraph(h);
    STOP_CLOCK;
    SUBSTEP_END("Method1");
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    START_CLOCK;
    Main::spasmFromGraph(h);
    STOP_CLOCK;
    SUBSTEP_END("Method2");
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    START_CLOCK;
    Main::spasmFromGraph(h);
    STOP_CLOCK;
    SUBSTEP_END("Method3");
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    START_CLOCK;
    Main::spasmFromGraph(h);
    STOP_CLOCK;
    SUBSTEP_END("Method4");
    
    END_TEST;
}

void TestFactory::Test3(TestSettings& settings, TestLogger& logger) {
    BEGIN_TEST("SquareSanity");
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

void TestFactory::Test4(TestSettings& settings, TestLogger& logger)
{
    
    BEGIN_TEST("SquareInN-Grid");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    ITERATIVE_START;
    GraphGenerator::CompleteGrid(g, n*2, n*2);
    START_CLOCK;
    Main::subgraphsGraph(h, g);
    STOP_CLOCK;
    ITERATIVE_END;
    
    END_TEST;
}

void TestFactory::Test5(TestSettings& settings, TestLogger& logger)
{
    
    BEGIN_TEST("DecomposeNClique");
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    
    ITERATIVE_START;
    GraphGenerator::Clique(g, n*2);
    START_CLOCK;
    auto spasm = Main::spasmFromGraph(g);
    Main::decomposedSpasmFromSpasm(spasm);
    STOP_CLOCK;
    ITERATIVE_END;
    
    END_TEST;
}

void TestFactory::joinHandler(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("JoinHandler")

    JoinHandler jh;

    std::vector<size_t> vec1, vec2;

    STEPLOOP_START

    vec1.resize(1 << c);
    fillVector(vec1);
    vec2.resize(1 << c);
    fillVector(vec2);
    // TODO: Update log
    START_CLOCK
    jh.join(vec1, vec2);
    STOP_CLOCK

    STEPLOOP_END

    END_TEST
}

int TestFactory::milliSecondDifferene(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> stop) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}

void TestFactory::fillVector(std::vector<size_t> data) {
    for(auto & entry : data) {
        entry = rand();
    }
}

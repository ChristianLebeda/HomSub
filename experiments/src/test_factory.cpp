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

#define BEGIN_TEST(name) logger.NotifyTestStart(name);int duration = 0;auto start = std::chrono::high_resolution_clock::now();auto stop = start;SubStep step;long exp = 0;

#define END_TEST logger.NotifyTestEnd(duration);

#define SUBSTEP_START(substep) start = std::chrono::high_resolution_clock::now();step = substep;

#define SUBSTEP_END(note) stop = std::chrono::high_resolution_clock::now();duration = microSecondDifferene(start, stop);logger.NotifyTestSubstep(step, note, duration);

#define ASSERT_START(expected) exp = expected;

#define ASSERT_END(note, result) logger.NotifyTestAssert(note,exp == result);

std::function<void(TestSettings&, TestLogger&)> TestFactory::GetTest(int i) {
    switch (i) {
        case 1:
            return Test1;
            break;
        case 2:
            return Test2;
        default:
            return nullptr;
    }
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
    auto spasm = Main::spasmFromGraph(h);
    SUBSTEP_END("");
    
    SUBSTEP_START(SubStep::DECOMPOSE_SPASM);
    Main::decomposedSpasmFromSpasm(spasm);
    SUBSTEP_END("");
    
    END_TEST;
}

void TestFactory::Test2(TestSettings& settings, TestLogger& logger)
{
    BEGIN_TEST("SpasmFromSquare");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2); //Should h be initialised between steps?
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    Main::spasmFromGraph(h);
    SUBSTEP_END("Method1");
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    Main::spasmFromGraph(h);
    SUBSTEP_END("Method2");
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    Main::spasmFromGraph(h);
    SUBSTEP_END("Method3");
    
    SUBSTEP_START(SubStep::CREATE_SPASM);
    Main::spasmFromGraph(h);
    SUBSTEP_END("Method4");
    
    END_TEST;
}

int TestFactory::microSecondDifferene(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> stop) {
    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

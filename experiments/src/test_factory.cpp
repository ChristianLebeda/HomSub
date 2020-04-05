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
#include <future>
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/iterator_remapper.h"
#include "homomorphism/traversal_homomorphism_counter.h"

#define BEGIN_TEST(name) logger.NotifyTestStart(name);std::vector<int> durations(settings.GetRepetitions(),0);int duration = 0;auto start = std::chrono::steady_clock::now();auto stop = start;SubStep step;long exp = 0;int n = 1;

#define END_TEST logger.NotifyTestEnd(duration);

#define START_CLOCK start = std::chrono::steady_clock::now();

#define STOP_CLOCK stop = std::chrono::steady_clock::now();duration = milliSecondDifferene(start, stop);

#define ITERATIVE_START(init) n = init; while( ((float)duration/1000.0) < settings.GetPrTestTime()) {

#define ITERATIVE_END(incr) logger.NotifyTestIterative(n, "", duration);incr;}

#define REPEATED_CLOCK_START \
    for(int r = 0; r < settings.GetRepetitions(); r++) { \
        START_CLOCK;

#define REPEATED_CLOCK_END \
        STOP_CLOCK; \
        durations[r] = duration; \
    }

#define LOG_DURATIONS(args) \
for(int q = 0; q < durations.size(); q++) { \
    logger.log(args, durations[q]) \
}
    

#define STEPLOOP_START \
    for(int k = 2; k <= 5; k++) { \
        for(int logn = 3; logn <= 10; logn++) { \
            int n = 1 << logn; \
            int c = k * logn; \
            /* Skip too small or too large cases */ \
            if(15 > c || c > 28) { continue; } \
            size_t size = 1 << c;

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
        {
            SquaresInGrid,
            BinaryTreeInBinaryTree,
            CliquesInClique,
            EdgesInPath,
            PathInRandomGraph,
            RandomPatternsInRandomGraph,
            ForgetLeastSignificant,
            joinHandler,
            InsertClosedForm,
            ExtractClosedForm,
            InsertIterator,
            ExtractIterator,
            MaxDegreeHomomorphismCount
        };
    return tests;
}

int TestFactory::TestCount() {
    return 0;
}

void TestFactory::SquaresInGrid(TestSettings& settings, TestLogger& logger)
{
    BEGIN_TEST("SquareInNGrid");
    
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    
    for(int n = 1; n < 17; n = n * 2) {
        GraphGenerator::CompleteGrid(g, n, n);
        REPEATED_CLOCK_START;
        Main::subgraphsGraph(h, g);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("", n, 4, d);
        }
    }

    END_TEST;
}

void TestFactory::BinaryTreeInBinaryTree(TestSettings& settings, TestLogger& logger)
{
    BEGIN_TEST("BinaryTreeInBinaryTree");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g  = AdjacencyMatrixGraph::testGraph();
    

    for(int k = 1; k < 4; k++) {
        GraphGenerator::CompleteBinaryTree(h, k);
        GraphGenerator::CompleteBinaryTree(g, k+3);
        
        REPEATED_CLOCK_START;
        Main::subgraphsGraph(h, g);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("", k+3, k, d);
        }
    }
    
    
    END_TEST;
}

void TestFactory::CliquesInClique(TestSettings& settings, TestLogger& logger) {
    BEGIN_TEST("CliquesInLargerCliques");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    
    for(int n = 1; n < 6; n++) {
        GraphGenerator::Clique(h, n);
        GraphGenerator::Clique(g, n*n);
        REPEATED_CLOCK_START;
        Main::subgraphsGraph(h, g);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("", n*n, n, d);
        }
    }

    END_TEST;
}

void TestFactory::EdgesInPath(TestSettings& settings, TestLogger& logger)
{
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    
    GraphGenerator::Path(h, 1);
    
    BEGIN_TEST("EdgesInPath");
    
    for(int n = 1; n < 4097; n = n*2) {
        GraphGenerator::Path(g, n);
        REPEATED_CLOCK_START;
        Main::subgraphsGraph(h, g);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("", n, 2, d);
        }
    }
    
    END_TEST;
}

void TestFactory::PathInRandomGraph(TestSettings& settings, TestLogger& logger)
{
    
    BEGIN_TEST("PathInRandomGraph");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    
    for(int k = 1; k < 8; k++) {
        GraphGenerator::Path(h, k);
        GraphGenerator::EdgeProbabilityGraph(g, 1 << k, 0.5f);
        REPEATED_CLOCK_START;
        Main::subgraphsGraph(h, g);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("", 1 << k, k, d);
        }
    }
    
    END_TEST;
}

void TestFactory::RandomPatternsInRandomGraph(TestSettings &settings, TestLogger &logger)
{
    BEGIN_TEST("RandomPatternInRandomGraph");
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    
    for(int k = 1; k < 7; k++) {
        GraphGenerator::EdgeProbabilityGraph(h, k, 0.5f);
        GraphGenerator::EdgeProbabilityGraph(g, 1 << k, 0.5f);
        REPEATED_CLOCK_START;
        Main::subgraphsGraph(h, g);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("", 1 << k, k, d);
        }
    }
    
    END_TEST;
}

void TestFactory::ForgetLeastSignificant(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("ForgetLeastSignificant")

    ForgetHandler handler;

    std::vector<size_t> vec1, vec2;

    STEPLOOP_START

        vec1.resize(size);
        fillVector(vec1);
        vec2.resize(size / n);
        fillVector(vec2);
        // TODO: Update log
        REPEATED_CLOCK_START;
        handler.forgetLast(vec1, vec2, n);
        REPEATED_CLOCK_END;
        for(int d : durations) {
            logger.Log("",n, k, d);
        }

    STEPLOOP_END

    END_TEST
}

void TestFactory::joinHandler(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("JoinHandler")

    JoinHandler jh;

    std::vector<size_t> vec1, vec1Copy, vec2;

    STEPLOOP_START

        vec1.resize(size);
        fillVector(vec1);
        vec2.resize(size);
        fillVector(vec2);
        vec1Copy = vec1;
        // TODO: Update log
        REPEATED_CLOCK_START;
        jh.join(vec1Copy, vec2);
        REPEATED_CLOCK_END;
        logger.Log("", n, k, duration);
        for(int d : durations) {
            logger.Log("", n, k, d);
        }

    STEPLOOP_END

    END_TEST
}

void TestFactory::InsertClosedForm(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("InsertClosedForm")

    CalculationRemapper remapper;

    std::vector<size_t> vec1, vec2;

    STEPLOOP_START

        vec1.resize(size);
        fillVector(vec1);
        vec2.resize(size);
        remapper.SetSizes(n, k);
        for(int pos = 0; pos < k - 1; pos++) {
            REPEATED_CLOCK_START;
            remapper.Insert(vec1, vec2, pos);
            REPEATED_CLOCK_END;
            for(int d : durations) {
                logger.Log("", n, k, d);
            }
        }

    STEPLOOP_END

    END_TEST
}

void TestFactory::ExtractClosedForm(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("ExtractClosedForm")

    CalculationRemapper remapper;

    std::vector<size_t> vec1, vec2;

    STEPLOOP_START

        vec1.resize(size);
        fillVector(vec1);
        vec2.resize(size);
        remapper.SetSizes(n, k);
        for(int pos = 0; pos < k - 1; pos++) {
            REPEATED_CLOCK_START;
            remapper.Extract(vec1, vec2, pos);
            REPEATED_CLOCK_END;
            for(int d : durations) {
                logger.Log("", n, k, pos, d);
            }
        }

    STEPLOOP_END

    END_TEST
}

void TestFactory::InsertIterator(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("InsertIterator")

    IteratorRemapper remapper;

    std::vector<size_t> vec1, vec2;

    STEPLOOP_START

        vec1.resize(size);
        fillVector(vec1);
        vec2.resize(size);
        remapper.SetSizes(n, k);
        for(int pos = 0; pos < k - 1; pos++) {
            REPEATED_CLOCK_START;
            remapper.Insert(vec1, vec2, pos);
            REPEATED_CLOCK_END;
            for(int d : durations) {
                logger.Log("", n, k, pos, d);
            }
        }

    STEPLOOP_END

    END_TEST
}

void TestFactory::ExtractIterator(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("ExtractIterator")

    IteratorRemapper remapper;

    std::vector<size_t> vec1, vec2;

    STEPLOOP_START

        vec1.resize(size);
        fillVector(vec1);
        vec2.resize(size);
        remapper.SetSizes(n, k);
        for(int pos = 0; pos < k - 1; pos++) {
            REPEATED_CLOCK_START;
            remapper.Extract(vec1, vec2, pos);
            REPEATED_CLOCK_END;
            for(int d : durations) {
                logger.Log("", n, k, pos, d);
            }
        }

    STEPLOOP_END

    END_TEST
}

void TestFactory::MaxDegreeHomomorphismCount(TestSettings &settings, TestLogger &logger) {
    BEGIN_TEST("MaxDegreeHomomorphismCount");
    
    std::shared_ptr<EdgeSetGraph> h = std::make_shared<EdgeSetGraph>(0);
    GraphGenerator::Cycle(h, 4);
    
    std::shared_ptr<EdgeSetGraph> g = std::make_shared<EdgeSetGraph>(0);
    
    for(int n = 2; n < 65; n = n*2) {
        GraphGenerator::CompleteGrid(g, n, n);
        REPEATED_CLOCK_START;
        TraversalHomomorphismCounter::Count(h, g);
        REPEATED_CLOCK_END;
        
        for(int i = 1; i < durations.size(); i++) {
            logger.Log("SquareInGrid", n*n, 4, durations[i]);
        }
    }
    
    END_TEST;
}

int TestFactory::milliSecondDifferene(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> stop) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}

void TestFactory::fillVector(std::vector<size_t> data) {
    for(auto & entry : data) {
        entry = rand();
    }
}

float TestFactory::averageDuration(std::vector<int> durations)
{
    float sum = 0;
    for(int i = 0 ; i <durations.size(); i++) {
        sum += durations[i];
    }
    return sum / durations.size();
}

//
//  test_factory.cpp
//  test
//
//  Created by Jonas Mortensen on 26/02/2020.
//

#include <stdio.h>
#include "test/test_factory.h"
#include "test/test.h"
#include "homomorphism/tamaki-2017.h"
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/nice_tree_decomposition.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/main.h"
#include "test/graph_generator.h"
#include <memory>

std::unique_ptr<Test> TestFactory::GetTest(int i) {
    switch (i) {
        case 0: {
            return std::unique_ptr<Test>(new Test("Square in grid2", "", Test0));
        }
        case 1: {
            return std::unique_ptr<Test>(new Test("Square in grid4", "", Test1));
        }
        case 2: {
            return std::unique_ptr<Test>(new Test("Square in grid8", "", Test2));
        }
        case 3: {
            return std::unique_ptr<Test>(new Test("Square in grid16", "", Test3));
        }
        case 4: {
            return std::unique_ptr<Test>(new Test("Square in coinFlip128", "", Test4));
        }
    }
    return nullptr;
}

void TestFactory::Test0()
{
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    Tamaki2017 t;
    std::shared_ptr<TreeDecomposition> td = t.decompose(g);
}

void TestFactory::Test1()
{
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(g, 4, 4);
    
    Main::subgraphsGraph(h, g);
}

void TestFactory::Test2()
{
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(g, 8, 8);
    
    Main::subgraphsGraph(h, g);
}

void TestFactory::Test3()
{
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(g, 16, 16);
    
    Main::subgraphsGraph(h, g);
}

void TestFactory::Test4()
{
    std::shared_ptr<AdjacencyMatrixGraph> h = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::CompleteGrid(h, 2, 2);
    
    std::shared_ptr<AdjacencyMatrixGraph> g = AdjacencyMatrixGraph::testGraph();
    GraphGenerator::EdgeProbabilityGraph(g, 128, 0.5);
    
    Main::subgraphsGraph(h, g);
}

int TestFactory::TestCount() {
    return 5;
}

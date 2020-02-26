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

Test TestFactory::GetTest(int i) {
    switch (i) {
        case 0: {
            Test t0("Square in Square", "", Test0);
            return t0;
            break;
        }
        case 1: {
            Test t1("Square in grid", "", Test1);
            return t1;
            break;
        }
    }
    throw "Unknown test requested";
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

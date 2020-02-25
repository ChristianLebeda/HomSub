#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "test/graph_generator.h"
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    std::shared_ptr<AdjacencyMatrixGraph> g = std::make_shared<AdjacencyMatrixGraph>(1);

    
    GraphGenerator gg;
    gg.RandomConnectedGraph(g, 10, 20);
    
    g->prettyPrint(std::cout);
    //std::shared_ptr<Graph> g = AdjacencyMatrixGraph::testGraph();
    
    return 0;
}

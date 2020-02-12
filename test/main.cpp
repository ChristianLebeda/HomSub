#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<Graph> g = AdjacencyMatrixGraph::testGraph();

    g->prettyPrint(std::cout);
    
    return 0;
}

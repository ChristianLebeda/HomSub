#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "test/graph_generator.h"

int main(int argc, char *argv[])
{
    
    std::shared_ptr<AdjacencyMatrixGraph> square = std::make_shared<AdjacencyMatrixGraph>(1);
    
    GraphGenerator::CompleteGrid(square, 2, 2);
    //std::shared_ptr<Graph> g = AdjacencyMatrixGraph::testGraph();

    square->prettyPrint(std::cout);
    
    return 0;
}

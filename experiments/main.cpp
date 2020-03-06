#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "experiments/graph_generator.h"
#include <time.h>
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/tamaki-2017.h"
#include "homomorphism/main.h"

int main(int argc, char *argv[])
{
    //srand(time(NULL));
    
    //std::shared_ptr<AdjacencyMatrixGraph> g = std::make_shared<AdjacencyMatrixGraph>(1);

    std::shared_ptr<Graph> g = AdjacencyMatrixGraph::testGraph();

    auto sp = Main::decomposedSpasmFromGraph(g);

    std::cout << sp->serialize() << std::endl;

    //GraphGenerator gg;
    //gg.RandomConnectedGraph(g, 10, 20);
    
    //g->prettyPrint(std::cout);
    //std::shared_ptr<Graph> g = AdjacencyMatrixGraph::testGraph();
    
    return 0;
}

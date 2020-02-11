#include <iostream>
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/tree_width_solver.h"
#include "homomorphism/tamaki-2017.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<AdjacencyMatrixGraph> a = AdjacencyMatrixGraph::fromGraph6("This is graph6");
    TreeWidthSolver *tws = new Tamaki2017();
    //tws->decompose(a);
    
    return 0;
}

#include <iostream>
#include <set>
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/tree_width_solver.h"
#include "homomorphism/tamaki-2017.h"
#include "homomorphism/nice_tree_decomposition.h"

int main(int argc, char *argv[])
{
    //std::shared_ptr<AdjacencyMatrixGraph> a = AdjacencyMatrixGraph::fromGraph6("This is graph6");
    //TreeWidthSolver *tws = new Tamaki2017();
    //tws->decompose(a);
    
    
    std::shared_ptr<AdjacencyMatrixGraph> graph = AdjacencyMatrixGraph::fromFile("test.gr");
    
    graph->prettyPrint(std::cout);
    
    Tamaki2017 t;
    std::shared_ptr<TreeDecomposition> td = t.decompose(graph);
    
    std::shared_ptr<NiceTreeDecomposition> ntd = NiceTreeDecomposition::FromTd(td);
    
    return 0;
}

#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/tree_width_solver.h"
#include "homomorphism/tamaki-2017.h"

int main(int argc, char *argv[])
{
    
    std::shared_ptr<Graph> a = Graph::fromGraph6("This is graph6");
    std::shared_ptr<Graph> b = Graph::fromFile("This is a path");
    std::cout << a->edgeCount() << std::endl;
    std::cout << a->isIsomorphic(b) << std::endl;
    
    TreeWidthSolver *tws = new Tamaki2017();
    tws->decompose(a);
    
    return 0;
}

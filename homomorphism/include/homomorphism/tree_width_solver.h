#ifndef HOMOMORPHISM_TREE_WIDTH_SOLVER_h
#define HOMOMORPHISM_TREE_WIDTH_SOLVER_h

#include <memory>
#include <string>

#include "homomorphism/graph.h"
#include "homomorphism/tree_decomposition.h"

class TreeWidthSolver
{
public:
    virtual std::shared_ptr<TreeDecomposition> decompose(std::shared_ptr<Graph> g) = 0;
};

#endif 

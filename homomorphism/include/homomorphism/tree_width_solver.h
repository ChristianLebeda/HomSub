//
//  tree_width_solver.h
//  homomorphism
//
//  Created by Jonas Mortensen on 04/02/2020.
//

#ifndef HOMOMORPHISM_TREE_WIDTH_SOLVER_h
#define HOMOMORPHISM_TREE_WIDTH_SOLVER_h

#include <string>
#include <memory>
#include "graph.h"
#include "tree_decomposition.h"

class TreeWidthSolver
{
public:
    virtual std::shared_ptr<TreeDecomposition> decompose(std::shared_ptr<Graph> g) = 0;
};

#endif /* tree_width_solver_h */

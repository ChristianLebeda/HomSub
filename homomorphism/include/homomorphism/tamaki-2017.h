//
//  tamaki-2017.h
//  homomorphism
//
//  Created by Jonas Mortensen on 04/02/2020.
//

#ifndef TAMAKI_2017_h
#define TAMAKI_2017_h

#include <string>
#include <memory>
#include "tree_width_solver.h"

class Tamaki2017 : public TreeWidthSolver
{
public:
    std::shared_ptr<TreeDecomposition> decompose(std::shared_ptr<Graph> g);
};

#endif /* tamaki_2017_h */

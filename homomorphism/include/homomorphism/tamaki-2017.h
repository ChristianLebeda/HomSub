#ifndef HOMOMORPHISM_TAMAKI_2017_h
#define HOMOMORPHISM_TAMAKI_2017_h

#include "homomorphism/tree_width_solver.h"

#include <memory>
#include <string>

class Tamaki2017 : public TreeWidthSolver
{
public:
    std::shared_ptr<TreeDecomposition> decompose(std::shared_ptr<Graph> g);
};

#endif 

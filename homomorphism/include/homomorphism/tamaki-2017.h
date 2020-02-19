#ifndef TAMAKI_2017_h
#define TAMAKI_2017_h

#include "tree_width_solver.h"

#include <memory>
#include <string>

class Tamaki2017 : public TreeWidthSolver
{
public:
    std::shared_ptr<TreeDecomposition> decompose(std::shared_ptr<Graph> g);
};

#endif 

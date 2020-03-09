#ifndef HOMOMORPHISM_TAMAKIRUNNER_H
#define HOMOMORPHISM_TAMAKIRUNNER_H

#include "homomorphism/tree_width_solver.h"

class TamakiRunner : public TreeWidthSolver {
public:
    std::shared_ptr<TreeDecomposition> decompose(std::shared_ptr<Graph> g) override;
    std::vector<std::shared_ptr<TreeDecomposition>> decomposeAll(std::vector<std::shared_ptr<Graph>> g) override;
};

#endif

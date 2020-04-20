#ifndef HOMOMORPHISM_NICE_PATH_DECOMPOSITION_H
#define HOMOMORPHISM_NICE_PATH_DECOMPOSITION_H

#include <utility>

#include "homomorphism/tree_decomposition.h"

struct NPDNode {
    bool introduce;
    size_t vertex;
    //size_t index;
    //std::vector<size_t> bag;
};

class NicePathDecomposition
{
public:
    NicePathDecomposition(std::vector<NPDNode> decomp, size_t width) :
        decomposition_(std::move(decomp)), width_(width) {};
    static std::shared_ptr<NicePathDecomposition> FromTd(std::shared_ptr<TreeDecomposition> td);
    size_t getWidth();

    std::vector<NPDNode> decomposition_;
private:
    size_t width_;
};



#endif

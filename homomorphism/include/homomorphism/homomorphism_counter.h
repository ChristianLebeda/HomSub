#ifndef HOMOMORPHISM_HOMOMORPHISMCOUNTER_H_
#define HOMOMORPHISM_HOMOMORPHISMCOUNTER_H_

#include <memory>

#include "homomorphism/graph.h"
#include "homomorphism/nice_tree_decomposition.h"

struct DPState {
    std::vector<size_t> bag;
    std::vector<size_t> mappings;
};

class HomomorphismCounter
{
public:
    HomomorphismCounter(std::shared_ptr<Graph> h, std::shared_ptr<Graph> g,
        std::shared_ptr<NiceTreeDecomposition> tree) : h_(h), g_(g), tdc_(tree), n_(g->vertCount()) {};
    
    static std::shared_ptr<HomomorphismCounter> instantiate(std::shared_ptr<Graph> h,
        std::shared_ptr<Graph> g, std::shared_ptr<NiceTreeDecomposition> tree);

    size_t compute();
private:
    std::shared_ptr<Graph> h_, g_;
    std::shared_ptr<NiceTreeDecomposition> tdc_;
    size_t n_;
    // Return vertices in bag first and count of all mappings second.
    DPState computeRec(std::shared_ptr<NTDNode> node);
    DPState computeIntroduceRec(std::shared_ptr<NTDNode> child, size_t x);
    DPState computeForgetRec(std::shared_ptr<NTDNode> child, size_t x);
    DPState computeJoinRec(std::shared_ptr<NTDNode> child1, std::shared_ptr<NTDNode> child2);
};

#endif
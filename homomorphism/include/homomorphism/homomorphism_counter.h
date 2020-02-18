#ifndef HOMOMORPHISM_HOMOMORPHISMCOUNTER_H_
#define HOMOMORPHISM_HOMOMORPHISMCOUNTER_H_

#include <memory>
#include <homomorphism\graph.h>
#include <homomorphism\nice_tree_decomposition.h>

class HomomorphismCounter
{
public:
    HomomorphismCounter(std::shared_ptr<Graph> h, std::shared_ptr<Graph> g,
        std::shared_ptr<NiceTreeDecomposition> tree) : h_(h), g_(g), tdc_(tree) {};
    
    static std::shared_ptr<HomomorphismCounter> instantiate(std::shared_ptr<Graph> h,
        std::shared_ptr<Graph> g, std::shared_ptr<NiceTreeDecomposition> tree);

    size_t compute();
private:
    std::shared_ptr<Graph> h_, g_;
    std::shared_ptr<NiceTreeDecomposition> tdc_;
    // Return vertices in bag first and count of all mappings second.
    std::pair<std::vector<size_t>, std::vector<size_t>> computeRec(std::shared_ptr<NTDNode> node);
    std::pair<std::vector<size_t>, std::vector<size_t>> computeIntroduceRec(std::shared_ptr<NTDNode> child, size_t x);
    std::pair<std::vector<size_t>, std::vector<size_t>> computeForgetRec(std::shared_ptr<NTDNode> child, size_t x);
    std::pair<std::vector<size_t>, std::vector<size_t>> computeJoinRec(std::shared_ptr<NTDNode> child1, std::shared_ptr<NTDNode> child2);
};

#endif
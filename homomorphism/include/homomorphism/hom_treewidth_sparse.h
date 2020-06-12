#ifndef HOMOMORPHISM_HOM_TREEWIDTH_SPARSE_H
#define HOMOMORPHISM_HOM_TREEWIDTH_SPARSE_H

#include "homomorphism/homomorphism_counter_interface.h"

#include <memory>

#include "homomorphism/dpstate.h"
#include "homomorphism/nice_tree_decomposition.h"


class HomTreewidthSparse : public HomomorphismCounterInterface {
public:
    HomTreewidthSparse(std::shared_ptr<Graph>& h, std::shared_ptr<Graph>& g,
                       std::shared_ptr<NiceTreeDecomposition>& tree) :
                       h_(h), g_(g), tdc_(tree), n_(g->vertCount()){}

    long compute() override;
private:
    std::shared_ptr<Graph> h_, g_;
    std::shared_ptr<NiceTreeDecomposition> tdc_;
    size_t n_;

    DPState computeRec(const std::shared_ptr<NTDNode>& node, std::vector<size_t>& forgetStack);
    DPState computeIntroduceRec(const std::shared_ptr<NTDNode>& child, size_t x, std::vector<size_t>& forgetStack);
    DPState computeForgetRec(const std::shared_ptr<NTDNode>& child, size_t x, std::vector<size_t>& forgetStack);
    DPState computeJoinRec(const std::shared_ptr<NTDNode>& child1, const std::shared_ptr<NTDNode>& child2, std::vector<size_t>& forgetStack);
    std::vector<size_t>* Introduce(std::vector<size_t> & child, std::vector<size_t> & bag, std::vector<unsigned char>& connected, int k, int pos);
    std::vector<size_t>* Forget(std::vector<size_t> & child, int k);
    std::vector<size_t>* Join(std::vector<size_t> & child1, std::vector<size_t> & child2, int k);
    int Compare(std::vector<size_t>::iterator first, std::vector<size_t>::iterator last, std::vector<size_t>::iterator second);
};

#endif

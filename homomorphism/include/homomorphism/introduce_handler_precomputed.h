#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_PRECOMPUTED_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_PRECOMPUTED_H

#include <utility>

#include "homomorphism/introduce_handler_least.h"

#include "homomorphism/edge_consistency_precomputation.h"

class IntroduceHandlerPrecomputed : public IntroduceHandlerLeast {
public:
    IntroduceHandlerPrecomputed(std::shared_ptr<EdgeConsistencyPrecomputation> precomputed):
                                    precomputed_(std::move(precomputed)) {};
    std::vector<size_t>& introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                       std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                       std::shared_ptr<Graph> g, size_t n, size_t x) override;
private:
    std::shared_ptr<EdgeConsistencyPrecomputation> precomputed_;
};

#endif

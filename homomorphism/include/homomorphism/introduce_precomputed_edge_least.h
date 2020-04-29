#ifndef HOMOMORPHISM_INTRODUCE_PRECOMPUTED_EDGE_LEAST_H
#define HOMOMORPHISM_INTRODUCE_PRECOMPUTED_EDGE_LEAST_H

#include "homomorphism/introduce_handler.h"

#include "homomorphism/edge_consistency_precomputation.h"

class IntroducePrecomputedEdgeLeast : IntroduceHandler{
public:
    IntroducePrecomputedEdgeLeast(size_t n, size_t k, std::shared_ptr<EdgeConsistencyPrecomputation> precomputed) :
            IntroduceHandler(n, k), precomputed_(std::move(precomputed)) {};
    std::vector<size_t>& Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
                                   std::vector<unsigned char>& bag, size_t x, size_t idx) override;
private:
    std::shared_ptr<EdgeConsistencyPrecomputation> precomputed_;
};

#endif
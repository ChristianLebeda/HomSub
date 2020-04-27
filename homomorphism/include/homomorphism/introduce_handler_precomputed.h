#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_PRECOMPUTED_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_PRECOMPUTED_H

#include "homomorphism/introduce_handler.h"

#include "homomorphism/introduce_precomputed_edge_least.h"
#include "homomorphism/introduce_precomputed_least.h"
#include "homomorphism/introduce_precomputed_nonedge_least.h"

class IntroduceHandlerPrecomputed : public IntroduceHandler {
public:
    IntroduceHandlerPrecomputed(size_t n, size_t k,
            const std::shared_ptr<EdgeConsistencyPrecomputation>& precomputedLeast,
            const std::shared_ptr<EdgeConsistencyPrecomputation>& precomputedSecond)
                : IntroduceHandler(n, k), least_(IntroducePrecomputedLeast(n, k, precomputedLeast)),
                edge_(IntroducePrecomputedEdgeLeast(n, k, precomputedSecond)),
                nonedge_(IntroducePrecomputedNonedgeLeast(n, k, precomputedLeast)) { }
    std::vector<size_t>& Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
                                           std::vector<unsigned char>& bag, size_t x, size_t idx) override;
private:
    IntroducePrecomputedEdgeLeast edge_;
    IntroducePrecomputedNonedgeLeast nonedge_;
    IntroducePrecomputedLeast least_;
};

#endif

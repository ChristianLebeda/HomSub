#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_COMPUTE_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_COMPUTE_H

#include "homomorphism/introduce_handler_least.h"

class IntroduceHandlerCompute : public IntroduceHandlerLeast {
public:
    std::vector<size_t>& introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                               std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                               std::shared_ptr<Graph> g, size_t n, size_t x) override;
};

#endif

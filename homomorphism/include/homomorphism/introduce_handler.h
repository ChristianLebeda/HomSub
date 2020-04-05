#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_H

#include <vector>

#include "homomorphism/graph.h"

class IntroduceHandler {
public:
    // TODO: Could store variables to simplify function
    virtual std::vector<size_t>& introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                                   std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                                   std::shared_ptr<Graph> g, size_t n, size_t x) = 0;
};

#endif

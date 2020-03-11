#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_H

#include <vector>

#include "homomorphism/graph.h"

//TODO: If more techniques are added this will become abstract
class IntroduceHandler {
public:
    // TODO: Could store variables to simplify function
    std::vector<size_t>& introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                       std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                       std::shared_ptr<Graph> g, size_t n, size_t x);
};

#endif

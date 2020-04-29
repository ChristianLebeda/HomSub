#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_H

#include <vector>

#include "homomorphism/graph.h"
#include "homomorphism/bag_sizes.h"

class IntroduceHandler {
public:
    IntroduceHandler(size_t n, size_t k) : size_(BagSizes(n, k)) { }
    virtual std::vector<size_t>& Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
                                                   std::vector<unsigned char>& bag, size_t x, size_t idx) = 0;
protected:
    BagSizes size_;
};

#endif

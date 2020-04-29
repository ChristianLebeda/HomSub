#ifndef HOMOMORPHISM_FORGET_HANDLER_H
#define HOMOMORPHISM_FORGET_HANDLER_H

#include <vector>

#include "homomorphism/bag_sizes.h"

class ForgetHandler {
public:
    ForgetHandler(size_t n, size_t k) : size_(BagSizes(n, k)) { }
    virtual std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t b, size_t idx) = 0;

    void SetSizes(size_t n, size_t k) {
        size_ = BagSizes(n, k);
    }
protected:
    BagSizes size_;
};

#endif

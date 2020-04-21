#ifndef HOMOMORPHISM_FORGET_HANDLER_H
#define HOMOMORPHISM_FORGET_HANDLER_H

#include <vector>

class ForgetHandler {
public:
    ForgetHandler(size_t n, size_t k) : n_(n), k_(k), powers_(std::vector<size_t>(k + 1)) {
        powers_[0] = 1;
        for (size_t i = 1; i < powers_.size(); ++i) {
            powers_[i] = powers_[i - 1] * n_;
        }
    }
    virtual std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t b, size_t idx) = 0;

    void SetSizes(size_t n, size_t k) {
        n_ = n;
        k_ = k;
        powers_.resize(k_ + 1);
        powers_[0] = 1;
        for (size_t i = 1; i < powers_.size(); ++i) {
            powers_[i] = powers_[i - 1] * n_;
        }
    }
protected:
    size_t n_, k_;
    std::vector<size_t> powers_;
};

#endif

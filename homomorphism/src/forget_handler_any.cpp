#include "homomorphism/forget_handler_any.h"

std::vector<size_t>& ForgetHandlerAny::forget(std::vector<size_t> &input, std::vector<size_t> &output, size_t n) {
    // Since index and exponents are inverted. If this is changed this line should be removed.
    size_t pos = b_ - idx_ - 1;
    size_t xMax = powers_[pos];
    size_t yMax = powers_[b_ - pos - 1];
    size_t zMax = n_;

    size_t xOff = n_;
    size_t yOff = powers_[pos + 1];
    size_t zOff = powers_[pos];

    for(size_t & entry : output) {
        entry = 0;
    }

    for (size_t y = 0; y < yMax; ++y) {
        for (size_t x = 0; x < xMax; ++x) {
            for (size_t z = 0; z < zMax; ++z) {
                output[x + zOff * y] += input[x + yOff * y + zOff * z];
            }
        }
    }

    return output;
}

void ForgetHandlerAny::SetSizesAndIndex(size_t n, size_t b, size_t idx) {
    n_ = n;
    b_ = b;
    powers_.resize(b_ + 1);

    powers_[0] = 1;
    for (size_t i = 1; i < powers_.size(); ++i) {
        powers_[i] = powers_[i - 1] * n_;
    }

    idx_ = idx;
}

#include "homomorphism/calculation_remapper.h"

#include <iostream>

void CalculationRemapper::Extract(std::vector <size_t>& in, std::vector <size_t>& out, size_t pos) {
    // Since index and exponents are inverted. If this is changed this line should be removed.
    pos = b_ - pos - 1;
    size_t xMax = powers_[pos];
    size_t yMax = powers_[b_ - pos - 1];
    size_t zMax = n_;

    size_t xOff = n_;
    size_t yOff = powers_[pos + 1];
    size_t zOff = powers_[pos];

    //TODO: Try different orderings
    for (size_t y = 0; y < yMax; ++y) {
        for (size_t z = 0; z < zMax; ++z) {
            for (size_t x = 0; x < xMax; ++x) {
                // TODO: Store partial offsets?
                out[xOff * x + yOff * y + z] = in[x + yOff * y + zOff * z];
            }
        }
    }
}

void CalculationRemapper::Insert(std::vector<size_t>& in, std::vector <size_t>& out, size_t pos) {
    pos = b_ - pos - 1;
    size_t xMax = powers_[pos];
    size_t yMax = powers_[b_ - pos - 1];
    size_t zMax = n_;

    size_t xOff = n_;
    size_t yOff = powers_[pos + 1];
    size_t zOff = powers_[pos];

    //TODO: Try different orderings
    for (size_t y = 0; y < yMax; ++y) {
        for (size_t z = 0; z < zMax; ++z) {
            for (size_t x = 0; x < xMax; ++x) {
                // TODO: Store partial offsets?
                out[x + yOff * y + zOff * z] = in[xOff * x + yOff * y + z];
            }
        }
    }
}

void CalculationRemapper::SetSizes(size_t n, size_t b) {
    n_ = n;
    b_ = b;
    powers_.resize(b_ + 1);

    powers_[0] = 1;
    for (size_t i = 1; i < powers_.size(); ++i) {
        powers_[i] = powers_[i - 1] * n_;
    }
}

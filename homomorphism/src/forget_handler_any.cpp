#include "homomorphism/forget_handler_any.h"

std::vector<size_t>& ForgetHandlerAny::forget(std::vector<size_t> &input, std::vector<size_t> &output,
        size_t b, size_t idx) {
    // Since index and exponents are inverted. If this is changed this line should be removed.
    size_t pos = idx;
    size_t xMax = size_.sizes[pos];
    size_t yMax = size_.sizes[b - pos - 1];
    size_t zMax = size_.n;

    size_t xOff = size_.n;
    size_t yOff = size_.sizes[pos + 1];
    size_t zOff = size_.sizes[pos];

    for(size_t & entry : output) {
        entry = 0;
    }

    for (size_t y = 0; y < yMax; ++y) {
        for (size_t z = 0; z < zMax; ++z) {
            for (size_t x = 0; x < xMax; ++x) {
                output[x + zOff * y] += input[x + yOff * y + zOff * z];
            }
        }
    }

    return output;
}

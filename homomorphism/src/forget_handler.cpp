#include "homomorphism/forget_handler.h"

std::vector<size_t>& ForgetHandler::forgetLast(std::vector<size_t>& input, std::vector<size_t>& output, size_t n) {
    size_t offset = 0;

    for(size_t & i : output) {
        size_t result = 0;

        for(size_t j = 0; j < n; j++) {
            result += input[offset + j];
        }

        i = result;
        offset += n;
    }

    return output;
}


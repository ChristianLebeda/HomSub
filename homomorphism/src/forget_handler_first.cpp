#include "homomorphism/forget_handler_first.h"

std::vector<size_t>& ForgetHandlerFirst::forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t n) {
    for(size_t i = 0; i < output.size(); i++) {
        output[i] = input[i];
    }

    size_t offset = output.size();

    for(int i = 1; i < n; i++) {
        for (size_t idx = 0; idx < output.size(); idx++) {
            output[idx] += input[offset + idx];
        }
        offset += output.size();
    }

    return output;
}


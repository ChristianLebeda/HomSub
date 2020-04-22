#include "homomorphism/forget_handler_first.h"

#include <iostream>

std::vector<size_t>& ForgetHandlerFirst::forget(std::vector<size_t>& input, std::vector<size_t>& output,
                                                    size_t b, size_t idx) {
    if(idx != 0) {
        std::cerr << "ERROR: ForgetHandlerFirst called with index " << idx << std::endl;
        throw;
    }

    for(size_t i = 0; i < output.size(); i++) {
        output[i] = input[i];
    }

    size_t offset = output.size();

    for(int i = 1; i < n_; i++) {
        for (size_t idx = 0; idx < output.size(); idx++) {
            output[idx] += input[offset + idx];
        }
        offset += output.size();
    }

    return output;
}


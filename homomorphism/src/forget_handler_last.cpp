#include "homomorphism/forget_handler_last.h"

#include <iostream>

std::vector<size_t>& ForgetHandlerLast::forget(std::vector<size_t>& input, std::vector<size_t>& output,
                                               size_t b, size_t idx) {
    if(idx != 0) {
        std::cerr << "ERROR: ForgetHandlerLast called with index " << idx << " and bag size " << b << std::endl;
        throw;
    }

    size_t offset = 0;

    for(size_t & i : output) {
        size_t result = 0;

        for(size_t j = 0; j < size_.n; j++) {
            result += input[offset + j];
        }

        i = result;
        offset += size_.n;
    }

    return output;
}


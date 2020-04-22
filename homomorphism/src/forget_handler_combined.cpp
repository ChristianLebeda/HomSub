#include "homomorphism/forget_handler_combined.h"

std::vector<size_t>& ForgetHandlerCombined::forget(std::vector<size_t> &input, std::vector<size_t> &output,
                                                        size_t b, size_t idx) {
    if (idx == 0) {
        return first_.forget(input, output, b, idx);
    } else if (idx == b - 1) {
        return last_.forget(input, output, b, idx);
    } else {
        return any_.forget(input, output, b, idx);
    }
}

#include "homomorphism/introduce_handler_precomputed.h"

std::vector<size_t>& IntroduceHandlerPrecomputed::Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
        std::vector<unsigned char> &bag, size_t x, size_t idx) {
    if(idx == 0) {
        least_.Introduce(input, output, bag, x, idx);
    } else if(bag[0]) {
        edge_.Introduce(input, output, bag, x, idx);
    } else {
        nonedge_.Introduce(input, output, bag, x, idx);
    }
}


#ifndef HOMOMORPHISM_INTRODUCE_HANDLER_H
#define HOMOMORPHISM_INTRODUCE_HANDLER_H

#include <vector>

//TODO: If more techniques are added this will become abstract
class IntroduceHandler {
public:
    std::vector<size_t>& introduceLast(std::vector<size_t>& input, std::vector<size_t>& output, std::vector<size_t>& bag, size_t n);
};

#endif

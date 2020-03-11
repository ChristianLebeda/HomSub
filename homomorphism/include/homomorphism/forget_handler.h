#ifndef HOMOMORPHISM_FORGET_HANDLER_H
#define HOMOMORPHISM_FORGET_HANDLER_H

#include <vector>

//TODO: If more techniques are added this will become abstract
class ForgetHandler {
public:
    std::vector<size_t>& forgetLast(std::vector<size_t>& input, std::vector<size_t>& output, size_t n);
};

#endif

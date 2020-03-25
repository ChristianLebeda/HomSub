#ifndef HOMOMORPHISM_FORGET_HANDLER_H
#define HOMOMORPHISM_FORGET_HANDLER_H

#include <vector>

class ForgetHandler {
public:
    virtual std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t n) = 0;
};

#endif

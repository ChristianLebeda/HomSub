#ifndef HOMOMORPHISM_FORGET_HANDLER_FIRST_H
#define HOMOMORPHISM_FORGET_HANDLER_FIRST_H

#include "homomorphism/forget_handler.h"

class ForgetHandlerFirst : public ForgetHandler {
public:
    ForgetHandlerFirst(size_t n, size_t k) : ForgetHandler(n, k) {}
    std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t b, size_t idx) override;
};

#endif
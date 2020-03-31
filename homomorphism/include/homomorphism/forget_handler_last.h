#ifndef HOMOMORPHISM_FORGET_HANDLER_LAST_H
#define HOMOMORPHISM_FORGET_HANDLER_LAST_H

#include "homomorphism/forget_handler.h"

class ForgetHandlerLast : public ForgetHandler {
public:
    std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t n) override;
};

#endif

#ifndef HOMOMORPHISM_FORGET_HANDLER_ANY_H
#define HOMOMORPHISM_FORGET_HANDLER_ANY_H

#include "homomorphism/forget_handler.h"

class ForgetHandlerAny : public ForgetHandler {
public:
    void SetSizesAndIndex(size_t n, size_t b, size_t idx);
    std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t n) override;
private:
    size_t n_, b_, idx_;
    std::vector<size_t> powers_;
};


#endif

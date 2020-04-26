#ifndef HOMOMORPHISM_FORGET_HANDLER_COMBINED_H
#define HOMOMORPHISM_FORGET_HANDLER_COMBINED_H

#include "homomorphism/forget_handler_any.h"
#include "homomorphism/forget_handler_first.h"
#include "homomorphism/forget_handler_last.h"

class ForgetHandlerCombined : public ForgetHandler {
public:
    ForgetHandlerCombined(size_t n, size_t k) : ForgetHandler(n, k), any_(ForgetHandlerAny(n, k)),
                    last_(ForgetHandlerFirst(n, k)), first_(ForgetHandlerLast(n, k)) {}
    std::vector<size_t>& forget(std::vector<size_t>& input, std::vector<size_t>& output, size_t b, size_t idx) override;
private:
    ForgetHandlerAny any_;
    ForgetHandlerLast first_;
    ForgetHandlerFirst last_;
};

#endif

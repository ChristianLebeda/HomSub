#ifndef HOMOMORPHISM_ITERATOR_INTRODUCE_HANDLER_H
#define HOMOMORPHISM_ITERATOR_INTRODUCE_HANDLER_H

#include "homomorphism/introduce_handler.h"

class IteratorIntroduceHandler : public IntroduceHandler {
public:
    std::vector<size_t>& introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                               std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                               std::shared_ptr<Graph> g, size_t n, size_t x) override;
};

#endif

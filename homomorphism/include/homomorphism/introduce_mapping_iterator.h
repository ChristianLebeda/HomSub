#ifndef HOMOMORPHISM_INTRODUCE_MAPPING_ITERATOR_H
#define HOMOMORPHISM_INTRODUCE_MAPPING_ITERATOR_H

#include <vector>

class IntroduceMappingIterator {
public:
    IntroduceMappingIterator(size_t n, size_t k, std::vector<size_t> offsets):
    n_(n), k_(k), offsets_(std::move(offsets)), current_(0), mapping_(std::vector<size_t> (k, 0)) {}

    static IntroduceMappingIterator Initialize(size_t n, size_t k, std::vector<bool> edges);

    bool NextChanged();
    size_t CurrentOffset();
private:
    size_t n_, k_, current_;
    std::vector<size_t> offsets_, mapping_;
};

#endif

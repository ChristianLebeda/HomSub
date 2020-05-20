#ifndef HOMOMORPHISM_INTRODUCE_MAPPING_ITERATOR_H
#define HOMOMORPHISM_INTRODUCE_MAPPING_ITERATOR_H

#include <vector>

class IntroduceMappingIterator {
public:
    IntroduceMappingIterator(size_t n, size_t k, std::vector<size_t> offsets):
    n_(n), k_(k), offsets_(std::move(offsets)), current_(0), mapping_(std::vector<size_t> (k, 0)) {}

    static IntroduceMappingIterator InitializeLeast(size_t n, size_t k, std::vector<unsigned char> edges);
    static IntroduceMappingIterator InitializeSecond(size_t n, size_t k, std::vector<unsigned char> edges);
    static IntroduceMappingIterator InitializeInputIterator(size_t n, size_t k, size_t pos);
    static IntroduceMappingIterator InitializePrecomputedSecond(size_t n, std::vector<unsigned char> edges, size_t pos);
    static IntroduceMappingIterator InitializePrecomputedNonedge(size_t n, std::vector<unsigned char> edges, size_t pos);

    bool NextChanged();
    size_t CurrentOffset();
    std::vector<size_t> mapping_;
private:
    size_t n_, k_, current_;
    std::vector<size_t> offsets_;
};

#endif

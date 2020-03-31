#ifndef HOMOMORPHISM_MAPPING_ITERATOR_H
#define HOMOMORPHISM_MAPPING_ITERATOR_H

#include <vector>

class MappingIterator
{
public:
    MappingIterator(int n, int k) : n_(n), mapping(std::vector<size_t>(k, 0)) {}

    std::vector<size_t> mapping;
    size_t idx = 0;

    void Increment();
private:
    size_t n_;
};


#endif

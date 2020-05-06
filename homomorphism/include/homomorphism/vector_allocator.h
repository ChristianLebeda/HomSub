#ifndef HOMOMORPHISM_VECTOR_ALLOCATOR_H
#define HOMOMORPHISM_VECTOR_ALLOCATOR_H

#include <vector>

#include "bag_sizes.h"

class VectorAllocator {
public:
    VectorAllocator(BagSizes size) : size_(size) {};
    virtual std::vector<size_t>* Allocate(size_t b) = 0;
    virtual void Free(std::vector<size_t> *vector, size_t bagSize) = 0;
protected:
    BagSizes size_;
};

#endif

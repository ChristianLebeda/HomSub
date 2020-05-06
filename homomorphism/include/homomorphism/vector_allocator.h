#ifndef HOMOMORPHISM_VECTOR_ALLOCATOR_H
#define HOMOMORPHISM_VECTOR_ALLOCATOR_H

#include <vector>

#include "bag_sizes.h"

// Can be extended for caching
class VectorAllocator {
public:
    VectorAllocator(BagSizes size) : size_(size) {};
    std::vector<size_t>* Allocate(size_t b);
    std::vector<size_t>* AllocateInitial();
    void Free(std::vector<size_t> *vector, size_t bagSize);
private:
    BagSizes size_;
};

#endif

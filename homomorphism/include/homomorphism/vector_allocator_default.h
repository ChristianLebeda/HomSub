#ifndef HOMOMORPHISM_VECTOR_ALLOCATOR_DEFAULT_H
#define HOMOMORPHISM_VECTOR_ALLOCATOR_DEFAULT_H

#include "homomorphism/vector_allocator.h"

class VectorAllocatorDefault : public VectorAllocator {
public:
    VectorAllocatorDefault(BagSizes size) : VectorAllocator(size) {};
    std::vector<size_t>* Allocate(size_t b) override;
    void Free(std::vector<size_t> *vector, size_t bagSize) override;
};

#endif
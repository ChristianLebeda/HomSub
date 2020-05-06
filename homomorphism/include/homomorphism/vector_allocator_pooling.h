#ifndef HOMOMORPHISM_VECTOR_ALLOCATOR_POOLING_H
#define HOMOMORPHISM_VECTOR_ALLOCATOR_POOLING_H

#include "homomorphism/vector_allocator.h"

#include <iostream>

class VectorAllocatorPooling : public VectorAllocator {
public:
    VectorAllocatorPooling(BagSizes size) : VectorAllocator(size),
        pool_(std::vector<std::vector<std::vector<size_t>*>>(size.k + 2)) {};
    ~VectorAllocatorPooling() {
        for(auto & pool : pool_) {
            for(auto & state : pool) {
                delete state;
            }
        }
    };
    std::vector<size_t>* Allocate(size_t b) override;
    void Free(std::vector<size_t> *vector, size_t bagSize) override;
private:
    std::vector<std::vector<std::vector<size_t>*>> pool_;
};

#endif

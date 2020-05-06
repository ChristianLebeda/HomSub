#include "homomorphism/vector_allocator_pooling.h"

std::vector<size_t> * VectorAllocatorPooling::Allocate(size_t b) {
    if(!pool_[b].empty()) {
        auto back = pool_[b].back();
        pool_[b].pop_back();
        return back;
    } else {
        return new std::vector<size_t>(size_.sizes[b]);
    }
}

void VectorAllocatorPooling::Free(std::vector<size_t> *vector, size_t bagSize) {
    pool_[bagSize].push_back(vector);
}


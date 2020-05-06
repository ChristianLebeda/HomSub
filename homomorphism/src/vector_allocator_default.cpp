#include "homomorphism/vector_allocator_default.h"

std::vector<size_t>* VectorAllocatorDefault::Allocate(size_t b) {
    return new std::vector<size_t>(size_.sizes[b]);
}

void VectorAllocatorDefault::Free(std::vector<size_t>* vector, size_t bagsize) {
    delete vector;
}

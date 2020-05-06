#include "homomorphism/vector_allocator.h"

#include <iostream>

std::vector<size_t>* VectorAllocator::Allocate(size_t b) {
    return new std::vector<size_t>(size_.sizes[b]);
}

void VectorAllocator::Free(std::vector<size_t>* vector, size_t bagsize) {
    delete vector;
}

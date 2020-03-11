#include "homomorphism/vector_allocator.h"

void VectorAllocator::setSize(size_t n, size_t width) {
    sizes_ = std::vector<size_t>(width + 2);

    sizes_[0] = 1;

    for (size_t i = 1; i < sizes_.size(); ++i) {
        sizes_[i] = sizes_[i - 1] * n;
    }
}

std::vector<size_t> VectorAllocator::get(size_t b) {
    return std::vector<size_t>(sizes_[b]);
}

void VectorAllocator::free(std::vector<size_t> &vector, size_t b) {}
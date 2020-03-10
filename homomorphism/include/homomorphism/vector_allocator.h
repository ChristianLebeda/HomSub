#ifndef HOMOMORPHISM_VECTOR_ALLOCATOR_H
#define HOMOMORPHISM_VECTOR_ALLOCATOR_H

#include <vector>

// Can be extended for caching
class VectorAllocator {
public:
    void setSize(size_t n, size_t width);
    std::vector<size_t> get(size_t b);
    void free(std::vector<size_t>& vector, size_t b);
private:
    std::vector<size_t> sizes_;
};

#endif

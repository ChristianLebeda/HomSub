#ifndef HOMOMORPHISM_MAPPING_ITERATOR_H_
#define HOMOMORPHISM_MAPPING_ITERATOR_H_

#include <memory>
#include <utility>
#include <vector>

class MappingIterator
{
public:
    MappingIterator(size_t n, size_t k, std::vector<size_t> offsets):
            n_(n), k_(k), offsets_(std::move(offsets)), current_(0), mapping_(std::vector<size_t> (k, 0)) {}

    static MappingIterator ExtractIterator(size_t n, size_t k, size_t pos);
    static MappingIterator InsertIterator(size_t n, size_t k, size_t pos);
    static MappingIterator CustomIterator(size_t n, size_t k, std::vector<size_t> offsets);

    size_t next();
private:
    size_t n_, k_, current_;
    std::vector<size_t> offsets_, mapping_;
};

#endif

#include "homomorphism/iterator_remapper.h"

#include <iostream>

#include "homomorphism/remapping_iterator.h"

void IteratorRemapper::Extract(std::vector <size_t>& in, std::vector <size_t>& out, size_t pos) {
    RemappingIterator it = RemappingIterator::ExtractIterator(n_, b_, pos);

    for(auto& e : in) {
        out[it.next()] = e;
    }
}

void IteratorRemapper::Insert(std::vector <size_t>& in, std::vector <size_t>& out, size_t pos) {
    RemappingIterator it = RemappingIterator::InsertIterator(n_, b_, pos);

    for(auto& e : in) {
        out[it.next()] = e;
    }
}

void IteratorRemapper::SetSizes(size_t n, size_t b) {
    n_ = n;
    b_ = b;
}

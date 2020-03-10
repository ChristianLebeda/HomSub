#include "homomorphism/iterator_remapper.h"

#include <iostream>

void IteratorRemapper::Extract(std::vector <size_t>& in, std::vector <size_t>& out, size_t pos) {
    std::cerr << "ERROR: IteratorRemapper::Extract not implemented yet" << std::endl;
}

void IteratorRemapper::Insert(std::vector <size_t>& in, std::vector <size_t>& out, size_t pos) {
    std::cerr << "ERROR: IteratorRemapper::Insert not implemented yet" << std::endl;
}

void IteratorRemapper::SetSizes(size_t n, size_t b) {
    n_ = n;
    b_ = b;
}

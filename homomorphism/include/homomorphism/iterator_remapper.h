#ifndef HOMOMORPHISM_ITERATOR_REMAPPER_H
#define HOMOMORPHISM_ITERATOR_REMAPPER_H

#include "homomorphism/remapper.h"

class IteratorRemapper : public Remapper {
public:
    void Extract(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos) override;
    void Insert(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos) override;
};

#endif

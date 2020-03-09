#ifndef HOMOMORPHISM_CALCULATION_REMAPPER_H
#define HOMOMORPHISM_CALCULATION_REMAPPER_H

#include "homomorphism/remapper.h"

class CalculationRemapper : public Remapper {
public:
    void SetSizes(size_t n, size_t b) override;
    void Extract(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos) override;
    void Insert(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos) override;
private:
    size_t n_, b_;
    std::vector<size_t> powers_;
};

#endif

#ifndef HOMOMORPHISM_CALCULATION_REMAPPER_H
#define HOMOMORPHISM_CALCULATION_REMAPPER_H

#include "homomorphism/remapper.h"

class CalculationRemapper : public Remapper {
public:
    void Extract(std::vector<size_t> in, std::vector<size_t> out, size_t pos);
    void Insert(std::vector<size_t> in, std::vector<size_t> out, size_t pos);
};

#endif

#ifndef HOMOMORPHISM_CALCULATION_REMAPPER_EXTRACT_VARIANTS_H
#define HOMOMORPHISM_CALCULATION_REMAPPER_EXTRACT_VARIANTS_H

#include <vector>

class CalculationRemapperExtractVarients {
public:
    void SetSizes(size_t n, size_t b);
    void ExtractXYZ(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void ExtractXZY(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void ExtractYXZ(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void ExtractYZX(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void ExtractZXY(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void ExtractZYX(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
private:
    size_t n_, b_;
    std::vector<size_t> powers_;
};

#endif

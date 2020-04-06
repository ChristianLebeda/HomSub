#ifndef HOMOMORPHISM_CALCULATION_REMAPPER_INSERT_VARIANTS_H
#define HOMOMORPHISM_CALCULATION_REMAPPER_INSERT_VARIANTS_H

#include <vector>

class CalculationRemapperInsertVarients {
public:
    void SetSizes(size_t n, size_t b);
    void InsertXYZ(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void InsertXZY(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void InsertYXZ(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void InsertYZX(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void InsertZXY(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
    void InsertZYX(std::vector<size_t>& in, std::vector<size_t>& out, size_t pos);
private:
    size_t n_, b_;
    std::vector<size_t> powers_;
};

#endif

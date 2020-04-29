#ifndef HOMOMORPHISM_BAG_SIZES_H
#define HOMOMORPHISM_BAG_SIZES_H

#include <vector>

class BagSizes {
public:
    BagSizes(size_t n, size_t k) : n(n), k(k), sizes(std::vector<size_t>(k + 1)) {
        sizes[0] = 1;
        for (size_t i = 1; i < sizes.size(); ++i) {
            sizes[i] = sizes[i - 1] * n;
        }
    }
    size_t n, k;
    std::vector<size_t> sizes;
};

#endif

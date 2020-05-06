#ifndef HOMOMORPHISM_DPSTATE_H
#define HOMOMORPHISM_DPSTATE_H

#include <vector>

// Stores the state of the treewidth based algorithm
// The bag is stored in ascending order of significance
struct DPState {
    std::vector<size_t> bag;
    std::vector<size_t>* mappings;
};

#endif

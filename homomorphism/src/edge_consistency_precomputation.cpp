#include "homomorphism/edge_consistency_precomputation.h"

std::shared_ptr<EdgeConsistencyPrecomputation> EdgeConsistencyPrecomputation::Initialize(std::shared_ptr<Graph> g, int maxEdges) {
    std::vector<std::vector<unsigned char>> storage;
    size_t n = g->vertCount();

    std::vector<unsigned char> prev(n, 1), current;
    storage.push_back(prev);

    //TODO: Might be better to use iterators to avoid copying
    for(int e = 0; e < maxEdges; e++) {
        current = std::vector<unsigned char>(prev.size() * n);
        auto it = current.begin();

        for(int idx = 0; idx < n; idx++) {
            for(int i = 0; i < prev.size(); i++) {
                *(it++) = prev[i] * g->edgeExist(idx, i % n);
            }
        }
        storage.push_back(current);
        prev = current;
    }

    return std::make_shared<EdgeConsistencyPrecomputation>(storage);
}

std::vector<unsigned char>::iterator EdgeConsistencyPrecomputation::GetIterator(size_t edges) {
    return storage_[edges].begin();
}

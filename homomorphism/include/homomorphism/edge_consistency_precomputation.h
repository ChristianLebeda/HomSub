#ifndef HOMOMORPHISM_EDGE_CONSISTENCY_PRECOMPUTATION_H
#define HOMOMORPHISM_EDGE_CONSISTENCY_PRECOMPUTATION_H

#include "homomorphism/graph.h"

#include <utility>
#include <vector>

//TODO: Should initialize using G and max number of edges. Should store vectors and return reference based on index
class EdgeConsistencyPrecomputation {
public:
    explicit EdgeConsistencyPrecomputation(std::vector<std::vector<unsigned char>> storage) : storage_(std::move(storage)) {}

    static std::shared_ptr<EdgeConsistencyPrecomputation> InitializeLeast(std::shared_ptr<Graph> g, int maxEdges);
    static std::shared_ptr<EdgeConsistencyPrecomputation> InitializeSecond(std::shared_ptr<Graph> g, int maxEdges);

    std::vector<unsigned char>::iterator GetIterator(size_t edges);
private:
    std::vector<std::vector<unsigned char>> storage_;
};

#endif

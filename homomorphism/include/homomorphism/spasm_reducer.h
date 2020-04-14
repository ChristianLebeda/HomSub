#ifndef HOMOMORPHISM_SPASM_REDUCER_H
#define HOMOMORPHISM_SPASM_REDUCER_H

#include "homomorphism/graph.h"

#include <memory>
#include <unordered_map>
#include <vector>

struct SpasmEntry
{
    std::shared_ptr<Graph> graph;
    int coefficient;
};

struct NautyEntry
{
    std::string graph;
    size_t n;
    int coefficient;
    bool operator<(const NautyEntry& rhs) const {
        return graph < rhs.graph;
    }
};

class SpasmReducer {
public:
    virtual std::vector<SpasmEntry> joinIsomorphic(std::unordered_map<std::string, int>& entries) = 0;
};

#endif

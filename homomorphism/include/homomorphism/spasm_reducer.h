#ifndef HOMOMORPHISM_SPASM_REDUCER_H
#define HOMOMORPHISM_SPASM_REDUCER_H

#include "homomorphism/graph.h"

#include <memory>
#include <vector>

struct SpasmEntry
{
    std::shared_ptr<Graph> graph;
    int coefficient;
};

class SpasmReducer {
public:
    virtual std::vector<SpasmEntry> joinIsomorphic(const std::vector<SpasmEntry>& spasm) = 0;
};

#endif

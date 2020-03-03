#ifndef HOMOMORPHISM_NAUTY_H
#define HOMOMORPHISM_NAUTY_H

#include <memory>
#include <string>
#include <vector>

#include "homomorphism/pipe_handler.h"
#include "homomorphism/spasm.h"

struct CanonicalEntry
{
    std::string graph;
    size_t n;
    int coefficient;
    bool operator<(const CanonicalEntry& rhs) const {
        return graph < rhs.graph;
    }
};

class Nauty
{
public:
    static void Test(std::vector<SpasmEntry> spasm);
    static std::vector<SpasmEntry> joinIsomorphic(const std::vector<SpasmEntry>& spasm);
};


#endif


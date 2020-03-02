#ifndef HOMOMORPHISM_NAUTY_H
#define HOMOMORPHISM_NAUTY_H

#include <memory>
#include <string>
#include <vector>

#include "homomorphism/spasm.h"

struct CanonicalEntry
{
    std::string graph;
    int coefficient;
};

class Nauty
{
public:
    static void Test(std::vector<SpasmEntry> spasm);
};


#endif


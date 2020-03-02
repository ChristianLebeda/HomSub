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
    int coefficient;
};

class Nauty
{
public:
    static void Test(std::vector<SpasmEntry> spasm);
private:
    static std::string compute(std::shared_ptr<Graph> g, PipeHandler& n);
};


#endif


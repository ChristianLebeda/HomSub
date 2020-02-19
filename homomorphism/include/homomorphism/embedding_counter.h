#ifndef HOMOMORPHISM_EMBEDDINGCOUNTER_H_
#define HOMOMORPHISM_EMBEDDINGCOUNTER_H_

#include <memory>

#include "homomorphism/graph.h"

class EmbeddingCounter
{
public:
    virtual size_t compute() = 0;
};

#endif

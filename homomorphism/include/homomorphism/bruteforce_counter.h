#ifndef HOMOMORPHISM_BRUTEFORCECOUNTER_H_
#define HOMOMORPHISM_BRUTEFORCECOUNTER_H_

#include "homomorphism/embedding_counter.h"

class BruteforceCounter : EmbeddingCounter
{
public:
    BruteforceCounter(std::shared_ptr<Graph> h, std::shared_ptr<Graph> g) 
        : h_(h), g_(g), k_(h->vertCount()), n_(g_->vertCount()) { }

    size_t compute() override;
private:
    std::shared_ptr<Graph> h_, g_;
    size_t k_, n_;

    void countRecursive(int* mapping, bool* used, int idx, int& count);
    bool checkIsEmbedding(int* mapping);
};

#endif

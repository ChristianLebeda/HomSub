#ifndef HOMOMORPHISM_PATHDECOMPOSITION_COUNTER_H
#define HOMOMORPHISM_PATHDECOMPOSITION_COUNTER_H

#include "homomorphism/forget_handler_any.h"
#include "homomorphism/introduce_handler_least.h"
#include "homomorphism/nice_path_decomposition.h"
#include "homomorphism/vector_allocator.h"

struct State {
    std::vector<size_t> bag;
    std::vector<size_t> mappings;
};

struct PathdecompotisionSettings {
    std::shared_ptr<ForgetHandler> forget;
    std::shared_ptr<IntroduceHandlerLeast> introduce;
    std::shared_ptr<VectorAllocator> alloc;
};

class PathdecompositionCounter
{
public:
    PathdecompositionCounter(std::shared_ptr<Graph>& h, std::shared_ptr<Graph>& g,
                        std::shared_ptr<NicePathDecomposition>& path, PathdecompotisionSettings& settings) :
            h_(h), g_(g), pdc_(path), n_(g->vertCount()),
            forgetter_(settings.forget), introducer_(settings.introduce), allocator_(settings.alloc) {};

    long compute();
private:
    std::shared_ptr<Graph> h_, g_;
    std::shared_ptr<NicePathDecomposition> pdc_;
    size_t n_;
    std::shared_ptr<ForgetHandler> forgetter_;
    std::shared_ptr<IntroduceHandlerLeast> introducer_;
    std::shared_ptr<VectorAllocator> allocator_;

    State Introduce(State& state, size_t v);
    State Forget(State& state, size_t v);
};

#endif

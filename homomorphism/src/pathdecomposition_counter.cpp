#include "homomorphism/pathdecomposition_counter.h"

#include <algorithm>

long PathdecompositionCounter::compute() {
    DPState state = { std::vector<size_t>(0), new std::vector<size_t> {1} };

    for(auto & node : pdc_->decomposition_) {
        if(node.introduce) {
            state = Introduce(state, node.vertex);
        } else {
            state = Forget(state, node.vertex);
        }
    }

    size_t count = 0;

    for (size_t c : *state.mappings)
    {
        count += c;
    }

    allocator_->Free(state.mappings, state.bag.size());

    return count;
}

DPState PathdecompositionCounter::Introduce(DPState &state, size_t v) {
    auto bag = state.bag;

    std::vector<size_t>* mapping = allocator_->Allocate(bag.size() + 1);
    introducer_->introduceLast(*state.mappings, *mapping, bag, h_, g_, n_, v);
    allocator_->Free(state.mappings, bag.size());

    bag.insert(bag.begin(), v);

    return {bag, mapping};
}

DPState PathdecompositionCounter::Forget(DPState &state, size_t v) {
    auto bag = state.bag;

    auto pos = std::find(bag.begin(), bag.end(), v) - bag.begin();

    std::vector<size_t>* mapping = allocator_->Allocate(bag.size() - 1);
    forgetter_->forget(*state.mappings, *mapping, bag.size(), pos);
    allocator_->Free(state.mappings, bag.size());

    bag.erase(bag.begin() + pos);

    return {bag, mapping};
}

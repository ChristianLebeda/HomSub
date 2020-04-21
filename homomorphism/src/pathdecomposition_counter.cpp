#include "homomorphism/pathdecomposition_counter.h"

#include <algorithm>

long PathdecompositionCounter::compute() {
    allocator_->setSize(n_, pdc_->getWidth());

    State state = { std::vector<size_t>(0), std::vector<size_t> {1} };

    for(auto & node : pdc_->decomposition_) {
        if(node.introduce) {
            state = Introduce(state, node.vertex);
        } else {
            state = Forget(state, node.vertex);
        }
    }

    size_t count = 0;

    for (size_t c : state.mappings)
    {
        count += c;
    }

    return count;
}

State PathdecompositionCounter::Introduce(State &state, size_t v) {
    auto bag = state.bag;

    std::vector<size_t> mapping = allocator_->get(bag.size() + 1);
    introducer_->introduceLast(state.mappings, mapping, bag, h_, g_, n_, v);
    allocator_->free(state.mappings, bag.size());

    bag.push_back(v);

    return {bag, mapping};
}

State PathdecompositionCounter::Forget(State &state, size_t v) {
    auto bag = state.bag;

    auto pos = std::find(bag.begin(), bag.end(), v) - bag.begin();

    std::vector<size_t> mapping = allocator_->get(bag.size() - 1);
    forgetter_->SetSizesAndIndex(n_, bag.size(), pos);
    forgetter_->forget(state.mappings, mapping, n_);
    allocator_->free(state.mappings, bag.size());

    bag.erase(bag.begin() + pos);

    return {bag, mapping};
}

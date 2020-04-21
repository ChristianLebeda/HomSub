#include <homomorphism/calculation_remapper.h>
#include "homomorphism/homomorphism_counter.h"

long HomomorphismCounter::compute() {
    allocator_->setSize(n_, tdc_->getWidth());

    DPState res = computeRec(tdc_->getRoot());

    size_t count = 0;

    for (size_t c : res.mappings)
    {
        count += c;
    }

    return count;
}

// The state at each step is a pair of vectors
// The first vector contains the ordered bag of vertices for that node
// The second vector contains the count of homomorphisms for all possible mappings of said bag
DPState HomomorphismCounter::computeRec(const std::shared_ptr<NTDNode>& node) {
    switch (node->nodeType)
    {
        case INTRODUCE:
            return computeIntroduceRec(node->left, node->vertex);
        case FORGET:
            return computeForgetRec(node->left, node->vertex);
        case JOIN:
            return computeJoinRec(node->left, node->right);
        default:
            return { std::vector<size_t>(0), std::vector<size_t> {1} };
    }
}

DPState HomomorphismCounter::computeIntroduceRec(const std::shared_ptr<NTDNode>& child, size_t x) {
    // Currently indices are 1-indexes for the tree decomposition and 0-indexes for the algorithm
    x--;

    DPState c = computeRec(child);

    std::vector<size_t> bag = c.bag;

    // TODO: Could be precomputed for cleaner code
    size_t pos;
    for(pos = 0; pos < bag.size(); pos++) {
        if(bag[pos] > x) {
            break;
        }
    }

    // Introduce the last vertex
    std::vector<size_t> mapping = allocator_->get(bag.size() + 1);
    introducer_->introduceLast(c.mappings, mapping, c.bag, h_, g_, n_, x);
    allocator_->free(c.mappings, bag.size());

    // Remap vertex to correct position
    std::vector<size_t> result = allocator_->get(bag.size() + 1);
    mapper_->SetSizes(n_, bag.size() + 1);
    mapper_->Insert(mapping, result, pos);
    allocator_->free(mapping, bag.size() + 1);

    bag.insert(bag.begin() + pos, x);

    return { bag, result };
}

// TODO: Handle case of forgetting only vertex
// Should also be handled properly for introduce nodes
DPState HomomorphismCounter::computeForgetRec(const std::shared_ptr<NTDNode>& child, size_t x) {
    x--;

    DPState c = computeRec(child);

    std::vector<size_t> bag = c.bag;

    // TODO: Could be precomputed for cleaner code
    size_t pos;
    for(pos = 0; pos < bag.size(); pos++) {
        if(bag[pos] == x) {
            break;
        }
    }

    // Remap vertex to last position
    std::vector<size_t> mapping = allocator_->get(bag.size());
    mapper_->SetSizes(n_, bag.size());
    mapper_->Extract(c.mappings, mapping, pos);
    allocator_->free(c.mappings, bag.size());

    // Forget the last vertex
    std::vector<size_t> result = allocator_->get(bag.size() - 1);
    forgetter_->forget(mapping, result, bag.size(), bag.size() - 1);
    allocator_->free(mapping, bag.size());

    bag.erase(bag.begin() + pos);

    return { bag, result };
}

DPState HomomorphismCounter::computeJoinRec(const std::shared_ptr<NTDNode>& child1, const std::shared_ptr<NTDNode>& child2) {
    // The bag of the results should be identical
    DPState c1 = computeRec(child1);
    DPState c2 = computeRec(child2);

    std::vector<size_t> joined = joiner_->join(c1.mappings, c2.mappings);

    return { c1.bag, joined };
}

#include "homomorphism/dynamic_programming_counter.h"

long DynamicProgrammingCounter::compute() {
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
DPState DynamicProgrammingCounter::computeRec(const std::shared_ptr<NTDNode>& node) {
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

DPState DynamicProgrammingCounter::computeIntroduceRec(const std::shared_ptr<NTDNode>& child, size_t x) {
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

    std::vector<unsigned char> connected(bag.size(), false);
    for (int i = 0; i < bag.size(); i++)
    {
        if(h_->edgeExist(x, bag[i])) {
            connected[i] = true;
        }
    }

    // Introduce the last vertex
    std::vector<size_t> result = allocator_->get(bag.size() + 1);
    introducer_->Introduce(c.mappings, result, connected, x, pos);
    allocator_->free(c.mappings, bag.size());

    bag.insert(bag.begin() + pos, x);

    return { bag, result };
}

DPState DynamicProgrammingCounter::computeForgetRec(const std::shared_ptr<NTDNode>& child, size_t x) {
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
    // Forget the last vertex
    std::vector<size_t> result = allocator_->get(bag.size() - 1);
    forgetter_->forget(c.mappings, result, bag.size(), pos);
    allocator_->free(c.mappings, bag.size());

    bag.erase(bag.begin() + pos);

    return { bag, result };
}

DPState DynamicProgrammingCounter::computeJoinRec(const std::shared_ptr<NTDNode>& child1, const std::shared_ptr<NTDNode>& child2) {
    // The bag of the results should be identical
    DPState c1 = computeRec(child1);
    DPState c2 = computeRec(child2);

    std::vector<size_t> joined = joiner_->join(c1.mappings, c2.mappings);

    return { c1.bag, joined };
}

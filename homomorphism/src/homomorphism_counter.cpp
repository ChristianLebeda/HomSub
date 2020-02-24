#include "homomorphism/homomorphism_counter.h"

#include "homomorphism/mapping_iterator.h"

std::shared_ptr<HomomorphismCounter> HomomorphismCounter::instantiate(std::shared_ptr<Graph> h,
    std::shared_ptr<Graph> g, std::shared_ptr<NiceTreeDecomposition> tree) {
    return std::make_shared<HomomorphismCounter>(h, g, tree);
}

size_t HomomorphismCounter::compute() {
    std::pair<std::vector<size_t>, std::vector<size_t>> res = computeRec(tdc_->getRoot());

    size_t count = 0;

    for (size_t c : res.second)
    {
        count += c;
    }

    return count;
}

// The state at each step is a pair of vectors
// The first vector contains the ordered bag of vertices for that node
// The second vector contains the count of homomorphisms for all possible mappings of said bag
std::pair<std::vector<size_t>, std::vector<size_t>> HomomorphismCounter::computeRec(std::shared_ptr<NTDNode> node) {
    switch (node->nodeType)
    {
        case INTRODUCE: 
            return computeIntroduceRec(node->left, node->vertex);
        case FORGET: 
            return computeForgetRec(node->left, node->vertex);
        case JOIN: 
            return computeJoinRec(node->left, node->right);
        default:
            return std::make_pair(std::vector<size_t>(0), std::vector<size_t> {1});
    }
}

std::pair<std::vector<size_t>, std::vector<size_t>> HomomorphismCounter::computeIntroduceRec(std::shared_ptr<NTDNode> child, size_t x) {
    // Currently indices are 1-indexes for the tree decomposition and 0-indexes for the algorithm
    x--;

    std::pair<std::vector<size_t>, std::vector<size_t>> c = computeRec(child);

    // First node to be introduced
    if (c.first.empty()) {
        return std::make_pair(std::vector<size_t> {x}, std::vector<size_t>(g_->vertCount(), c.second[0]));
    }

    std::vector<size_t> bag = c.first;

    // Figure out which vertices in H are connected to the introduced vertex
    std::vector<bool> connected;
    for (size_t v : bag)
    {
        connected.push_back(h_->edgeExist(x, v));
    }

    // Compute offsets values to compute the new index
    std::vector<size_t> offsets(bag.size());

    size_t offset = 1;
    bool larger = true;
    size_t newPos, newOffset;
    for (int i = bag.size() - 1; i >= 0; i--)
    {
        if (larger && c.first[i] < x) {
            larger = false;
            newPos = i + 1ULL;
            newOffset = offset;
            offset *= g_->vertCount();
        }
        offsets[i] = offset;
        offset *= g_->vertCount();
    }

    if (larger) {
        newPos = 0;
        newOffset = offset;
    }

    std::vector<size_t> mapping(c.second.size() * g_->vertCount(), 0);

    std::shared_ptr<MappingIterator> it = MappingIterator::makeIterator(g_->vertCount(), bag.size());

    do {
        size_t count = c.second[it->idx];
        if (count) {
            // Compute where the new entries should be stored.
            // TODO: Compute this in the iterator to avoid recomputing
            size_t newidx = 0;
            for (size_t i = 0; i < it->mapping.size(); i++)
            {
                newidx += it->mapping[i] * offsets[i];
            }

            // Add all valid assignments of vertex x
            for (size_t i = 0; i < g_->vertCount(); i++)
            {
                // Ensure that all edges of H are also present in G
                bool valid = true;
                for (size_t j = 0; j < connected.size(); j++)
                {
                    if (connected[j] && !g_->edgeExist(i, it->mapping[j])) {
                        valid = false;
                        break;
                    }
                }
                if(valid)
                    mapping[newidx + i * newOffset] = count;
            }
        }
    } while (it->next());

    bag.insert(bag.begin() + newPos, x);

    return std::make_pair(bag, mapping);
}

// TODO: Handle case of forgetting only vertex
// Should also be handled properly for introduce nodes
std::pair<std::vector<size_t>, std::vector<size_t>> HomomorphismCounter::computeForgetRec(std::shared_ptr<NTDNode> child, size_t x) {
    x--;

    std::pair<std::vector<size_t>, std::vector<size_t>> c = computeRec(child);

    std::vector<size_t> bag = c.first;

    std::vector<size_t> offsets(bag.size());

    size_t offset = 1;
    size_t oldPos = 0;
    for (int i = bag.size() - 1; i >= 0; i--)
    {
        if (bag[i] == x) {
            oldPos = i;
            offsets[i] = 0;
            continue;
        }
        offsets[i] = offset;
        offset *= g_->vertCount();
    }

    std::vector<size_t> mapping(c.second.size() / g_->vertCount(), 0);

    std::shared_ptr<MappingIterator> it = MappingIterator::makeIterator(g_->vertCount(), bag.size());

    do {
        size_t count = c.second[it->idx];
        if (count) {
            // Combines mappings that are identical without x
            size_t newidx = 0;
            for (size_t i = 0; i < it->mapping.size(); i++)
            {
                newidx += it->mapping[i] * offsets[i];
            }

            mapping[newidx] += count;
        }
    } while (it->next());

    bag.erase(bag.begin() + oldPos);

    return std::make_pair(bag, mapping);
}

std::pair<std::vector<size_t>, std::vector<size_t>> HomomorphismCounter::computeJoinRec(std::shared_ptr<NTDNode> child1, std::shared_ptr<NTDNode> child2) {
    // First element of results should be identical
    std::pair<std::vector<size_t>, std::vector<size_t>> c1 = computeRec(child1);
    std::pair<std::vector<size_t>, std::vector<size_t>> c2 = computeRec(child2);

    std::vector<size_t> joined(c1.second.size());

    for (size_t i = 0; i < joined.size(); i++)
    {
        joined[i] = c1.second[i] * c2.second[i];
    }

    return std::make_pair(c1.first, joined);
}

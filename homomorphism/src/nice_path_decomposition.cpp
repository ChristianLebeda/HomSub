#include "homomorphism/nice_path_decomposition.h"

std::shared_ptr<NicePathDecomposition> NicePathDecomposition::FromTd(std::shared_ptr<TreeDecomposition> td) {
    if(!td->IsPathDecomposition()) {
        return nullptr;
    }

    int next = 0;
    // Find start vertex
    for(size_t i = 0; i < td->getGraph()->vertCount(); i++) {
        if(td->getGraph()->getNeighbourList()[i].size() == 1) {
            next = i;
            break;
        }
    }

    std::vector<NPDNode> decomposition;

    auto nbs = td->getGraph()->getNeighbourList();

    int prev = -1;
    std::unordered_set<size_t> prevBag(0), nextBag;

    auto ss = td->getGraph()->vertCount();

    for(int i = 0; i < td->getGraph()->vertCount(); i++) {
        nextBag = td->getBag(next);

        for(size_t v : prevBag) {
            if(!nextBag.count(v)) {
                decomposition.push_back({false, v - 1});
            }
        }

        for(size_t v : nextBag) {
            if(!prevBag.count(v)) {
                decomposition.push_back({true, v - 1});
            }
        }

        prev = next;
        prevBag = nextBag;

        nbs[next].erase(prev);
        next = nbs[next].empty() ? -1 : (int) *nbs[next].begin();
    }


    return std::make_shared<NicePathDecomposition>(decomposition, td->getWidth());
}

size_t NicePathDecomposition::getWidth() {
    return width_;
}
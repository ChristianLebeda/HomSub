#include "homomorphism//hom_treewidth_sparse.h"

#include <algorithm>

long HomTreewidthSparse::compute() {
    std::vector<size_t> forgetStack;
    DPState res = computeRec(tdc_->getRoot(), forgetStack);

    size_t count = 0;
    size_t k = res.bag.size();

    for(size_t idx = k; idx < res.mappings->size(); idx += k + 1) {
        count += res.mappings->operator[](idx);
    }

    delete res.mappings;

    return count;
}

// The state at each step is a pair of vectors
// The first vector contains the ordered bag of vertices for that node
// The second vector contains the count of homomorphisms for functions of said bag
// A function of a bag with k vertices is stored as k + 1 integers
DPState HomTreewidthSparse::computeRec(const std::shared_ptr<NTDNode>& node, std::vector<size_t>& forgetStack) {
    switch (node->nodeType)
    {
        case INTRODUCE:
            return computeIntroduceRec(node->left, node->vertex, forgetStack);
        case FORGET:
            return computeForgetRec(node->left, node->vertex, forgetStack);
        case JOIN:
            return computeJoinRec(node->left, node->right, forgetStack);
        default:
            return { std::vector<size_t>(0), new std::vector<size_t> {1} };
    }
}

DPState HomTreewidthSparse::computeIntroduceRec(const std::shared_ptr<NTDNode>& child, size_t x, std::vector<size_t>& forgetStack) {
    // Currently indices are 1-indexes for the tree decomposition and 0-indexes for the algorithm
    x--;

    DPState c = computeRec(child, forgetStack);

    std::vector<size_t> bag = c.bag;

    auto entry = std::find(forgetStack.begin(), forgetStack.end(), x);

    size_t pos = 0;

    if(entry != forgetStack.end()) {
        pos = bag.size();
        while(pos != 0) {
            if(std::find(entry, forgetStack.end(), bag[pos - 1]) != forgetStack.end()) {
                pos--;
            } else {
                break;
            }
        }
    }

    std::vector<unsigned char> connected(bag.size(), false);
    for (int i = 0; i < bag.size(); i++)
    {
        if(h_->edgeExist(x, bag[i])) {
            connected[i] = true;
        }
    }

    auto functions = Introduce(*c.mappings, bag, connected, connected.size(), pos);

    delete c.mappings;

    bag.insert(bag.begin() + pos, x);

    return { bag, functions };
}

DPState HomTreewidthSparse::computeForgetRec(const std::shared_ptr<NTDNode>& child, size_t x, std::vector<size_t>& forgetStack) {
    x--;

    forgetStack.push_back(x);
    DPState c = computeRec(child, forgetStack);
    forgetStack.pop_back();

    std::vector<size_t> bag = c.bag;

    auto functions = Forget(*c.mappings, bag.size());

    delete c.mappings;

    size_t pos;
    for(pos = 0; pos < bag.size(); pos++) {
        if(bag[pos] == x) {
            break;
        }
    }

    bag.erase(bag.begin() + pos);

    return { bag, functions };
}

DPState HomTreewidthSparse::computeJoinRec(const std::shared_ptr<NTDNode>& child1, const std::shared_ptr<NTDNode>& child2, std::vector<size_t>& forgetStack) {
    // The bag of the results should be identical
    DPState c1 = computeRec(child1, forgetStack);
    DPState c2 = computeRec(child2, forgetStack);

    auto functions = Join(*c1.mappings, *c2.mappings, c1.bag.size());

    delete c1.mappings;
    delete c2.mappings;

    return { c1.bag, functions };
}

// The functions below could be refactored to use structure of dense implementation
// They could also reuse the vectors to save memory and perhaps increase performance
std::vector<size_t>* HomTreewidthSparse::Introduce(std::vector<size_t> & child, std::vector<size_t>& bag, std::vector<unsigned char>& connected, int k, int pos) {
    auto state = new std::vector<size_t>();
    state->reserve(child.size());

    auto it = child.begin();

    while(it != child.end()) {
        auto start = it;
        it += k + 1;
        while(it != child.end() && std::equal(start, start + pos, it)) {
            it += k + 1;
        }
        // The range start-it does not differ in most significant digits
        // The value of the new vertex determines the order of the new functions
        for(size_t fx = 0; fx < n_; fx++) {
            bool consistent = true;
            for(int idx = 0; idx < pos; idx++) {
                consistent &= !connected[idx] || g_->edgeExist(fx, *(start + idx));
            }
            if(!consistent) {
                // The value of the new vertex is not consistent with the most significant vertices
                continue;
            }
            // Add all functions in the range consistent with the new vertex
            for(auto func = start; func != it; func += k + 1) {
                consistent = true;
                for(int idx = pos; idx < k; idx++) {
                    consistent &= !connected[idx] || g_->edgeExist(fx, *(func + idx));
                }
                if(consistent) {
                    // Copy function to new state
                    state->insert(state->end(), func, func + pos);
                    state->push_back(fx);
                    state->insert(state->end(), func + pos, func + k + 1);
                }
            }
        }
    }


    return state;
}

std::vector<size_t>* HomTreewidthSparse::Forget(std::vector<size_t> & child, int k) {
    // Always forget the least significant value
    auto state = new std::vector<size_t>();
    if(child.size() / n_ > 50)
        state->reserve(child.size()/n_);

    auto it = child.begin();

    while(it != child.end()) {
        state->insert(state->end(), it, it + k - 1);
        size_t val = *(it + k);
        it += k + 1;
        while(it != child.end() && std::equal(it, it + k - 1, it - (k + 1))) {
            val += *(it + k);
            it += k + 1;
        }
        state->push_back(val);
    }

    return state;
}

std::vector<size_t>* HomTreewidthSparse::Join(std::vector<size_t> & child1, std::vector<size_t> & child2, int k) {
    auto state = new std::vector<size_t>();
    state->reserve(std::min(child1.size(), child2.size()));

    auto it1 = child1.begin();
    auto it2 = child2.begin();

    while(it1 != child1.end() && it2 != child2.end()) {
        switch (Compare(it1, it1 + k, it2)) {
            case -1:
                it2 += k + 1;
                break;
            case 0:
                state->insert(state->end(), it1, it1 + k + 1);
                state->push_back(*(it1 + k) * *(it2 + k));
                it1 += k + 1;
                it2 += k + 1;
                break;
            case 1:
                it1 += k + 1;
                break;
        }
    }


    return state;
}

int HomTreewidthSparse::Compare(std::vector<size_t>::iterator first, std::vector<size_t>::iterator last, std::vector<size_t>::iterator second) {
    while (first!=last)
    {
        if (*second<*first) return -1;
        else if (*first<*second) return 1;
        ++first; ++second;
    }
    return 0;
}


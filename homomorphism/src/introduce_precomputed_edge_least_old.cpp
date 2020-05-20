#include "homomorphism/introduce_precomputed_edge_least_old.h"

#include <iostream>

#include "homomorphism/introduce_mapping_iterator.h"

std::vector<size_t>& IntroducePrecomputedEdgeLeastOld::Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
                                                                 std::vector<unsigned char> &bag, size_t x, size_t ii) {
    if(input.size() == 1) {
        for(unsigned long & i : output) {
            i = input[0];
        }
        return output;
    }

    if(!bag[0]) {
        std::cerr << "ERROR: IntroducePrecomputedEdgeLeast called with no edge to least significant" << std::endl;
        throw;
    }

    if(ii == 0) {
        std::cerr << "ERROR: IntroducePrecomputedEdgeLeast called with index zero" << std::endl;
        throw;
    }

    size_t edges = 0;
    for(auto & edge : bag) {
        if(edge) {
            edges++;
        }
    }

    IntroduceMappingIterator mapping = IntroduceMappingIterator::InitializeSecond(size_.n, bag.size(), bag);
    auto precomputedStart = precomputed_->GetIterator(edges);

    for(size_t idx = 0; idx < input.size(); idx += size_.n) {

        //TODO: Include in iterator
        size_t newidx = 0;
        for(int i = 0; i < ii; i++) {
            newidx += mapping.mapping_[i] * size_.sizes[i];
        }
        for(int i = ii; i < bag.size(); i++) {
            newidx += mapping.mapping_[i] * size_.sizes[i + 1];
        }

        // Add all valid assignments of vertex x
        for (size_t i = 0; i < size_.n; i++)
        {
            auto it = precomputedStart + mapping.CurrentOffset() + i * size_.n;
            size_t rangestart = newidx + i * size_.sizes[ii];
            // Add range of value for least significant
            for (size_t j = 0; j < size_.n; j++)
            {
                output[rangestart + j] = *(it++) * input[idx + j];
            }
        }

        //TODO: Fix to single operator
        for(int i = 0; i < size_.n; i++) {
            mapping.NextChanged();
        }
    }

    return output;
}
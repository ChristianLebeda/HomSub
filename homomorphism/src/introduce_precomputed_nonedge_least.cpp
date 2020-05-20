#include "homomorphism/introduce_precomputed_nonedge_least.h"

#include <iostream>

#include "homomorphism/introduce_mapping_iterator.h"

std::vector<size_t>& IntroducePrecomputedNonedgeLeast::Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
        std::vector<unsigned char> &bag, size_t x, size_t idx) {
    if(input.size() == 1) {
        for(unsigned long & i : output) {
            i = input[0];
        }
        return output;
    }

    if(bag[0]) {
        std::cerr << "ERROR: IntroducePrecomputedNonedgeLeast called with edge to least significant" << std::endl;
        throw;
    }

    if(idx == 0) {
        std::cerr << "ERROR: IntroducePrecomputedNonedgeLeast called with index zero" << std::endl;
        throw;
    }

    size_t edges = 0;
    for(auto & edge : bag) {
        if(edge) {
            edges++;
        }
    }

    IntroduceMappingIterator itIn = IntroduceMappingIterator::InitializeInputIterator(size_.n, bag.size(), idx - 1);
    IntroduceMappingIterator itPre = IntroduceMappingIterator::InitializePrecomputedNonedge(size_.n, bag, idx - 1);
    auto precomputedStart = precomputed_->GetIterator(edges);


    for (auto outEntry = output.begin(); outEntry != output.end(); itIn.NextChanged(), itPre.NextChanged(), outEntry += size_.n) {
        if(precomputedStart[itPre.CurrentOffset()]) {
            auto inEntry = input.begin() + itIn.CurrentOffset();
            std::copy(inEntry, inEntry + size_.n, outEntry);
        } else {
            std::fill(outEntry, outEntry + size_.n, 0);
        }
    }

    return output;
}
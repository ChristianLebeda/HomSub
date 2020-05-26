#include "homomorphism/introduce_precomputed_edge_least.h"

#include <iostream>

#include "homomorphism/introduce_mapping_iterator.h"

std::vector<size_t>& IntroducePrecomputedEdgeLeast::Introduce(std::vector<size_t> &input, std::vector<size_t> &output,
                                                                 std::vector<unsigned char> &bag, size_t x, size_t idx) {
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

    if(idx == 0) {
        std::cerr << "ERROR: IntroducePrecomputedEdgeLeast called with index zero" << std::endl;
        throw;
    }

    size_t edges = 0;
    for(auto & edge : bag) {
        if(edge) {
            edges++;
        }
    }

    IntroduceMappingIterator itIn = IntroduceMappingIterator::InitializeInputIterator(size_.n, bag.size(), idx - 1);
    IntroduceMappingIterator itPre = IntroduceMappingIterator::InitializePrecomputedSecond(size_.n, bag, idx - 1);
    auto precomputedStart = precomputed_->GetIterator(edges);


    for (auto outEntry = output.begin(); outEntry != output.end(); itIn.NextChanged(), itPre.NextChanged()) {
        auto inEntry = input.begin() + itIn.CurrentOffset();
        auto precomputed = precomputedStart + itPre.CurrentOffset();

        for(int i = 0; i < size_.n; i++) {
            *(outEntry++) = *(inEntry++) * *(precomputed++);
        }
    }

    return output;
}
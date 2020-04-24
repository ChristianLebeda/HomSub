#include "homomorphism/introduce_mapping_iterator.h"

IntroduceMappingIterator IntroduceMappingIterator::Initialize(size_t n, size_t k, std::vector<bool> edges) {
    std::vector<size_t> offsets(k, 0);

    size_t offset = 1;

    for (int i = k - 1; i >= 0; --i) {
        if(edges[i]) {
            offset *= n;
            offsets[i] = offset;
        }
    }

    return IntroduceMappingIterator(n, k, offsets);
}

size_t IntroduceMappingIterator::CurrentOffset() {
    return current_;
}

bool IntroduceMappingIterator::NextChanged() {
    size_t prev = current_;

    for (int i = mapping_.size() - 1; i >= 0; --i)
    {
        if (mapping_[i] < n_ - 1)
        {
            mapping_[i]++;
            current_ += offsets_[i];
            return prev != current_;
        } else {
            mapping_[i] = 0;
            current_ -= offsets_[i] * (n_ - 1);
        }
    }

    return prev != current_;
}

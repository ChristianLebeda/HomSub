#include "homomorphism/remapping_iterator.h"

#include <utility>

RemappingIterator RemappingIterator::ExtractIterator(size_t n, size_t k, size_t pos) {
    std::vector<size_t> offsets(k);

    size_t offset = 1;

    for (int i = 0; i < k; ++i) {
        if(i == pos) {
            offsets[i] = 1;
        } else {
            offset *= n;
            offsets[i] = offset;
        }
    }

    return RemappingIterator(n, k, offsets);
}

RemappingIterator RemappingIterator::InsertIterator(size_t n, size_t k, size_t pos) {
    std::vector<size_t> offsets(k, 1);

    size_t offset = 1;

    for (int i = 1; i < k; ++i) {
        offsets[i] = offset;
        offset *= n;
        if(i == pos) {
            offsets[0] = offset;
            offset *= n;
        }
    }

    return RemappingIterator(n, k, offsets);
}

RemappingIterator RemappingIterator::CustomIterator(size_t n, size_t k, std::vector<size_t> offsets) {
    return RemappingIterator(n, k, std::move(offsets));
}

size_t RemappingIterator::next() {
    size_t next = current_;

    for (int i = 0; i < mapping_.size(); ++i)
    {
        if (mapping_[i] < n_ - 1)
        {
            mapping_[i]++;
            current_ += offsets_[i];
            return next;
        } else {
            mapping_[i] = 0;
            current_ -= offsets_[i] * (n_ - 1);
        }
    }

    current_ = -1;
    return next;
}
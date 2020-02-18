#include <homomorphism/mapping_iterator.h>

std::shared_ptr<MappingIterator> MappingIterator::makeIterator(int n, int k) {
    return std::make_shared<MappingIterator>(n, k);
}

bool MappingIterator::next() {
    idx++;

    for (int i = mapping.size() - 1; i >= 0; --i)
    {
        if (mapping[i] < n_ - 1)
        {
            mapping[i]++;
            for (int j = mapping.size() - 1; j > i; --j)
            {
                mapping[j] = 0;
            }
            return true;
        }
    }

    return false;
}

#include "homomorphism/mapping_iterator_old.h"

std::shared_ptr<MappingIteratorOld> MappingIteratorOld::makeIterator(int n, int k) {
    return std::make_shared<MappingIteratorOld>(n, k);
}

bool MappingIteratorOld::next() {
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

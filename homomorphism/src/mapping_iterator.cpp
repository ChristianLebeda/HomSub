#include "homomorphism/mapping_iterator.h"

void MappingIterator::Increment() {
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
            break;
        }
    }
}

#include "homomorphism/mapping_iterator.h"

void MappingIterator::Increment() {
    idx++;

    for (int i = 0; i < mapping.size(); ++i)
    {
        if (mapping[i] < n_ - 1)
        {
            mapping[i]++;
            for (int j = 0; j < i; ++j)
            {
                mapping[j] = 0;
            }
            break;
        }
    }
}

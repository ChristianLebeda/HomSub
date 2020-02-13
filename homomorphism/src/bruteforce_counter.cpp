#include "homomorphism/bruteforce_counter.h"

size_t BruteforceCounter::compute() {
	int count = 0;

    int* mapping = new int[k_];
    bool* used = new bool[n_] {0} ;
    
    countRecursive(mapping, used, 0, count);

    delete[] mapping;
    delete[] used;

	return count;
}

void BruteforceCounter::countRecursive(int* mapping, bool* used, int idx, int& count) {
    if (idx < k_) {
        for (size_t i = 0; i < n_; i++)
        {
            if (!used[i]) {
                used[i] = true;
                mapping[idx] = i;
                countRecursive(mapping, used, idx + 1, count);
                used[i] = false;
            }
        }
    }
    else {
        count += checkIsEmbedding(mapping);
    }
}

bool BruteforceCounter::checkIsEmbedding(int* mapping) {  
    for (size_t u = 1; u < k_; u++) {
        for (size_t v = 0; v < u; v++) {
            if (h_->edgeExist(u, v) && !g_->edgeExist(mapping[u], mapping[v])) {
                return false;
            }
        }
    }

    return true;
}

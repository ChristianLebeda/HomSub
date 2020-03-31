#include "homomorphism/iterator_introduce_handler.h"

#include <memory>
#include <vector>

#include "homomorphism/graph.h"
#include "homomorphism/mapping_iterator.h"

std::vector<size_t>& IteratorIntroduceHandler::introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                                     std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                                     std::shared_ptr<Graph> g, size_t n, size_t x) {

    if(input.size() == 1) {
        for(unsigned long & i : output) {
            i = input[0];
        }
        return output;
    }

    // Figure out which vertices in H are connected to the introduced vertex
    std::vector<unsigned char> connected;
    for (size_t v : bag)
    {
        connected.push_back(h->edgeExist(x, v));
    }

    MappingIterator it(n, bag.size());

    //for(size_t idx = 0; idx < input.size(); idx++) {
    while(it.idx < input.size()) {
        size_t count = input[it.idx];

        size_t newidx = it.idx * n;

        // Add all valid assignments of vertex x
        for (size_t i = 0; i < n; i++)
        {
            // Ensure that all edges of H are also present in G
            bool valid = true;
            for (size_t j = 0; j < connected.size(); j++)
            {
                if (connected[j] && !g->edgeExist(i, it.mapping[j])) {
                    valid = false;
                    break;
                }
            }

            output[newidx + i] = valid ? count : 0;
        }

        it.Increment();
    }

    return output;
}

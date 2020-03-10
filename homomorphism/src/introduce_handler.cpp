#include "homomorphism/introduce_handler.h"

#include <memory>
#include <vector>

#include "homomorphism/graph.h"
#include "homomorphism/mapping_iterator.h"

std::vector<size_t>& IntroduceHandler::introduceLast(std::vector <size_t> &input, std::vector <size_t> &output,
                                                     std::vector <size_t>& bag, std::shared_ptr<Graph> h,
                                                     std::shared_ptr<Graph> g, size_t n, size_t x) {

    // Figure out which vertices in H are connected to the introduced vertex
    std::vector<unsigned char> connected;
    for (size_t v : bag)
    {
        connected.push_back(h->edgeExist(x, v));
    }

    // Compute offsets values to compute the new index
    std::vector<size_t> offsets(bag.size() + 1);

    offsets[offsets.size() - 1] = 1;

    for (int i = 1; i < offsets.size(); ++i) {
        offsets[offsets.size() - i - 1] = offsets[offsets.size() - i] * n;
    }

    std::shared_ptr<MappingIterator> it = MappingIterator::makeIterator(n, bag.size());

    do {
        size_t count = input[it->idx];

        // Compute where the new entries should be stored.
        // TODO: Compute this in the iterator to avoid recomputing
        size_t newidx = 0;
        for (size_t i = 0; i < it->mapping.size(); i++)
        {
            newidx += it->mapping[i] * offsets[i];
        }

        // Add all valid assignments of vertex x
        for (size_t i = 0; i < n; i++)
        {
            // Ensure that all edges of H are also present in G
            bool valid = true;
            for (size_t j = 0; j < connected.size(); j++)
            {
                if (connected[j] && !g->edgeExist(i, it->mapping[j])) {
                    valid = false;
                    break;
                }
            }
            output[newidx + i] = valid ? count : 0;
        }
    } while (it->next());

    return output;
}
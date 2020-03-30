#ifndef TRAVERSAL_HOMOMORPHISM_COUNTER_H
#define TRAVERSAL_HOMOMORPHISM_COUNTER_H

#include <vector>
#include "homomorphism/edge_set_graph.h"
#include <memory>

class TraversalHomomorphismCounter {
public:
    static int Count(EdgeSetGraph h, EdgeSetGraph g);
    static std::vector<std::vector<size_t>> GetKTraversals(std::shared_ptr<EdgeSetGraph> g, int k);
private:
    static bool CheckHomomorphism(EdgeSetGraph h, EdgeSetGraph g, std::vector<size_t> mapping);
    static std::vector<std::vector<size_t>> GetKTraversalsUtil(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> visited, int k);
};


#endif /* traversal_homomorphism_counter_h */

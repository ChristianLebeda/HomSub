#ifndef TRAVERSAL_HOMOMORPHISM_COUNTER_H
#define TRAVERSAL_HOMOMORPHISM_COUNTER_H

#include <vector>
#include "homomorphism/edge_set_graph.h"

class TraversalHomomorphismCounter {
public:
    static int Count(EdgeSetGraph h, EdgeSetGraph g);
    
private:
    static bool CheckHomomorphism(EdgeSetGraph h, EdgeSetGraph g, std::vector<size_t> mapping);
    static std::vector<std::vector<size_t>> GetKTraversals(EdgeSetGraph g, int k);
    static std::vector<std::vector<size_t>> GetKTraversalsUtil(EdgeSetGraph g, std::vector<size_t> visited, int k);
};


#endif /* traversal_homomorphism_counter_h */

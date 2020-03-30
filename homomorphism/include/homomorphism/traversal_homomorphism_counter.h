#ifndef TRAVERSAL_HOMOMORPHISM_COUNTER_H
#define TRAVERSAL_HOMOMORPHISM_COUNTER_H

#include <vector>
#include "homomorphism/edge_set_graph.h"
#include <memory>

class TraversalHomomorphismCounter {
public:
    static int Count(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g);
    static std::vector<std::vector<size_t>> GetKTraversals(std::shared_ptr<EdgeSetGraph> g, int k);
private:
    static bool CheckHomomorphism(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> hTraversal, std::vector<size_t> gTraversal);
    static std::vector<std::vector<size_t>> GetKTraversalsUtil(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> visited, int k);
    static std::vector<size_t> GetFirstTraversal(std::shared_ptr<EdgeSetGraph> g);
    
    static std::unordered_set<size_t> GetOpenNeighbourhood(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> verts);
};


#endif /* traversal_homomorphism_counter_h */

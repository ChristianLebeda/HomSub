#ifndef TRAVERSAL_HOMOMORPHISM_COUNTER_H
#define TRAVERSAL_HOMOMORPHISM_COUNTER_H

#include <vector>
#include "homomorphism/edge_set_graph.h"
#include <memory>

class TraversalHomomorphismCounter {
public:
    static long Count(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g);
private:
    static bool CheckHomomorphism(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> hTraversal, std::vector<size_t> gTraversal);
    static long TestKTraversals(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> hTraversal, std::vector<size_t> gTraversal);
    static std::vector<size_t> GetFirstTraversal(std::shared_ptr<EdgeSetGraph> g);
    static std::unordered_set<size_t> GetOpenNeighbourhood(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> verts);
};


#endif /* traversal_homomorphism_counter_h */

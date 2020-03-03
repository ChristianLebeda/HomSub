#ifndef HOMOMORPHISM_EDGE_SET_GRAPH_H_
#define HOMOMORPHISM_EDGE_SET_GRAPH_H_

#include <set>
#include <vector>
#include <unordered_set>

#include "homomorphism/graph.h"

class EdgeSetGraph : public Graph {
public:
    EdgeSetGraph(size_t verts) : verts_(verts), edges_(0), neighbours_() {
        neighbours_.resize(verts);
    };
    EdgeSetGraph(size_t verts, size_t edges, std::vector<std::unordered_set<size_t>> neighbours) : verts_(verts), edges_(edges), neighbours_(neighbours) {};
    void clear(size_t v);
    size_t vertCount();
    size_t edgeCount();
    void addEdge(size_t u, size_t v);
    bool edgeExist(size_t u, size_t v);
    std::unordered_set<size_t> getNeighbourhood(size_t v);
    bool isIsomorphic(std::shared_ptr<Graph> g);
    std::shared_ptr<Graph> partition(std::set<size_t>* parts, size_t size);
    std::vector<std::unordered_set<size_t>> getNeighbourList();
    
private:
    size_t verts_;
    size_t edges_;
    std::vector<std::unordered_set<size_t>> neighbours_;
};

#endif 

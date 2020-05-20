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
    static std::shared_ptr<EdgeSetGraph> FromGraph(std::shared_ptr<Graph> g);
    void clear(size_t v) override;
    size_t vertCount() override;
    size_t edgeCount() override;
    static std::shared_ptr<EdgeSetGraph> fromFile(std::string path);
    static std::shared_ptr<EdgeSetGraph> parseGr(std::ifstream& input);
    void addEdge(size_t u, size_t v) override;
    bool edgeExist(size_t u, size_t v) override;
    std::unordered_set<size_t> getNeighbourhood(size_t v) override;
    bool isIsomorphic(std::shared_ptr<Graph> g) override;
    std::shared_ptr<Graph> partition(std::set<size_t>* parts, size_t size) override;
    std::vector<std::unordered_set<size_t>> getNeighbourList();
    
private:
    size_t verts_;
    size_t edges_;
    std::vector<std::unordered_set<size_t>> neighbours_;
};

#endif 

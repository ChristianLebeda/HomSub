#ifndef HOMOMORPHISM_TREE_DECOMPOSITION_h
#define HOMOMORPHISM_TREE_DECOMPOSITION_h

#include "homomorphism/edge_set_graph.h"

#include <fstream>
#include <memory>
#include <vector>
#include <unordered_set>

class TreeDecomposition {
public:
    TreeDecomposition(std::shared_ptr<EdgeSetGraph> g, const std::vector<std::unordered_set<size_t>> &b, size_t width) : graph(g), bags(b), width_(width) {};
    static std::shared_ptr<TreeDecomposition> parseTd(std::istream& input);
    std::string toTd();
    bool IsPathDecomposition();
    std::shared_ptr<EdgeSetGraph> getGraph();
    std::unordered_set<size_t> getBag(size_t bag);
    size_t getWidth();
private:
    std::shared_ptr<EdgeSetGraph> graph;
    std::vector<std::unordered_set<size_t>> bags;
    size_t width_;
};

#endif 

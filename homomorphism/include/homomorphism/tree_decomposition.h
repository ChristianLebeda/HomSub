//
//  tree_decomposition.h
//  homomorphism
//
//  Created by Jonas Mortensen on 05/02/2020.
//

#ifndef TREE_DECOMPOSITION_h
#define TREE_DECOMPOSITION_h

#include "edge_set_graph.h"
#include <memory>
#include <vector>
#include <unordered_set>
#include <fstream>

class TreeDecomposition {
public:
    TreeDecomposition(std::shared_ptr<EdgeSetGraph> g, std::vector<std::unordered_set<size_t>> b) : graph(g), bags(b) {};
    static std::shared_ptr<TreeDecomposition> parseTd(std::ifstream& input);
    std::shared_ptr<EdgeSetGraph> getGraph();
    std::unordered_set<size_t> getBag(size_t bag);
private:
    std::shared_ptr<EdgeSetGraph> graph;
    std::vector<std::unordered_set<size_t>> bags;
};

#endif /* tree_decomposition_h */

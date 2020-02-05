//
//  tree_decomposition.h
//  homomorphism
//
//  Created by Jonas Mortensen on 05/02/2020.
//

#ifndef TREE_DECOMPOSITION_h
#define TREE_DECOMPOSITION_h

#include "graph.h"
#include <memory>
#include <vector>
#include <fstream>

class TreeDecomposition {
public:
    TreeDecomposition(std::shared_ptr<Graph> g, std::vector<std::vector<size_t>> b) : graph(g), bags(b) {};
    static std::shared_ptr<TreeDecomposition> parseTd(std::ifstream& input);
    int test();
private:
    std::shared_ptr<Graph> graph;
    std::vector<std::vector<size_t>> bags;
};

#endif /* tree_decomposition_h */

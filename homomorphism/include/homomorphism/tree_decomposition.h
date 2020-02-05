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

class TreeDecomposition {
public:
    TreeDecomposition(std::shared_ptr<Graph> g, std::vector<std::vector<int>> b) : graph(g), bags(b) {};
    std::shared_ptr<TreeDecomposition> fromTdFile(std::string tdFile);
    int test();
private:
    std::shared_ptr<Graph> graph;
    std::vector<std::vector<int>> bags;
};

#endif /* tree_decomposition_h */

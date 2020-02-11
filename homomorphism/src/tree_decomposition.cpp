//
//  tree_decomposition.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 05/02/2020.
//

#include <iostream>
#include <sstream>
#include "homomorphism/tree_decomposition.h"

std::shared_ptr<TreeDecomposition> TreeDecomposition::parseTd(std::ifstream& input) {
    std::string line;
    do {
        if(!std::getline(input, line)) return nullptr;
    } while (line[0] == 'c');
    size_t bagN, width, n;
    if (!std::sscanf(line.c_str(), "s td %zd %zd %zd", &bagN, &width, &n)) return nullptr;
    
    //TODO: Specific Graph. Maybe this should maybe be generic
    std::shared_ptr <EdgeSetGraph> G = std::make_shared<EdgeSetGraph>(n);
    
    std::vector<std::vector<size_t>> bags;
    bags.resize(bagN);
    for(size_t i = 0; i < bagN; i++) {
        int bagI = -1;
        getline(input, line);
        std::stringstream ss;
        ss << line;
        std::string temp;
        while(!ss.eof())
        {
            ss >> temp;
            
            if(std::stringstream(temp) >> n)
            {
                if(bagI < 0) bagI = n - 1;
                else bags[bagI].push_back(n);
            }
            
            temp="";
        }
        bagI = -1;
    }
    getline(input, line);
    size_t u, v;
    while (getline(input, line)) {
        if (line.empty() || line[0] == 'c') continue;

        if (!std::sscanf(line.c_str(), "%zd %zd", &u, &v)) return nullptr;

        G->addEdge(u - 1, v - 1);
    }

    return std::make_shared<TreeDecomposition>(G, bags);
}


std::shared_ptr<EdgeSetGraph> TreeDecomposition::getGraph()
{
    return graph;
}

std::vector<size_t> TreeDecomposition::getBag(size_t bag)
{
    return bags[bag];
}

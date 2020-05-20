#include "homomorphism/edge_set_graph.h"

#include <fstream>
#include <iostream>
#include <stdio.h>

#include "homomorphism/graph6helper.h"
#include "homomorphism/helper_functions.h"

void EdgeSetGraph::clear(size_t v)
{
    verts_ = v;
    edges_ = v;
    std::vector<std::unordered_set<size_t>> nei;
    nei.resize(v);
    neighbours_ = nei;
}

size_t EdgeSetGraph::vertCount()
{
    return verts_;
}

size_t EdgeSetGraph::edgeCount()
{
    return edges_;
}

void EdgeSetGraph::addEdge(size_t u, size_t v)
{
    int oldSize = neighbours_[u].size();
    neighbours_[u].insert(v);
    neighbours_[v].insert(u);
    int newSize = neighbours_[u].size();
    if(oldSize != newSize) {
        edges_++;
    }
}

bool EdgeSetGraph::edgeExist(size_t u, size_t v)
{
    return neighbours_[u].count(v) || neighbours_[v].count(u);
}

bool EdgeSetGraph::isIsomorphic(std::shared_ptr<Graph> g)
{
    return false;
}

std::shared_ptr<Graph> EdgeSetGraph::partition(std::set<size_t>* parts, size_t size)
{
    return nullptr;
}

std::unordered_set<size_t> EdgeSetGraph::getNeighbourhood(size_t v)
{
    return neighbours_[v];
}

std::vector<std::unordered_set<size_t>> EdgeSetGraph::getNeighbourList()
{
    return neighbours_;
}

std::shared_ptr<EdgeSetGraph> EdgeSetGraph::FromGraph(std::shared_ptr<Graph> g) {
    std::shared_ptr<EdgeSetGraph> result = std::make_shared<EdgeSetGraph>(g->vertCount());
    
    for(int u = 0; u < g->vertCount(); u++) {
        for(int v : g->getNeighbourhood(u)) {
            result->addEdge(u, v);
        }
    }
    return result;
}

std::shared_ptr<EdgeSetGraph> EdgeSetGraph::parseGr(std::ifstream& input) {
    std::string line;
    do {
        if(!std::getline(input, line)) return nullptr;
    } while (line[0] == 'c');
    
    size_t n, m;
    if (!std::sscanf(line.c_str(), "p tw %zd %zd", &n, &m)) return nullptr;
    std::shared_ptr <EdgeSetGraph> G = std::make_shared<EdgeSetGraph>(n);

    size_t u, v;
    while (getline(input, line)) {
        if (line.empty() || line[0] == 'c') continue;

        if (!std::sscanf(line.c_str(), "%zd %zd", &u, &v)) return nullptr;

        G->addEdge(u - 1, v - 1);
    }

    return G;
}

std::shared_ptr<EdgeSetGraph> EdgeSetGraph::fromFile(std::string path) {
    std::ifstream input (path);
    
    if (input.is_open()) {
        if (HelperFunctions::hasSuffix(path, ".gr")) {
            return parseGr(input);
        }
        else {
            std::cerr << "ERROR: Unknown graph format for file " << path
                << "\n Current supported formats are: .gr" << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "ERROR: Unable to open file: " << path << std::endl;
        return nullptr;
    }
}

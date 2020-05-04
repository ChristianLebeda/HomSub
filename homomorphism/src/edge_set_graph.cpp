#include "homomorphism/edge_set_graph.h"

#include <stdio.h>

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
    neighbours_[u].insert(v);
    neighbours_[v].insert(u);
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
            result->addEdge(v, v);
        }
    }
    return result;
}

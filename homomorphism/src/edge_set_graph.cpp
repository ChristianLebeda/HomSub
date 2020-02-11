//
//  edge_set_graph.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 11/02/2020.
//

#include <stdio.h>
#include "homomorphism/edge_set_graph.h"

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
    return neighbours_[u].count(v);
}

bool EdgeSetGraph::isIsomorphic(std::shared_ptr<Graph> g)
{
    return false;
}

std::shared_ptr<Graph> EdgeSetGraph::partition(std::set<size_t>* parts, size_t size)
{
    return nullptr;
}

std::set<size_t> EdgeSetGraph::getNeighbourhood(size_t v)
{
    return neighbours_[v];
}

std::vector<std::set<size_t>> EdgeSetGraph::getNeighbourList()
{
    return neighbours_;
}
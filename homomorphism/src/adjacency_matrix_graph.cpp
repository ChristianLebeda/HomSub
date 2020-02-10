//
//  adjacency_matrix_graph.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 10/02/2020.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "homomorphism/adjacency_matrix_graph.h"
#include <sstream>
#include <bitset>
#include <algorithm>
#include "homomorphism/graph6helper.h"

#include <stdio.h>

std::shared_ptr<AdjacencyMatrixGraph> AdjacencyMatrixGraph::fromGraph6(std::string graph6) {
    std::stringstream str(graph6);
    unsigned char input;
    str >> input;

    size_t n = Graph6helper::readN(str);

    bool* matrix = new bool[n * n]{ 0 };

    size_t idx = 0, m = 0;

    for (size_t u = 1; u < n; u++)
    {
        for (size_t v = 0; v < u; v++)
        {
            if (!idx) {
                str >> input;
                input -= 63;
                idx = 6;
            }
            
            if ((input >> --idx) & 0x1) {
                m++;
                matrix[u * n + v] = true;
                matrix[v * n + u] = true;
            }
        }
    }

    return std::make_shared<AdjacencyMatrixGraph>(n, m, matrix);
}

bool has_suffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void AdjacencyMatrixGraph::addEdge(size_t u, size_t v) {
    if (!matrix_[u * vertices_ + v]) edges_++;
    matrix_[u * vertices_ + v] = true;
    matrix_[v * vertices_ + u] = true;
}

std::shared_ptr<AdjacencyMatrixGraph> parseGr(std::ifstream& input) {
    std::string line;
    do {
        if(!std::getline(input, line)) return nullptr;
    } while (line[0] == 'c');
    
    size_t n, m;
    if (!std::sscanf(line.c_str(), "p tw %zd %zd", &n, &m)) return nullptr;
    std::shared_ptr <AdjacencyMatrixGraph> G = std::make_shared<AdjacencyMatrixGraph>(n);

    size_t u, v;
    while (getline(input, line)) {
        if (line.empty() || line[0] == 'c') continue;

        if (!std::sscanf(line.c_str(), "%zd %zd", &u, &v)) return nullptr;

        G->addEdge(u - 1, v - 1);
    }

    return G;
}

std::shared_ptr<AdjacencyMatrixGraph> AdjacencyMatrixGraph::fromFile(std::string path) {
    std::ifstream input (path);
    
    if (input.is_open()) {
        if (has_suffix(path, ".gr")) {
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

std::shared_ptr<AdjacencyMatrixGraph> AdjacencyMatrixGraph::testGraph()
{
    std::shared_ptr<AdjacencyMatrixGraph> g = std::make_shared<AdjacencyMatrixGraph>(4);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    g->addEdge(2, 3);
    g->addEdge(3, 0);

    return g;
}

bool AdjacencyMatrixGraph::edgeExist(size_t u, size_t v)
{
    return matrix_[u * vertices_ + v];
}

bool AdjacencyMatrixGraph::isIsomorphism(std::shared_ptr<AdjacencyMatrixGraph> g, size_t* permutation) {
    for (size_t u = 1; u < vertices_; u++)
    {
        for (size_t v = 0; v < u; v++)
        {
            if (edgeExist(u, v) && !g->edgeExist(permutation[u], permutation[v])) {
                return false;
            }
        }
    }

    return true;
}

bool AdjacencyMatrixGraph::isIsomorphic(std::shared_ptr<AdjacencyMatrixGraph> g)
{
    if (vertices_ != g->vertices_ || edges_ != g->edges_) return false;
    
    size_t* perm = new size_t[vertices_];

    for (size_t i = 0; i < vertices_; i++)
    {
        perm[i] = i;
    }

    do {
        if (isIsomorphism(g, perm)) {
            delete[] perm;
            return true;
        }
    } while (std::next_permutation(perm, perm + vertices_));

    delete[] perm;
    return false;
}

size_t AdjacencyMatrixGraph::vertCount()
{
    return vertices_;
}

size_t AdjacencyMatrixGraph::edgeCount()
{
    return edges_;
}

std::string AdjacencyMatrixGraph::toString()
{
    std::ostringstream out;
    out << "Graph of size (" << vertices_ << "," << edges_ << ")";
    return out.str();
}

std::string AdjacencyMatrixGraph::toGraph6()
{
    std::ostringstream str;
    str << "G" << Graph6helper::N(vertices_);
    std::bitset<6> buffer;
    int idx = 6;
    for (size_t u = 1; u < vertices_; u++)
    {
        for (size_t v = 0; v < u; v++)
        {
            buffer.set(--idx, edgeExist(u, v));
            if (!idx) {
                str << Graph6helper::R(buffer.to_ulong());
                idx = 6;
            }
        }
    }

    if (idx != 6) {
        while (idx) {
            buffer.set(--idx, false);
        }
        str << Graph6helper::R(buffer.to_ulong());
    }

    return str.str();
}

std::shared_ptr<AdjacencyMatrixGraph> AdjacencyMatrixGraph::partition(std::set<size_t>* parts, size_t size) {
    std::shared_ptr<AdjacencyMatrixGraph> newGraph = std::make_shared<AdjacencyMatrixGraph>(size);

    bool edgeFound;
    std::set<size_t>::iterator uit, uend, vit, vend;

    for(size_t u = 0; u < size; u++)
    {
        uend = parts[u].end();
        
        for (size_t v = u + 1; v < size; v++)
        {
            edgeFound = false;
            uit = parts[u].begin();
            vend = parts[v].end();

            while (!edgeFound && uit != uend) {
                vit = parts[v].begin();

                while (vit != vend) {
                    if (edgeExist(*uit, *vit)) {
                        edgeFound = true;
                        break;
                    }
                    vit++;
                }
                uit++;
            }

            if (edgeFound) {
                newGraph->addEdge(u, v);
            }
        }
    }

    return newGraph;
}

void AdjacencyMatrixGraph::prettyPrint(std::ostream& os)
{
    os << "Graph with " << vertices_ << " vertices and " << edges_ << " edges:\n";
    for (size_t u = 0; u < vertices_; u++) {
        os << "[ ";
        for (size_t v = 0; v < vertices_; v++) {
            os << edgeExist(u, v) << " ";
        }
        os << "]" << std::endl;
    }
}

//
//  adjacency_matrix_graph.h
//  homomorphism
//
//  Created by Jonas Mortensen on 10/02/2020.
//

#ifndef ADJACENCY_MATRIX_GRAPH_H_
#define ADJACENCY_MATRIX_GRAPH_H_

#include <string>
#include <memory>
#include <tuple>
#include <set>
#include "graph.h"

class AdjacencyMatrixGraph : public Graph
{
public:
    AdjacencyMatrixGraph(size_t v) : vertices_(v), edges_(0), matrix_(new bool[v * v]{ 0 }) { };
    AdjacencyMatrixGraph(size_t v, size_t e) : vertices_(v), edges_(e), matrix_(new bool[v * v]{ 0 }) { };
    AdjacencyMatrixGraph(size_t v, size_t e, bool* a) : vertices_(v), edges_(e), matrix_(a) { };
    
    static std::shared_ptr<AdjacencyMatrixGraph> fromGraph6(std::string graph6);
    static std::shared_ptr<AdjacencyMatrixGraph> fromFile(std::string path);
    static std::shared_ptr<AdjacencyMatrixGraph> testGraph();
    
    size_t vertCount();
    size_t edgeCount();
    void addEdge(size_t u, size_t v);
    bool edgeExist(size_t u, size_t v);
    bool isIsomorphic(std::shared_ptr<Graph> g);
    std::shared_ptr<Graph> partition(std::set<size_t>* parts, size_t size);

    void operator delete(void* p)
    {
        delete ((AdjacencyMatrixGraph*)p)->matrix_;
        free(p);
    }
    
private:
    size_t vertices_;
    size_t edges_;
    bool* matrix_;

    bool isIsomorphism(std::shared_ptr<Graph> g, size_t* permutation);
};

#endif /* ADJACENCY_MATRIX_GRAPH_H_ */

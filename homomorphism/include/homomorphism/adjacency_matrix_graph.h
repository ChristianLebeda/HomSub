#ifndef HOMOMORPHISM_ADJACENCY_MATRIX_GRAPH_H_
#define HOMOMORPHISM_ADJACENCY_MATRIX_GRAPH_H_

#include "homomorphism/graph.h"

#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

typedef std::vector<unsigned char> Matrix;

class AdjacencyMatrixGraph : public Graph
{
public:
    AdjacencyMatrixGraph(size_t v) : vertices_(v), edges_(0), matrix_(Matrix(v * v, 0)) { };
    AdjacencyMatrixGraph(size_t v, size_t e) : vertices_(v), edges_(e), matrix_(Matrix(v * v,  0 )) { };
    AdjacencyMatrixGraph(size_t v, size_t e, Matrix a) : vertices_(v), edges_(e), matrix_(a) { };
    
    static std::shared_ptr<AdjacencyMatrixGraph> fromGraph6(std::string graph6, bool includeG);
    static std::shared_ptr<AdjacencyMatrixGraph> fromFile(std::string path);
    static std::shared_ptr<AdjacencyMatrixGraph> testGraph();
    static std::shared_ptr<AdjacencyMatrixGraph> parseNautyFormat(const std::string& nauty, size_t n);
    static std::shared_ptr<AdjacencyMatrixGraph> FromGraph(std::shared_ptr<Graph> gr);
    
    void clear(size_t v) override;
    size_t vertCount() override;
    size_t edgeCount() override;
    void addEdge(size_t u, size_t v) override;
    bool edgeExist(size_t u, size_t v) override;
    std::unordered_set<size_t> getNeighbourhood(size_t v) override;
    bool isIsomorphic(std::shared_ptr<Graph> g) override;
    std::shared_ptr<Graph> partition(std::set<size_t>* parts, size_t size) override;
    std::vector<unsigned char>::iterator GetRowIterator(size_t row);

private:
    size_t vertices_;
    size_t edges_;
    Matrix matrix_;

    bool isIsomorphism(std::shared_ptr<Graph> g, size_t* permutation);
};

#endif 

#ifndef GRAPH_GENERATOR_H_
#define GRAPH_GENERATOR_H_

#include "homomorphism/graph.h"
#include <iostream>
#include <memory>


class GraphGenerator
{
public:
    static void CompleteGrid(std::shared_ptr<Graph> g, int rows, int columns);
    void RandomConnectedGrid(std::shared_ptr<Graph> g, int rows, int columns);
    void Path(std::shared_ptr<Graph> g, int length);
    void Cycle(std::shared_ptr<Graph> g, int length);
    void CompleteBinaryTree(std::shared_ptr<Graph> g, int depth);
    void RandomConnectedGraph(std::shared_ptr<Graph> g, size_t verts, size_t edges);
    void EdgeProbabilityGraph(std::shared_ptr<Graph> g, size_t verts, float probability);
private:
    float RandomFloat();
    size_t RandomSize(size_t max);
};

#endif

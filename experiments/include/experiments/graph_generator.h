#ifndef EXPERIMENTS_GRAPH_GENERATOR_H_
#define EXPERIMENTS_GRAPH_GENERATOR_H_

#include "homomorphism/graph.h"

#include <iostream>
#include <memory>

class GraphGenerator
{
public:
    // TODO: Cleanup. decide between static or not and remove one clique implementation
    static void CompleteGrid(std::shared_ptr<Graph> g, int rows, int columns);
    static void RandomConnectedGrid(std::shared_ptr<Graph> g, int rows, int columns);
    static void Path(std::shared_ptr<Graph> g, int length);
    static void Cycle(std::shared_ptr<Graph> g, int length);
    static void CompleteBinaryTree(std::shared_ptr<Graph> g, int depth);
    static void RandomConnectedGraph(std::shared_ptr<Graph> g, size_t verts, size_t edges);
    static void EdgeProbabilityGraph(std::shared_ptr<Graph> g, size_t verts, float probability);
    static void VertexPairs(std::shared_ptr<Graph> g, int pairCount);
    static void Clique(std::shared_ptr<Graph> g, int size);
    static void Star(std::shared_ptr<Graph> g, int size);
    static void MaxDegreeRandomGraph(std::shared_ptr<Graph> g, size_t n, size_t maxDegree);
    static void FromGraph(std::shared_ptr<Graph> destination, std::shared_ptr<Graph> source);
private:
    static float RandomFloat();
    static size_t RandomSize(size_t max);
};

#endif

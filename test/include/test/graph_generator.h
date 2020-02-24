#ifndef GRAPH_GENERATOR_H_
#define GRAPH_GENERATOR_H_

#include "homomorphism/graph.h"
#include <iostream>
#include <memory>


class GraphGenerator
{
public:
    //GraphGenerator();
    static void CompleteGrid(std::shared_ptr<Graph> g, int rows, int columns);
};

#endif

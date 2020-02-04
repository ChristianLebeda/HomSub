#include <iostream>
#include "homomorphism/graph.h"

std::shared_ptr<Graph> Graph::fromGraph6(std::string graph6) {
    return testGraph();
}

std::shared_ptr<Graph> Graph::fromFile(std::string path) {
    return testGraph();
}

std::shared_ptr<Graph> Graph::testGraph()
{
    int v = 4;
    int e = 5;
    return std::make_shared<Graph>(v, e);
}

bool Graph::edgeExist(int u, int v)
{
    //TODO: implement
    return true;
}

bool Graph::isIsomorphic(std::shared_ptr<Graph> g)
{
    //TODO: implement
    return true;
}

int Graph::vertCount()
{
    return vertices;
}

int Graph::edgeCount()
{
    return edges;
}


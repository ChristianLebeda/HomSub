#include <iostream>
#include "homomorphism/Graph.h"

Graph Graph::fromGraph6(std::string graph6) {
    return testGraph();
}

Graph Graph::fromFile(std::string path) {
    return testGraph();
}

Graph Graph::testGraph()
{
    Graph g = Graph(2, 2);
    return g;
}

bool Graph::edgeExist(int u, int v)
{
    //TODO: implement
    return true;
}

bool Graph::isIsomorphic(Graph g)
{
    //TODO: implement
    return true;
}

int Graph::verCount()
{
    return vertices;
}

int Graph::edgeCount()
{
    return edges;
}

Graph::Graph(int v, int e) {
    vertices = v;
    edges = e;
}


#include <iostream>
#include <sstream>
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
    return false;
}

bool Graph::isIsomorphic(std::shared_ptr<Graph> g)
{
    //TODO: implement
    return false;
}

int Graph::vertCount()
{
    return vertices_;
}

int Graph::edgeCount()
{
    return edges_;
}

std::string Graph::toString()
{
    std::ostringstream out;
    out << "Graph of size (" << vertices_ << "," << edges_ << ")";
    return out.str();
}

std::string Graph::toGraph6()
{
    //TODO: implement
    return "";
}


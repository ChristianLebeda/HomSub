#ifndef HOMOMORPHISM_GRAPH_H_
#define HOMOMORPHISM_GRAPH_H_

#include <string>
#include <memory>
#include <tuple>

class Graph
{
public:
    Graph(int v, int e) : vertices_(v), edges_(e) {};
    
    static std::shared_ptr<Graph> fromGraph6(std::string graph6);
    static std::shared_ptr<Graph> fromFile(std::string path);
    static std::shared_ptr<Graph> testGraph();
    
    int vertCount();
    int edgeCount();
    bool edgeExist(int u, int v);
    bool isIsomorphic(std::shared_ptr<Graph> g);
    std::string toString();
    std::string toGraph6();
    
private:
    int vertices_;
    int edges_;
};

#endif

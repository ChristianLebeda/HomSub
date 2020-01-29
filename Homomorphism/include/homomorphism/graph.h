#ifndef Graph_H
#define Graph_H

class Graph
{
public:
    Graph(int v, int e) : vertices(v), edges(e) {};
    
    static std::shared_ptr<Graph> fromGraph6(std::string graph6);
    static std::shared_ptr<Graph> fromFile(std::string path);
    static std::shared_ptr<Graph> testGraph();
    
    int vertCount();
    int edgeCount();
    bool edgeExist(int u, int v);
    bool isIsomorphic(std::shared_ptr<Graph> g);
    
private:
    int vertices;
    int edges;
};

#endif

#ifndef Graph_H
#define Graph_H

class Graph
{
public:
    static Graph fromGraph6(std::string graph6);
    static Graph fromFile(std::string path);
    static Graph testGraph();
    
    int verCount();
    int edgeCount();
    bool edgeExist(int u, int v);
    bool isIsomorphic(Graph g);
    
private:
    Graph(int v, int e);
    
    int vertices;
    int edges;
};

#endif

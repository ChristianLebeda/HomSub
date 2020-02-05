#ifndef HOMOMORPHISM_GRAPH_H_
#define HOMOMORPHISM_GRAPH_H_

#include <string>
#include <memory>
#include <tuple>
#include <set>

class Graph
{
public:
    Graph(size_t v) : vertices_(v), edges_(0), matrix_(new bool[v * v]{ 0 }) { };
    Graph(size_t v, size_t e) : vertices_(v), edges_(e), matrix_(new bool[v * v]{ 0 }) { };
    Graph(size_t v, size_t e, bool* a) : vertices_(v), edges_(e), matrix_(a) { };
    
    static std::shared_ptr<Graph> fromGraph6(std::string graph6);
    static std::shared_ptr<Graph> fromFile(std::string path);
    static std::shared_ptr<Graph> testGraph();
    
    size_t vertCount();
    size_t edgeCount();
    void addEdge(size_t u, size_t v);
    bool edgeExist(size_t u, size_t v);
    bool isIsomorphic(std::shared_ptr<Graph> g);
    std::string toString();
    std::string toGraph6();
    void prettyPrint(std::ostream& os);
    std::shared_ptr<Graph> partition(std::set<size_t>* parts, size_t size);

    void operator delete(void* p)
    {
        delete ((Graph*)p)->matrix_;
        free(p);
    }
    
private:
    size_t vertices_;
    size_t edges_;
    bool* matrix_;
};

#endif

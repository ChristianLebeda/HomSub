
#ifndef TRAVERSAL_SUBGRAPH_COUNTER_H
#define TRAVERSAL_SUBGRAPH_COUNTER_H

#include "graph.h"
#include "spasm.h"

#include <memory>

class TraversalSubgraphCounter {
public:
    TraversalSubgraphCounter(std::shared_ptr<Graph> g, std::shared_ptr<Spasm> spasm) : _g(g), _spasm(spasm) {}
    
    long compute();
private:
    
    std::shared_ptr<Graph> _g;
    std::shared_ptr<Spasm> _spasm;
};

#endif /* traversal_subgraph_counter_h */

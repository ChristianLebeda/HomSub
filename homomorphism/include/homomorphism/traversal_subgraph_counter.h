
#ifndef TRAVERSAL_SUBGRAPH_COUNTER_H
#define TRAVERSAL_SUBGRAPH_COUNTER_H

#include "edge_set_graph.h"
#include "spasm.h"

#include <memory>

class TraversalSubgraphCounter {
public:
    TraversalSubgraphCounter(std::shared_ptr<Spasm> H, std::shared_ptr<Graph> g) : _g(EdgeSetGraph::FromGraph(g)), _spasm(H) {}
    TraversalSubgraphCounter(std::shared_ptr<Spasm> H, std::shared_ptr<EdgeSetGraph> g) : _g(g), _spasm(H) {}
    
    
    long compute();
private:
    
    std::shared_ptr<EdgeSetGraph> _g;
    std::shared_ptr<Spasm> _spasm;
};

#endif /* traversal_subgraph_counter_h */

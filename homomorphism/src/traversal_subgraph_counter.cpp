#include <stdio.h>
#include "homomorphism/traversal_subgraph_counter.h"
#include "homomorphism/traversal_homomorphism_counter.h"
#include "homomorphism/edge_set_graph.h"

long TraversalSubgraphCounter::compute() {
    long count = 0;
    std::shared_ptr<EdgeSetGraph> edgeSetG = EdgeSetGraph::FromGraph(_g);
    for(int i = 0; i < _spasm->size(); i++) {
        
        std::shared_ptr<EdgeSetGraph> spasmEntry = EdgeSetGraph::FromGraph(_spasm->operator[](i).graph);
        
        count += TraversalHomomorphismCounter::Count(edgeSetG, edgeSetG);
    }
    
    return count;
}

#include <stdio.h>
#include "homomorphism/traversal_subgraph_counter.h"
#include "homomorphism/traversal_homomorphism_counter.h"
#include "homomorphism/edge_set_graph.h"

long TraversalSubgraphCounter::compute() {
    long count = 0;
    for(int i = 0; i < _spasm->size(); i++) {
        SpasmEntry spasmEntry = _spasm->operator[](i);
        std::shared_ptr<EdgeSetGraph> spasmGraph  = EdgeSetGraph::FromGraph(spasmEntry.graph);
        count += TraversalHomomorphismCounter::Count(spasmGraph, _g) * spasmEntry.coefficient;
    }
    return count;
}

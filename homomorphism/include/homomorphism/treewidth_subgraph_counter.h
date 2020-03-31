#ifndef HOMOMORPHISM_TREEWIDTHSUBGRAPHCOUNTER_H_
#define HOMOMORPHISM_TREEWIDTHSUBGRAPHCOUNTER_H_

#include "homomorphism/subgraph_counter.h"

#include <memory>

#include "homomorphism/spasm_decomposition.h"

class TreewidthSubgraphCounter : SubgraphCounter
{
public:
	TreewidthSubgraphCounter(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g) : spdc_(spasm), g_(g) {}

	static std::shared_ptr<TreewidthSubgraphCounter> instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g);
	
	long compute() override;
private:
	std::shared_ptr<SpasmDecomposition> spdc_;
	std::shared_ptr<Graph> g_;
};

#endif
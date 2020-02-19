#include "homomorphism/treewidth_subgraph_counter.h"

#include <tuple>

#include "homomorphism/homomorphism_counter.h"

std::shared_ptr<TreewidthSubgraphCounter> TreewidthSubgraphCounter::instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g) {
	return std::make_shared<TreewidthSubgraphCounter>(spasm, g);
}

long TreewidthSubgraphCounter::compute() {
	long count = 0;

	for (size_t i = 0; i < spdc_->size(); i++)
	{
		auto next = (*spdc_)[i];
		auto hc = HomomorphismCounter::instantiate(std::get<0>(next), g_, std::get<1>(next));
		count += hc->compute() * std::get<2>(next);
	}

	return count;
}

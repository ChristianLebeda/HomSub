#include "homomorphism/treewidth_subgraph_counter.h"

#include <tuple>

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/calculation_remapper.h"

std::shared_ptr<TreewidthSubgraphCounter> TreewidthSubgraphCounter::instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g) {
	return std::make_shared<TreewidthSubgraphCounter>(spasm, g);
}

long TreewidthSubgraphCounter::compute() {
	long count = 0;

	for (size_t i = 0; i < spdc_->size(); i++)
	{
		auto next = (*spdc_)[i];
		// TODO: Refactor as settings
		IntroduceHandler ih;
		JoinHandler jh;
		ForgetHandler fh;
		VectorAllocator va;
		CalculationRemapper re;
		auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
		auto hc = HomomorphismCounter(next.graph, g_, ntd, re, fh, ih, jh, va);
		count += hc.compute() * next.coefficient;
	}

	return count;
}

#include "homomorphism/treewidth_subgraph_counter.h"

#include <tuple>

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/configuration_factory.h"

std::shared_ptr<TreewidthSubgraphCounter> TreewidthSubgraphCounter::instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g) {
	return std::make_shared<TreewidthSubgraphCounter>(spasm, g);
}

long TreewidthSubgraphCounter::compute() {
	long count = 0;

    HomomorphismSettings settings = ConfigurationFactory::defaultSettings(g_->vertCount(), spdc_->width());
    PathdecompotisionSettings set = ConfigurationFactory::DefaultPathSettings(g_->vertCount(), spdc_->width());

	for (size_t i = 0; i < spdc_->size(); i++)
	{
		auto next = (*spdc_)[i];
		if(next.decomposition->IsPathDecomposition()) {
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = PathdecompositionCounter(next.graph, g_, npd, set);
            count += hc.compute() * next.coefficient;
		} else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = HomomorphismCounter(next.graph, g_, ntd, settings);
            count += hc.compute() * next.coefficient;
		}
	}

	return count;
}

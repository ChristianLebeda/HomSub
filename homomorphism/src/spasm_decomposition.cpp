#include "homomorphism/spasm_decomposition.h"

#include "homomorphism/tamaki-2017.h"

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::decomposeSpasm(std::shared_ptr<Spasm> sp) {
	Tamaki2017 t;
	
	std::vector<std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>> decomps(sp->size());
	
	for (size_t i = 0; i < sp->size(); i++)
	{
		auto next = (*sp)[i];

		auto ntd = NiceTreeDecomposition::FromTd(t.decompose(next.graph));

		decomps[i] = std::make_tuple(next.graph, ntd, next.coefficient);
	}

	return std::make_shared<SpasmDecomposition>(decomps, sp->graph());
}

size_t SpasmDecomposition::size()
{
	return graphDecomps_.size();
}

std::shared_ptr<Graph> SpasmDecomposition::graph() {
	return graph_;
}

std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>& SpasmDecomposition::operator[](std::size_t position) {
	return graphDecomps_[position];
}
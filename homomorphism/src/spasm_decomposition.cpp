#include "homomorphism/spasm_decomposition.h"

#include "homomorphism/tamaki-2017.h"

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::decomposeSpasm(std::shared_ptr<Spasm> sp) {
	Tamaki2017 t;
	
	std::vector<SpasmDecompositionEntry> decomps(sp->size());
	
	for (size_t i = 0; i < sp->size(); i++)
	{
		auto next = (*sp)[i];

		auto ntd = NiceTreeDecomposition::FromTd(t.decompose(next.graph));

		SpasmDecompositionEntry spe;
		spe.graph = next.graph;
		spe.coefficient = next.coefficient;
		spe.decomposition = ntd;

		decomps[i] = spe;
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

SpasmDecompositionEntry& SpasmDecomposition::operator[](std::size_t position) {
	return graphDecomps_[position];
}
#ifndef HOMOMORPHISM_SPASMDECOMPOSITION_H_
#define HOMOMORPHISM_SPASMDECOMPOSITION_H_

#include "homomorphism/graph.h"
#include "homomorphism/nice_tree_decomposition.h"
#include "homomorphism/spasm.h"

class SpasmDecomposition
{
public:
	SpasmDecomposition(std::vector<std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>> graphs) : graphDecomps_(graphs) {}

	static std::shared_ptr<SpasmDecomposition> decomposeSpasm(std::shared_ptr<Spasm> sp);

	size_t size();
	std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>& operator[](std::size_t position);
private:
	std::vector<std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>> graphDecomps_;
};

#endif

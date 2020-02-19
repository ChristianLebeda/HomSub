#ifndef HOMOMORPHISM_SPASMDECOMPOSITION_H_
#define HOMOMORPHISM_SPASMDECOMPOSITION_H_

#include "homomorphism/graph.h"
#include "homomorphism/nice_tree_decomposition.h"
#include "homomorphism/spasm.h"

class SpasmDecomposition
{
public:
	SpasmDecomposition(std::vector<std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>> graphs, std::shared_ptr<Graph> graph) : graphDecomps_(graphs), graph_(graph) {}

	static std::shared_ptr<SpasmDecomposition> decomposeSpasm(std::shared_ptr<Spasm> sp);

	size_t size();
	std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>& operator[](std::size_t position);
	std::shared_ptr<Graph> graph();
private:
	std::vector<std::tuple<std::shared_ptr<Graph>, std::shared_ptr<NiceTreeDecomposition>, int>> graphDecomps_;
	std::shared_ptr<Graph> graph_;
};

#endif

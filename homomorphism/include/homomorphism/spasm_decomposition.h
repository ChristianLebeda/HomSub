#ifndef HOMOMORPHISM_SPASMDECOMPOSITION_H_
#define HOMOMORPHISM_SPASMDECOMPOSITION_H_

#include "homomorphism/graph.h"
#include "homomorphism/nice_tree_decomposition.h"
#include "homomorphism/spasm.h"

struct SpasmDecompositionEntry : SpasmEntry {
	std::shared_ptr<NiceTreeDecomposition> decomposition;
};

class SpasmDecomposition
{
public:
	SpasmDecomposition(std::vector<SpasmDecompositionEntry> graphs, std::shared_ptr<Graph> graph) : graphDecomps_(graphs), graph_(graph) {}

	static std::shared_ptr<SpasmDecomposition> decomposeSpasm(std::shared_ptr<Spasm> sp);

	size_t size();
	SpasmDecompositionEntry& operator[](std::size_t position);
	std::shared_ptr<Graph> graph();
private:
	std::vector<SpasmDecompositionEntry> graphDecomps_;
	std::shared_ptr<Graph> graph_;
};

#endif

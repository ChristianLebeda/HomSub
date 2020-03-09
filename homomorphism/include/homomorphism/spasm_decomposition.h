#ifndef HOMOMORPHISM_SPASMDECOMPOSITION_H_
#define HOMOMORPHISM_SPASMDECOMPOSITION_H_

#include "homomorphism/graph.h"
#include "homomorphism/spasm.h"
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/tree_width_solver.h"

struct SpasmDecompositionEntry : SpasmEntry {
	std::shared_ptr<TreeDecomposition> decomposition;
};

class SpasmDecomposition
{
public:
	SpasmDecomposition(std::vector<SpasmDecompositionEntry> graphs, std::shared_ptr<Graph> graph, size_t width) : graphDecomps_(graphs), graph_(graph), width_(width) {}

	static std::shared_ptr<SpasmDecomposition> decomposeSpasm(std::shared_ptr<Spasm> sp);
    static std::shared_ptr<SpasmDecomposition> decomposeSpasm(std::shared_ptr<Spasm> sp, TreeWidthSolver& tws);
	static std::shared_ptr<SpasmDecomposition> fromFile(std::string path);
	static std::shared_ptr<SpasmDecomposition> deserialize(std::istream& input);

	size_t size();
	std::string serialize();
	SpasmDecompositionEntry& operator[](std::size_t position);
	std::shared_ptr<Graph> graph();
	size_t width();
private:
	std::vector<SpasmDecompositionEntry> graphDecomps_;
	std::shared_ptr<Graph> graph_;
	size_t width_;
};

#endif

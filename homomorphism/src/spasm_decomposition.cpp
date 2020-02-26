#include "homomorphism/spasm_decomposition.h"

#include "homomorphism/helper_functions.h"
#include "homomorphism/tamaki-2017.h"
#include "adjacency_matrix_graph.cpp"

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::fromFile(std::string path) {
	std::ifstream input(path);

	if (input.is_open()) {
		if (HelperFunctions::hasSuffix(path, ".spsmd")) {
			return deserialize(input);
		}
		else {
			std::cerr << "ERROR: Spasm decomposition must be stored in a .spsmd file" << std::endl;
			return nullptr;
		}
	}
	else {
		std::cerr << "ERROR: Unable to open file: " << path << std::endl;
		return nullptr;
	}
}

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::decomposeSpasm(std::shared_ptr<Spasm> sp) {
	Tamaki2017 t;
	
	std::vector<SpasmDecompositionEntry> decomps(sp->size());
	
	for (size_t i = 0; i < sp->size(); i++)
	{
		auto next = (*sp)[i];

		auto td = t.decompose(next.graph);

		SpasmDecompositionEntry spe;
		spe.graph = next.graph;
		spe.coefficient = next.coefficient;
		spe.decomposition = td;

		decomps[i] = spe;
	}

	return std::make_shared<SpasmDecomposition>(decomps, sp->graph());
}

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::deserialize(std::istream& input) {
	std::string line;
	do {
		if (!std::getline(input, line)) return nullptr;
	} while (line[0] == 'c');

	size_t size;
	if (!std::sscanf(line.c_str(), "sp %zd", &size)) return nullptr;
	std::vector<SpasmDecompositionEntry> graphs;

	int coef;
	std::string g6;
	for (size_t i = 0; i < size; i++)
	{
		getline(input, line);

		std::stringstream str(line);

		str >> coef >> g6;

		SpasmDecompositionEntry spe;
		spe.coefficient = coef;
		spe.graph = AdjacencyMatrixGraph::fromGraph6(g6);

		graphs.push_back(spe);
	}

	for (size_t i = 0; i < size; i++)
	{
		graphs[i].decomposition = TreeDecomposition::parseTd(input);
	}

	return std::make_shared<SpasmDecomposition>(graphs, graphs[0].graph);
}

std::string SpasmDecomposition::serialize() {
	// Current format: 
	// First line: spdc [c] [n] [m]
	// c is the number of graphs
	// n and m are number of vertices and edges of original graph
	std::ostringstream str;
	str << "sp " << graphDecomps_.size() << " " << graph_->vertCount() << " "
		<< graph_->edgeCount() << "\n";

	std::vector<SpasmDecompositionEntry>::iterator it = graphDecomps_.begin();

	while (it != graphDecomps_.end()) {
		SpasmDecompositionEntry next = *it;
		str << next.coefficient << " " << next.graph->toGraph6() << "\n";
		it++;
	}

	it = graphDecomps_.begin();

	while (it != graphDecomps_.end()) {
		SpasmDecompositionEntry next = *it;
		str << next.decomposition->toTd();
		it++;
	}

	return str.str();
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
#include "homomorphism/spasm_decomposition.h"

#include "homomorphism/helper_functions.h"
#include "homomorphism/tamaki-2017.h"
#include "homomorphism/adjacency_matrix_graph.h"

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
	size_t width = 0;
	
	for (size_t i = 0; i < sp->size(); i++)
	{
		auto next = (*sp)[i];

		auto td = t.decompose(next.graph);

		SpasmDecompositionEntry spe;
		spe.graph = next.graph;
		spe.coefficient = next.coefficient;
		spe.decomposition = td;
        if(width < spe.decomposition->getWidth()) {
            width = spe.decomposition->getWidth();
        }

		decomps[i] = spe;
	}

	return std::make_shared<SpasmDecomposition>(decomps, sp->graph(), width);
}

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::decomposeSpasm(std::shared_ptr<Spasm> sp, TreeWidthSolver& tws) {

    std::vector<std::shared_ptr<Graph>> graphs;

    for(size_t i = 0; i < sp->size(); i++) {
        graphs.push_back((*sp)[i].graph);
    }

    std::vector<std::shared_ptr<TreeDecomposition>> decomps = tws.decomposeAll(graphs);

    if(decomps.size() != sp->size()) {
        std::cerr << "ERROR: Different sizes of tree decompositions("
            << decomps.size() << ") and spasm(" << sp->size() << ")" << std::endl;
        return nullptr;
    }

    std::vector<SpasmDecompositionEntry> entries(sp->size());
    size_t width = 0;

    for (size_t i = 0; i < sp->size(); i++)
    {
        auto old = (*sp)[i];

        SpasmDecompositionEntry spe;
        spe.graph = old.graph;
        spe.coefficient = old.coefficient;
        spe.decomposition = decomps[i];
        if(width < spe.decomposition->getWidth()) {
            width = spe.decomposition->getWidth();
        }

        entries[i] = spe;
    }

    return std::make_shared<SpasmDecomposition>(entries, sp->graph(), width);
}

std::shared_ptr<SpasmDecomposition> SpasmDecomposition::deserialize(std::istream& input) {
	std::string line;
	do {
		if (!std::getline(input, line)) return nullptr;
	} while (line[0] == 'c');

	size_t size, n, m, w;
	if (!std::sscanf(line.c_str(), "sp %zd %zd %zd %zd", &size, &n, &m, &w)) return nullptr;
	std::vector<SpasmDecompositionEntry> graphs;

	int coef;
	std::string g6;

    getline(input, g6);
    std::shared_ptr<Graph> g = AdjacencyMatrixGraph::fromGraph6(g6, false);

	for (size_t i = 0; i < size; i++)
	{
		getline(input, line);

		std::stringstream str(line);

		str >> coef >> g6;

		SpasmDecompositionEntry spe;
		spe.coefficient = coef;
		spe.graph = AdjacencyMatrixGraph::fromGraph6(g6, false);

		graphs.push_back(spe);
	}

	for (size_t i = 0; i < size; i++)
	{
		graphs[i].decomposition = TreeDecomposition::parseTd(input);
	}

	return std::make_shared<SpasmDecomposition>(graphs, g, w);
}

std::string SpasmDecomposition::serialize() {
	// Current format: 
	// First line: spdc [c] [n] [m] [w]
	// c is the number of graphs
	// n and m are number of vertices and edges of original graph
	// w is the maximum treewidth of all decompositions
	std::ostringstream str;
	str << "sp " << graphDecomps_.size() << " " << graph_->vertCount() << " "
		<< graph_->edgeCount() << " " << width_ << "\n";

	str << graph_->toGraph6(false) << "\n";

	std::vector<SpasmDecompositionEntry>::iterator it = graphDecomps_.begin();

	while (it != graphDecomps_.end()) {
		SpasmDecompositionEntry next = *it;
		str << next.coefficient << " " << next.graph->toGraph6(false) << "\n";
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

size_t SpasmDecomposition::width() {
    return width_;
}
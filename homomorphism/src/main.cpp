#include "homomorphism/main.h"

#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/nauty.h"
#include "homomorphism/tamaki_runner.h"
#include "homomorphism/treewidth_subgraph_counter.h"

std::shared_ptr<Spasm> Main::spasmFromGraph(std::shared_ptr<Graph> h) {
    Nauty n;
	return Spasm::createSpasm(h, n);
}

std::shared_ptr<Spasm> Main::spasmFromGraph(std::string filename) {
	std::shared_ptr<Graph> g = AdjacencyMatrixGraph::fromFile(filename);
	
	return spasmFromGraph(g);
}

std::shared_ptr<SpasmDecomposition> Main::decomposedSpasmFromGraph(std::shared_ptr<Graph> h) {
	return decomposedSpasmFromSpasm(spasmFromGraph(h));
}

std::shared_ptr<SpasmDecomposition> Main::decomposedSpasmFromGraph(std::string filename) {
	return decomposedSpasmFromSpasm(spasmFromGraph(filename));
}

std::shared_ptr<SpasmDecomposition> Main::decomposedSpasmFromSpasm(std::shared_ptr<Spasm> sp) {
    TamakiRunner tr;
    return SpasmDecomposition::decomposeSpasm(sp, tr);
}

std::shared_ptr<SpasmDecomposition> Main::decomposedSpasmFromSpasm(std::string filename) {
	return SpasmDecomposition::decomposeSpasm(Spasm::fromFile(filename));
}

long long Main::subgraphsGraph(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromGraph(H), G);
}

long long Main::subgraphsGraph(std::string filenameH, std::string filenameG) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromGraph(filenameH), AdjacencyMatrixGraph::fromFile(filenameG));
}


long long Main::subgraphsSpasmGraph(std::shared_ptr<Spasm> H, std::shared_ptr<Graph> G) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromSpasm(H), G);
}


long long Main::subgraphsSpasmGraph(std::string filenameH, std::string filenameG) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromSpasm(filenameH), AdjacencyMatrixGraph::fromFile(filenameG));
}


long long Main::subgraphsSpasmDecompositionGraph(std::shared_ptr<SpasmDecomposition> SpasmDecompH, std::shared_ptr<Graph> G) {
	std::shared_ptr<TreewidthSubgraphCounter> autoCounter = TreewidthSubgraphCounter::instatiate(SpasmDecompH, SpasmDecompH->graph());
	
	std::shared_ptr<TreewidthSubgraphCounter> embCounter = TreewidthSubgraphCounter::instatiate(SpasmDecompH, G);
	
    long autoMorph = autoCounter->compute();
    
	return autoMorph > 0 ? embCounter->compute() / autoCounter->compute() : 0;
}


long long Main::subgraphsSpasmDecompositionGraph(std::string filenameSpasmDecompH, std::string filenameG) {
	std::cerr << "ERROR: Spasm decomposition is not serializable yet" << std::endl;
	
	return 0;
}


long long Main::subgraphsFiles(std::string filenameH, std::string filenameG) {
	std::shared_ptr<Graph> g = AdjacencyMatrixGraph::fromFile(filenameG);

	if (!g) {
		std::cerr << "ERROR: Could not load graph G. Aborting." << std::endl;
		return 0;
	}

	if (HelperFunctions::hasSuffix(filenameH, ".gr")) {
		return subgraphsGraph(AdjacencyMatrixGraph::fromFile(filenameH), g);
	}
	else if (HelperFunctions::hasSuffix(filenameH, ".spsm")) {
		return subgraphsSpasmGraph(Spasm::fromFile(filenameH), g);
	}

	std::cerr << "ERROR: Unknown file formats for first argument: " << filenameH << std::endl;
	std::cerr << "ERROR: Supported formats: .gr .spsm" << std::endl;
	return 0;
}

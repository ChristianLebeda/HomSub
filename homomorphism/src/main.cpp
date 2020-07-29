#include <assert.h>
#include "homomorphism/main.h"

#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/nauty.h"
#include "homomorphism/tamaki_runner.h"
#include "homomorphism/edge_consistency_precomputation.h"
#include "homomorphism/treewidth_subgraph_counter.h"
#include "homomorphism/traversal_subgraph_counter.h"
#include "homomorphism/configuration_factory.h"
#include "homomorphism/pathdecomposition_counter.h"
#include "homomorphism/dynamic_programming_counter.h"

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

long long Main::subgraphsGraphJoined(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G) {
    auto originalSpasm = decomposedSpasmFromGraph(H);
    
    std::vector<SpasmDecompositionEntry> treeWidth;
    std::vector<SpasmEntry> maxDegree;
    
    for(int i = 0; i < originalSpasm->size(); i++) {
        auto spasmDecomp = originalSpasm->operator[](i);
        
        if (spasmDecomp.decomposition->getWidth() > 2) {
            maxDegree.push_back(spasmDecomp);
        } else {
            treeWidth.push_back(spasmDecomp);
        }
    }
    
    TraversalSubgraphCounter maxDegreeEmbCounter(std::make_shared<Spasm>(maxDegree, H), G);
    
    long embs = maxDegreeEmbCounter.compute();
    
    std::shared_ptr<TreewidthSubgraphCounter> treeWidthEmbCounter = TreewidthSubgraphCounter::instatiate(std::make_shared<SpasmDecomposition>(treeWidth, H, 2), G, true);
    
    embs += treeWidthEmbCounter->compute();
    
    std::shared_ptr<TreewidthSubgraphCounter> autoCounter = TreewidthSubgraphCounter::instatiate(originalSpasm, H, true);
    
    return embs / autoCounter->compute();
}

long long Main::subgraphsGraph(std::string filenameH, std::string filenameG) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromGraph(filenameH), AdjacencyMatrixGraph::fromFile(filenameG));
}

long long Main::subgraphsGraphNonpooled(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G) {
    return subgraphsSpasmDecompositionGraphNonpooled(decomposedSpasmFromGraph(H), G);
}

long long Main::subgraphsGraphMaxDegree(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G) {
    std::shared_ptr<Spasm> spasm = spasmFromGraph(H);
    
    TraversalSubgraphCounter autoCounter(spasm, H);
    TraversalSubgraphCounter embCounter(spasm, G);
    
    long autoMorphisms = autoCounter.compute();
    
    return embCounter.compute() / autoMorphisms;
}



long long Main::subgraphsSpasmGraph(std::shared_ptr<Spasm> H, std::shared_ptr<Graph> G) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromSpasm(H), G);
}


long long Main::subgraphsSpasmGraph(std::string filenameH, std::string filenameG) {
	return subgraphsSpasmDecompositionGraph(decomposedSpasmFromSpasm(filenameH), AdjacencyMatrixGraph::fromFile(filenameG));
}

long long subgraphsSpasmGraphMaxDegree(std::shared_ptr<Spasm> H, std::shared_ptr<Graph> G) {
    TraversalSubgraphCounter autoCounter(H, G);
    TraversalSubgraphCounter embCounter(H, H->graph());
    
    long autoMorphisms = autoCounter.compute();
    
    return embCounter.compute() / autoMorphisms;
}

long long Main::subgraphsSpasmDecompositionGraph(std::shared_ptr<SpasmDecomposition> SpasmDecompH, std::shared_ptr<Graph> G) {
	std::shared_ptr<TreewidthSubgraphCounter> autoCounter = TreewidthSubgraphCounter::instatiate(SpasmDecompH, SpasmDecompH->graph(), true);
	
	std::shared_ptr<TreewidthSubgraphCounter> embCounter = TreewidthSubgraphCounter::instatiate(SpasmDecompH, G, true);
	
    long autoMorph = autoCounter->compute();

    if(autoMorph < 0) {
        std::cerr << "ERROR: Automorphisms should alway be positive";
        assert(false);
    }

	return embCounter->compute() / autoMorph;
}

long long Main::subgraphsSpasmDecompositionGraphNonpooled(std::shared_ptr<SpasmDecomposition> SpasmDecompH, std::shared_ptr<Graph> G) {
    std::shared_ptr<TreewidthSubgraphCounter> autoCounter = TreewidthSubgraphCounter::instatiate(SpasmDecompH, SpasmDecompH->graph(), false);

    std::shared_ptr<TreewidthSubgraphCounter> embCounter = TreewidthSubgraphCounter::instatiate(SpasmDecompH, G, false);

    long autoMorph = autoCounter->compute();

    if(autoMorph < 0) {
        std::cerr << "ERROR: Automorphisms should alway be positive";
        assert(false);
    }

    return embCounter->compute() / autoMorph;
}

long long Main::subgraphsSpasmDecompositionGraph(std::string filenameSpasmDecompH, std::string filenameG) {
    auto spdc = SpasmDecomposition::fromFile(filenameSpasmDecompH);
    auto g = AdjacencyMatrixGraph::fromFile(filenameG);

	return subgraphsSpasmDecompositionGraph(spdc, g);
}

long long Main::subgraphsGraphParallel(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G, int threadCount) {
    std::shared_ptr<SpasmDecomposition> spd = decomposedSpasmFromGraph(H);
    
    std::shared_ptr<TreewidthSubgraphCounter> autoCounter = TreewidthSubgraphCounter::instatiate(spd, H, true);
    std::shared_ptr<TreewidthSubgraphCounter> embCounter = TreewidthSubgraphCounter::instatiate(spd, G, true);
    
    long autoMorph = autoCounter->computeParallel(threadCount);

    if(autoMorph < 0) {
        std::cerr << "ERROR: Automorphisms should alway be positive";
        assert(false);
    }
    
    return embCounter->computeParallel(threadCount) / autoMorph;
}


long long Main::subgraphsFiles(std::string filenameH, std::string filenameG) {
	auto g = AdjacencyMatrixGraph::fromFile(filenameG);

	if (!g) {
		std::cerr << "ERROR: Could not load graph G. Aborting." << std::endl;
		return 0;
	}

	if (HelperFunctions::hasSuffix(filenameH, ".gr")) {
        auto h = AdjacencyMatrixGraph::fromFile(filenameH);
        if (!h) {
            std::cerr << "ERROR: Could not load graph H. Aborting." << std::endl;
            return 0;
    	}
		return subgraphsGraph(h, g);
	} else if (HelperFunctions::hasSuffix(filenameH, ".spsm")) {
        auto s = Spasm::fromFile(filenameH);
        if (!s) {
            std::cerr << "ERROR: Could not load spasm H. Aborting." << std::endl;
            return 0;
    	}
        return subgraphsSpasmGraph(s, g);
	}

	std::cerr << "ERROR: Unknown file formats for first argument: " << filenameH << std::endl;
	std::cerr << "ERROR: Supported formats: .gr .spsm" << std::endl;
	return 0;
}


long long Main::homomorphismsFiles(std::string filenameH, std::string filenameG) {
	std::shared_ptr<Graph> g = AdjacencyMatrixGraph::fromFile(filenameG);

	if (!g) {
		std::cerr << "ERROR: Could not load graph G. Aborting." << std::endl;
		return 0;
	}

	if (HelperFunctions::hasSuffix(filenameH, ".gr")) {
        std::shared_ptr<Graph> h = AdjacencyMatrixGraph::fromFile(filenameH);
        if (!h) {
            std::cerr << "ERROR: Could not load graph H. Aborting." << std::endl;
            return 0;
    	}

        TamakiRunner tr;
        auto td = tr.decompose(h);
        auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g, td->getWidth());
        auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g, td->getWidth());
        auto settings = ConfigurationFactory::DefaultPrecomputedSettings(g->vertCount(), td->getWidth(), pre1, pre2);

        if(td->IsPathDecomposition()) {
            auto npd = NicePathDecomposition::FromTd(td);
            auto hc = PathdecompositionCounter(h, g, npd, settings.second);
            return hc.compute();
        } else {
            auto ntd = NiceTreeDecomposition::FromTd(td);
            auto hc = DynamicProgrammingCounter(h, g, ntd, settings.first);
            return hc.compute();
        }
	} else if (HelperFunctions::hasSuffix(filenameH, ".spsm")) {
		std::cerr << "ERROR: Homcounting for spasm not implemented. Aborting." << std::endl;
        return 0;
		// return subgraphsSpasmGraph(Spasm::fromFile(filenameH), g);
	}

	std::cerr << "ERROR: Unknown file formats for first argument: " << filenameH << std::endl;
	std::cerr << "ERROR: Supported formats: .gr .spsm" << std::endl;
	return 0;
}

long long Main::EmbeddingsSpasmGraphDegree(std::string filenameH, std::string filenameG) {
    std::shared_ptr<Spasm> sp = Spasm::fromFile(filenameH);
    std::shared_ptr<Graph> g = EdgeSetGraph::fromFile(filenameG);

    return TraversalSubgraphCounter(sp, g).compute();
}

long long Main::EmbeddingsSpasmDecompositionGraph(std::string filenameH, std::string filenameG) {
    std::shared_ptr<SpasmDecomposition> spdc = SpasmDecomposition::fromFile(filenameH);
    std::shared_ptr<Graph> g = AdjacencyMatrixGraph::fromFile(filenameG);

    return TreewidthSubgraphCounter::instatiate(spdc, g, true)->compute();
}

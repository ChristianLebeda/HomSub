#ifndef HOMOMORPHISM_MAIN_H_
#define HOMOMORPHISM_MAIN_H_

#include <memory>
#include <string>

#include "homomorphism/graph.h"
#include "homomorphism/spasm.h"
#include "homomorphism/spasm_decomposition.h"

class Main
{
public:
    static std::shared_ptr<Spasm> spasmFromGraph(std::shared_ptr<Graph> h);
    static std::shared_ptr<Spasm> spasmFromGraph(std::string filename);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromGraph(std::shared_ptr<Graph> h);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromGraph(std::string filename);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromSpasm(std::shared_ptr<Spasm> sp);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromSpasm(std::string filename);
    static long long subgraphsGraphParallel(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G, int threadCount);
    static long long subgraphsGraph(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G);
    static long long subgraphsGraphJoined(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G);
    static long long subgraphsGraphNonpooled(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G);
    static long long subgraphsGraph(std::string filenameH, std::string filenameG);
    static long long subgraphsGraphMaxDegree(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G);
    static long long subgraphsSpasmGraph(std::shared_ptr<Spasm> H, std::shared_ptr<Graph> G);
    static long long subgraphsSpasmGraph(std::string filenameH, std::string filenameG);
    static long long subgraphsSpasmDecompositionGraph(std::shared_ptr<SpasmDecomposition> SpasmDecompH, std::shared_ptr<Graph> G);
    static long long subgraphsSpasmDecompositionGraphNonpooled(std::shared_ptr<SpasmDecomposition> SpasmDecompH, std::shared_ptr<Graph> G);
    static long long subgraphsSpasmDecompositionGraph(std::string filenameSpasmDecompH, std::string filenameG);
    static long long subgraphsFiles(std::string filenameH, std::string filenameG);
    static long long EmbeddingsSpasmGraphDegree(std::string filenameH, std::string filenameG);
    static long long EmbeddingsSpasmDecompositionGraph(std::string filenameH, std::string filenameG);
};

#endif

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
    static std::shared_ptr<Spasm> spasmFromGraph(std::shared_ptr<Graph> filename);
    static std::shared_ptr<Spasm> spasmFromGraph(std::string filename);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromGraph(std::shared_ptr<Graph> filename);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromGraph(std::string filename);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromSpasm(std::shared_ptr<Spasm> filename);
    static std::shared_ptr<SpasmDecomposition> decomposedSpasmFromSpasm(std::string filename);
    static size_t subgraphsGraph(std::shared_ptr<Graph> H, std::shared_ptr<Graph> G);
    static size_t subgraphsGraph(std::string filenameH, std::string filenameG);
    static size_t subgraphsSpasmGraph(std::shared_ptr<Spasm> H, std::shared_ptr<Graph> G);
    static size_t subgraphsSpasmGraph(std::string filenameH, std::string filenameG);
    static size_t subgraphsSpasmDecompositionGraph(std::shared_ptr<SpasmDecomposition> SpasmDecompH, std::shared_ptr<Graph> G);
    static size_t subgraphsSpasmDecompositionGraph(std::string filenameSpasmDecompH, std::string filenameG);
    static size_t subgraphsFiles(std::string filenameH, std::string filenameG);
};

#endif

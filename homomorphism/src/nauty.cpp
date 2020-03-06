#include "homomorphism/nauty.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/pipe_handler.h"
#include "homomorphism/third_party.h"

std::vector<SpasmEntry> Nauty::joinIsomorphic(const std::vector<SpasmEntry>& spasm) {
    std::ostringstream str;

    // Canonical mode
    str << "c\n";

    for (auto &entry : spasm) {
        // Define graph
        str << "n=" << entry.graph->vertCount() << " g " << entry.graph->toNautyFormat();

        // Execute nauty and display graph
        str << "x b\n";
    }

    str << "q\n";

    std::ofstream graphs;

    //TODO: Use tmp files
    graphs.open("nauty.in");
    graphs << str.str();
    graphs.close();

    std::string command = ThirdParty::directory() + "nauty/dreadnaut < nauty.in > nauty.out";
    system(command.c_str());

    remove("nauty.in");

    std::string line;
    std::ifstream output("nauty.out");
    std::vector<CanonicalEntry> canons;
    if (output.is_open()) {
        for (auto &i : spasm) {
            canons.push_back({HelperFunctions::trimDreadnautOutput(output, i.graph->vertCount()), i.graph->vertCount(), i.coefficient});
        }
    } else std::cout << "Unable to open file";

    sort(canons.begin(), canons.end());

    std::vector<SpasmEntry> joined;

    std::string last;
    SpasmEntry next = SpasmEntry();

    for(auto& a : canons) {
        if(last != a.graph) {
            last = a.graph;
            next = {AdjacencyMatrixGraph::parseNautyFormat(a.graph, a.n), a.coefficient};
            joined.push_back(next);
        } else {
            next.coefficient += a.coefficient;
        }
    }

    return joined;
}

void Nauty::Test(std::vector<SpasmEntry> spasm) {
    PipeHandler pipe = PipeHandler::openNauty();

    std::ostringstream str;

    // Canonical mode
    str << "c\n";

    for(auto& entry : spasm) {
        // Define graph
        str << "n=" << entry.graph->vertCount() << "\n";
        str << "g\n" << entry.graph->toNautyFormat() << "\n";

        // Execute nauty and display graph
        str << "x\n b\n";
    }

    str << "q";;

    pipe.writeLine(str.str());

    // Has to close input pipe
    // pipe.closePipes();

    for (auto & i : spasm) {
       std::cout << HelperFunctions::trimDreadnautOutput(pipe, i.graph->vertCount()) << std::endl;
    }
}

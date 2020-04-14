#include "homomorphism/nauty.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/pipe_handler.h"
#include "homomorphism/third_party.h"

std::vector<NautyEntry> Nauty::combineEntries(std::vector<NautyEntry> entries) {
    std::vector<NautyEntry> joined;

    sort(entries.begin(), entries.end());

    std::string last;
    NautyEntry* next = nullptr;

    for(auto& e : entries) {
        if(last != e.graph) {
            last = e.graph;
            joined.push_back(e);
            next = &joined.back();
        } else {
            next->coefficient += e.coefficient;
        }
    }

    return joined;
}

std::vector<SpasmEntry> Nauty::convertToSpasm(const std::vector<NautyEntry>& entries) {
    std::vector<SpasmEntry> spasm;

    spasm.reserve(spasm.size());
    for(auto& entry : entries) {
        spasm.push_back({AdjacencyMatrixGraph::parseNautyFormat(entry.graph, entry.n), entry.coefficient});
    }

    return spasm;
}

std::vector<SpasmEntry> Nauty::joinIsomorphic(std::unordered_map<std::string, int>& entries) {
    std::ostringstream str;

    // Canonical mode
    str << "c\n";

    for (auto &entry : entries) {
        // Define graph
        str << "n=" << std::count(entry.first.begin(), entry.first.end(), ';')
                << " g " << entry.first;

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

    std::vector<NautyEntry> spasm;
    spasm.reserve(entries.size());

    if (output.is_open()) {
        // Update graphs with new canonical labelling
        for (auto &entry : entries) {
            size_t n = std::count(entry.first.begin(), entry.first.end(), ';');
            spasm.push_back({HelperFunctions::trimDreadnautOutput(output, n), n, entry.second});
        }
    } else std::cout << "Unable to open file";

    remove("nauty.out");

    std::vector<SpasmEntry> joined = convertToSpasm(combineEntries(spasm));

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

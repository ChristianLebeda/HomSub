#include "homomorphism/spasm.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/nauty.h"

std::shared_ptr<Spasm> Spasm::fromFile(std::string path) {
    std::ifstream input(path);

    if (input.is_open()) {
        if (HelperFunctions::hasSuffix(path, ".spsm")) {
            return deserialize(input);
        }
        else {
            std::cerr << "ERROR: Spasm must be stored in a .spsm file" << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "ERROR: Unable to open file: " << path << std::endl;
        return nullptr;
    }
}

std::shared_ptr<Spasm> Spasm::createSpasm(std::shared_ptr<Graph> H, SpasmReducer& red) {
    std::vector<SpasmEntry> graphs{ {H, 1} };
    std::set<size_t>* parts = new std::set<size_t>[H->vertCount()]{};
    
    addPartitioningsRec(H, graphs, parts, 0, 0);

    delete[] parts;

    graphs = red.joinIsomorphic(graphs);

    auto lamb = [](SpasmEntry& g1, SpasmEntry& g2) -> bool
    {
        return g1.graph->vertCount() == g2.graph->vertCount() ?
               g1.graph->edgeCount() > g2.graph->edgeCount() :
               g1.graph->vertCount() > g2.graph->vertCount();
    };

    sort(graphs.begin(), graphs.end(), lamb);

    return std::make_shared<Spasm>(graphs, H);
}

std::vector<SpasmEntry> Spasm::joinIsomorphic(std::vector<SpasmEntry> graphs) {
    std::vector<SpasmEntry> joined;
    std::vector<bool> used(graphs.size(), false);

    auto lamb = [](SpasmEntry& g1, SpasmEntry& g2) -> bool
    {
        return g1.graph->vertCount() == g2.graph->vertCount() ?
               g1.graph->edgeCount() > g2.graph->edgeCount() :
               g1.graph->vertCount() > g2.graph->vertCount();
    };
    sort(graphs.begin(), graphs.end(), lamb);

    size_t sizev, sizee;
    int coef;
    std::shared_ptr<Graph> gi, gj;

    for (size_t i = 0; i < graphs.size(); i++)
    {        
        if (used[i]) continue;

        gi = graphs[i].graph;
        coef = graphs[i].coefficient;
        sizev = gi->vertCount();
        sizee = gi->edgeCount();

        for (size_t j = i + 1; j < graphs.size(); j++)
        {
            if (used[j]) continue;
            gj = graphs[j].graph;
            if (gj->vertCount() != sizev || gj->edgeCount() != sizee) {
                break;
            }
            if (gi->isIsomorphic(gj)) {
                coef += graphs[j].coefficient;
                used[j] = true;
            }
        }

        joined.push_back({ gi, coef });
    }

    return joined;
}

void Spasm::addPartitioningsRec(std::shared_ptr<Graph> H, std::vector<SpasmEntry>& graphs, std::set<size_t>* parts, size_t next, size_t size) {
    if (H->vertCount() == next) {
        if (H->vertCount() != size) {
            std::shared_ptr<Graph> quotient = H->partition(parts, size);
            // Use closed formula to find coefficient
            // product B in parts (|B| - 1)!
            // Sign is determined based on size of quotient graph
            int coef = (H->vertCount() - size) % 2 ? -1 : 1;
            for (size_t i = 0; i < size; i++)
            {
                size_t B = parts[i].size() - 1;
                while (1 < B) {
                    coef *= B;
                    B--;
                }
            }
            graphs.push_back({ quotient, coef });
        }
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        std::set<size_t>::iterator it = parts[i].begin();

        bool isIndependent = true;

        while (it != parts[i].end()) {
            if (H->edgeExist(*it, next)) {
                isIndependent = false;
                break;
            }
            it++;
        }

        if (isIndependent) {
            parts[i].insert(next);
            addPartitioningsRec(H, graphs, parts, next + 1, size);
            parts[i].erase(next);
        }
    }

    parts[size].insert(next);
    addPartitioningsRec(H, graphs, parts, next + 1, size + 1);
    parts[size].erase(next);
}

std::shared_ptr<Spasm> Spasm::testSpasm()
{
    //TODO: Add testspasm
    return nullptr;
}

std::shared_ptr<Graph> Spasm::graph() {
    return g_;
}

size_t Spasm::size()
{
    return graphs_.size();
}

SpasmEntry& Spasm::operator[](std::size_t position) {
    return graphs_[position];
}

std::shared_ptr<Spasm> Spasm::deserialize(std::istream& input) {
    std::string line;
    do {
        if (!std::getline(input, line)) return nullptr;
    } while (line[0] == 'c');

    size_t size;
    if (!std::sscanf(line.c_str(), "sp %zd", &size)) return nullptr;
    std::vector<SpasmEntry> graphs;

    int coef;
    std::string g6;

    getline(input, g6);
    std::shared_ptr<Graph> g = AdjacencyMatrixGraph::fromGraph6(g6, false);

    for (size_t i = 0; i < size; i++)
    {
        getline(input, line);

        std::stringstream str(line);

        str >> coef >> g6;

        graphs.push_back({ AdjacencyMatrixGraph::fromGraph6(g6, false), coef });
    }

    return std::make_shared<Spasm>(graphs, g);
}

std::string Spasm::serialize() {
    // Current format: 
    // First line: sp [c] [n] [m]
    // c is the number of graphs
    // n and m are number of vertices and edges of original graph
    std::ostringstream str;
    str << "sp " << graphs_.size() << " " << graphs_[0].graph->vertCount() << " "
        << graphs_[0].graph->edgeCount() << "\n";

    str << g_->toGraph6(false) << "\n";

    std::vector<SpasmEntry>::iterator it = graphs_.begin();

    while (it != graphs_.end()) {
        SpasmEntry next = *it;
        str << next.coefficient << " " << next.graph->toGraph6(false) << "\n";
        it++;
    }

    return str.str();
}

void Spasm::prettyPrint(std::ostream& os) {
    os << "Spasm with " << graphs_.size() << " graphs.\n";
    std::vector<SpasmEntry>::iterator it;

    for (it = graphs_.begin(); it != graphs_.end(); it++)
    {
        os << "Coefficient " << it->coefficient << ": ";
        it->graph->prettyPrint(os);
    }
}

std::string Spasm::toString()
{
    std::ostringstream out;
    out << "Spasm of " << size() << "graphs";
    return out.str();
}

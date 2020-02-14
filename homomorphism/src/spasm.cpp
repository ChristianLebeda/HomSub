#include <sstream>
#include <algorithm>
#include <fstream>
#include "homomorphism/spasm.h"
#include <homomorphism\helper_functions.h>
#include <homomorphism/adjacency_matrix_graph.h>

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

std::shared_ptr<Spasm> Spasm::createSpasm(std::shared_ptr<Graph> H) {
    std::vector<std::pair<std::shared_ptr<Graph>, int>> graphs { std::make_pair(H, 1) };
    std::set<size_t>* parts = new std::set<size_t>[H->vertCount()]{};
    
    addPartitioningsRec(H, graphs, parts, 0, 0);

    auto lamb = [](std::pair< std::shared_ptr<Graph>, int >& g1, std::pair< std::shared_ptr<Graph>, int >& g2) -> bool
    {
        return g1.first->vertCount() == g2.first->vertCount() ?
            g1.first->edgeCount() > g2.first->edgeCount() :
            g1.first->vertCount() > g2.first->vertCount();
    };
    sort(graphs.begin(), graphs.end(), lamb);

    delete[] parts;

    graphs = joinIsomorphic(graphs);

    return std::make_shared<Spasm>(graphs);
}

std::vector<std::pair<std::shared_ptr<Graph>, int>> Spasm::joinIsomorphic(std::vector<std::pair<std::shared_ptr<Graph>, int>> graphs) {
    std::vector<std::pair<std::shared_ptr<Graph>, int>> joined;
    std::vector<bool> used(graphs.size(), false);

    size_t sizev, sizee, coef;
    std::shared_ptr<Graph> gi, gj;

    for (size_t i = 0; i < graphs.size(); i++)
    {        
        if (used[i]) continue;

        gi = graphs[i].first;
        coef = graphs[i].second;
        sizev = gi->vertCount();
        sizee = gi->edgeCount();

        for (size_t j = i + 1; j < graphs.size(); j++)
        {
            if (used[j]) continue;
            gj = graphs[j].first;
            if (gj->vertCount() != sizev || gj->edgeCount() != sizee) {
                break;
            }
            if (gi->isIsomorphic(gj)) {
                coef += graphs[j].second;
                used[j] = true;
            }
        }

        joined.push_back(std::make_pair(gi, coef));
    }

    return joined;
}

void Spasm::addPartitioningsRec(std::shared_ptr<Graph> H, std::vector<std::pair<std::shared_ptr<Graph>, int>>& graphs, std::set<size_t>* parts, size_t next, size_t size) {
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
            graphs.push_back(std::make_pair(quotient, coef));
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
    std::vector<std::pair<std::shared_ptr<Graph>, int> > vec;
    return std::make_shared<Spasm>(vec);
}

size_t Spasm::size()
{
    return graphs_.size();
}

std::pair< std::shared_ptr<Graph>, int>& Spasm::operator[](std::size_t position) {
    return graphs_[position];
}

std::shared_ptr<Spasm> Spasm::deserialize(std::istream& input) {
    std::string line;
    do {
        if (!std::getline(input, line)) return nullptr;
    } while (line[0] == 'c');

    size_t size;
    if (!std::sscanf(line.c_str(), "sp %zd", &size)) return nullptr;
    std::vector<std::pair<std::shared_ptr<Graph>, int>> graphs;

    size_t coef;
    std::string g6;
    for (size_t i = 0; i < size; i++)
    {
        getline(input, line);

        std::stringstream str(line);

        str >> coef >> g6;

        graphs.push_back(std::make_pair(AdjacencyMatrixGraph::fromGraph6(g6), coef));
    }

    return std::make_shared<Spasm>(graphs);
}

std::string Spasm::serialize() {
    // Current format: 
    // First line: sp [c] [n] [m]
    // c is the number of graphs
    // n and m are number of vertices and edges of original graph
    std::ostringstream str;
    str << "sp " << graphs_.size() << " " << graphs_[0].first->vertCount() << " "
        << graphs_[0].first->edgeCount() << "\n";

    std::vector<std::pair<std::shared_ptr<Graph>, int>>::iterator it = graphs_.begin();

    while (it != graphs_.end()) {
        std::pair<std::shared_ptr<Graph>, int> next = *it;
        str << next.second << " " << next.first->toGraph6() << "\n";
        it++;
    }

    return str.str();
}

void Spasm::prettyPrint(std::ostream& os) {
    os << "Spasm with " << graphs_.size() << " graphs.\n";
    std::vector<std::pair< std::shared_ptr<Graph>, int>>::iterator it;

    for (it = graphs_.begin(); it != graphs_.end(); it++)
    {
        os << "Coefficient " << it->second << ": ";
        it->first->prettyPrint(os);
    }
}

std::string Spasm::toString()
{
    std::ostringstream out;
    out << "Spasm of " << size() << "graphs";
    return out.str();
}

#include <sstream>
#include "homomorphism/spasm.h"

std::shared_ptr<Spasm> Spasm::fromFile(std::string path) {
    return testSpasm();
}

std::shared_ptr<Spasm> Spasm::createSpasm(std::shared_ptr<Graph> H) {
    std::vector<std::pair<std::shared_ptr<Graph>, int>> graphs;
    std::set<size_t>* parts = new std::set<size_t>[H->vertCount()]{};
    
    addPartitioningsRec(H, graphs, parts, 0, 0);

    delete[] parts;

    return std::make_shared<Spasm>(graphs);
}

void Spasm::addPartitioningsRec(std::shared_ptr<Graph> H, std::vector<std::pair<std::shared_ptr<Graph>, int>>& graphs, std::set<size_t>* parts, size_t next, size_t size) {
    if (H->vertCount() == next) {
        if (H->vertCount() != size) {
            std::shared_ptr<Graph> quotient = H->partition(parts, size);
            // Use closed formula to find coefficient
            // product B in parts (|B| - 1)!
            // Sign is determined based on size of quotient graph
            int coef = (H->vertCount() - size) % 2 ? 1 : -1;
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

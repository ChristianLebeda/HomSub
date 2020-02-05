#include <sstream>
#include "homomorphism/spasm.h"

std::shared_ptr<Spasm> Spasm::fromFile(std::string path) {
    return testSpasm();
}

std::shared_ptr<Spasm> Spasm::createSpasm(Graph H) {
    return testSpasm();
}

std::shared_ptr<Spasm> Spasm::testSpasm()
{
    std::vector<std::pair<Graph, int> > vec;
    return std::make_shared<Spasm>(vec);
}

size_t Spasm::size()
{
    return graphs_.size();
}

std::pair<Graph, int>& Spasm::operator[](std::size_t position) {
    return graphs_[position];
}

std::string Spasm::toString()
{
    std::ostringstream out;
    out << "Spasm of " << size() << "graphs";
    return out.str();
}

#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include "homomorphism/graph.h"
#include "homomorphism/spasm.h"

std::shared_ptr<Spasm> Spasm::fromFile(std::string path) {
    return testSpasm();
}

std::shared_ptr<Spasm> Spasm::createSpasm(Graph H) {
    return testSpasm();
}

std::shared_ptr<Spasm> Spasm::testSpasm()
{
    return std::make_shared<Spasm>(std::vector<std::tuple<Graph, int>>());
}

size_t Spasm::size()
{
    return graphs_.size();
}

std::tuple<Graph, int>& Spasm::operator[](std::size_t position) {
    return graphs_[position];
}

std::string Spasm::toString()
{
    std::ostringstream out;
    out << "Spasm of " << size() << "graphs";
    return out.str();
}

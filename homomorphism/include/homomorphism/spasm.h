#ifndef HOMOMORPHISM_SPASM_H_
#define HOMOMORPHISM_SPASM_H_

#include <iostream>
#include <vector>
#include <tuple>
#include "homomorphism/graph.h"

class Spasm
{
public:
    Spasm(std::vector<std::pair<Graph, int> > g) : graphs_(g) {};

    static std::shared_ptr<Spasm> fromFile(std::string path);
    static std::shared_ptr<Spasm> createSpasm(Graph H);
    static std::shared_ptr<Spasm> testSpasm();

    std::size_t size();
    std::pair<Graph, int>& operator[](std::size_t position);
    std::string toString();

private:
    std::vector<std::pair<Graph, int> > graphs_;
};

#endif

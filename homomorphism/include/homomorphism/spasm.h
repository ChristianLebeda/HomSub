#ifndef HOMOMORPHISM_SPASM_H_
#define HOMOMORPHISM_SPASM_H_

#include <iostream>
#include <vector>

#include "homomorphism/graph.h"

struct SpasmEntry
{
    std::shared_ptr<Graph> graph;
    int coefficient;
};

class Spasm
{
public:
    Spasm(std::vector<SpasmEntry> g) : graphs_(g) {};

    static std::shared_ptr<Spasm> fromFile(std::string path);
    static std::shared_ptr<Spasm> createSpasm(std::shared_ptr<Graph> H);
    static std::shared_ptr<Spasm> testSpasm();

    std::size_t size();
    SpasmEntry& operator[](std::size_t position);
    std::string toString();
    std::string serialize();
    std::shared_ptr<Graph> graph();
    void prettyPrint(std::ostream& os);

private:
    std::vector<SpasmEntry> graphs_;

    static std::shared_ptr<Spasm> deserialize(std::istream& input);
    static void addPartitioningsRec(std::shared_ptr<Graph> H, std::vector<SpasmEntry>& graphs, std::set<size_t>* parts, size_t next, size_t size);
    static std::vector<SpasmEntry> joinIsomorphic(std::vector<SpasmEntry> graphs);
};

#endif

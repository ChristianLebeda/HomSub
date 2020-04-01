#ifndef HOMOMORPHISM_SPASM_H_
#define HOMOMORPHISM_SPASM_H_

#include <iostream>
#include <unordered_map>
#include <vector>

#include "homomorphism/graph.h"
#include "homomorphism/spasm_reducer.h"

class Spasm
{
public:
    Spasm(std::vector<SpasmEntry> entries, std::shared_ptr<Graph> g) : graphs_(entries), g_(g) {};

    static std::shared_ptr<Spasm> fromFile(std::string path);
    static std::shared_ptr<Spasm> createSpasm(std::shared_ptr<Graph> H, SpasmReducer& red);
    static std::shared_ptr<Spasm> testSpasm();
    static std::shared_ptr<Spasm> deserialize(std::istream& input);

    std::size_t size();
    SpasmEntry& operator[](std::size_t position);
    std::string toString();
    std::string serialize();
    std::shared_ptr<Graph> graph();
    void prettyPrint(std::ostream& os);

private:
    std::vector<SpasmEntry> graphs_;
    std::shared_ptr<Graph> g_;

    static void addPartitioningsRec(std::shared_ptr<Graph> H, std::unordered_map<std::string, int>& graphs, std::set<size_t>* parts, size_t next, size_t size);
    static std::vector<SpasmEntry> joinIsomorphic(std::vector<SpasmEntry> graphs);
};

#endif

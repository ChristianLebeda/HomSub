#ifndef HOMOMORPHISM_SPASM_H_
#define HOMOMORPHISM_SPASM_H_

#include <iostream>
#include <tuple>
#include <vector>

#include "homomorphism/graph.h"

class Spasm
{
public:
    Spasm(std::vector<std::pair<std::shared_ptr<Graph>, int> > g) : graphs_(g) {};

    static std::shared_ptr<Spasm> fromFile(std::string path);
    static std::shared_ptr<Spasm> createSpasm(std::shared_ptr<Graph> H);
    static std::shared_ptr<Spasm> testSpasm();

    std::size_t size();
    std::pair< std::shared_ptr<Graph>, int>& operator[](std::size_t position);
    std::string toString();
    std::string serialize();
    void prettyPrint(std::ostream& os);

private:
    std::vector<std::pair<std::shared_ptr<Graph>, int> > graphs_;

    static std::shared_ptr<Spasm> deserialize(std::istream& input);
    static void addPartitioningsRec(std::shared_ptr<Graph> H, std::vector<std::pair<std::shared_ptr<Graph>, int>>& graphs, std::set<size_t>* parts, size_t next, size_t size);
    static std::vector<std::pair<std::shared_ptr<Graph>, int>> joinIsomorphic(std::vector<std::pair<std::shared_ptr<Graph>, int>> graphs);
};

#endif

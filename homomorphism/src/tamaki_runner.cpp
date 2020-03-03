#include "homomorphism/tamaki_runner.h"

#include <iostream>
#include <sstream>

std::shared_ptr<TreeDecomposition> TamakiRunner::decompose(std::shared_ptr<Graph> g)
{
    std::vector<std::shared_ptr<Graph>> gr(1, g);

    auto td = decomposeAll(gr);

    return td[0];
}

std::vector<std::shared_ptr<TreeDecomposition>> TamakiRunner::decomposeAll(std::vector<std::shared_ptr<Graph>> graphs)
{
    std::ostringstream str;

    for(auto& g : graphs) {
        str << g->toGr();
    }

    //TODO: Use tmp files
    std::ofstream in;
    in.open("tam.in");
    in << str.str();
    in.close();

    // TODO: Might want to increase heap for JVM
    system("java TamakiRunner < tam.in > tam.out");
    remove("tam.in");

    std::string line;
    std::ifstream output("tam.out");
    std::vector<std::shared_ptr<TreeDecomposition>> decomps;

    if (output.is_open()) {
        for (size_t i = 0; i < graphs.size(); i++) {
            decomps.push_back(TreeDecomposition::parseTd(output));
        }
        output.close();
    } else std::cerr << "Unable to open file" << std::endl;

    return decomps;
}

#include "homomorphism/tamaki-2017.h"

#include <fstream>
#include <iostream>

std::shared_ptr<TreeDecomposition> Tamaki2017::decompose(std::shared_ptr<Graph> g)
{
    //This might not be the smartest way, but it is the easiest way
    
    
    std::ofstream graphFile;
    
    graphFile.open ("tempGraph.gr");
    graphFile << g->toGr();
    graphFile.close();
    system("java -Xmx30g -Xms30g -Xss10m tw.exact.MainDecomposer < tempGraph.gr > tempTree.td");
    remove("tempGraph.gr");
    
    std::string line;
    std::ifstream tdFile ("tempTree.td");
    std::shared_ptr<TreeDecomposition> td;
    if (tdFile.is_open())
    {
        td = TreeDecomposition::parseTd(tdFile);
        tdFile.close();
    } else std::cout << "Unable to open file";
    
    remove("tempTree.td");
    return td;
}

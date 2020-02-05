//
//  tamaki-2017.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 04/02/2020.
//

#include "homomorphism/tamaki-2017.h"
#include <iostream>
#include <fstream>

std::shared_ptr<TreeDecomposition> Tamaki2017::decompose(std::shared_ptr<Graph> g)
{
    //This might not be the smartest, but the easiest to get to run
    
    
    std::ofstream graphFile;
    std::string test = "p tw 5 4\n1 2\n2 3\n3 4\n4 5";
    
    graphFile.open ("graph.gr");
    graphFile << test;
    graphFile.close();
    system("java -Xmx30g -Xms30g -Xss10m tw.exact.MainDecomposer < graph.gr > tree.td");
    remove("graph.gr");
    
    std::string line;
    std::ifstream tdFile ("tree.td");
    if (tdFile.is_open())
    {
      while ( getline (tdFile,line) )
      {
        std::cout << line << '\n';
      }
      tdFile.close();
    } else std::cout << "Unable to open file";
    remove("tree.td");
    
    std::vector<std::vector<int>> b;
    std::shared_ptr<Graph> tree = Graph::testGraph();
    std::shared_ptr<TreeDecomposition> td = std::make_shared<TreeDecomposition>(tree, b);
    return td;
}

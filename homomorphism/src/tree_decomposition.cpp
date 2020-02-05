//
//  tree_decomposition.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 05/02/2020.
//

#include <iostream>
#include "homomorphism/tree_decomposition.h"
#include <fstream>

std::shared_ptr<TreeDecomposition> TreeDecomposition::fromTdFile(std::string path)
{
    std::string line;
    std::ifstream tdFile (path);
    if (tdFile.is_open())
    {
        
        
      while ( getline (tdFile,line) )
      {
        std::cout << line << '\n';
      }
      tdFile.close();
    } else return nullptr;
    return nullptr;
}

int TreeDecomposition::test()
{
    return 0;
}

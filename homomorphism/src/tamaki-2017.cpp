//
//  tamaki-2017.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 04/02/2020.
//

#include "homomorphism/tamaki-2017.h"

std::string Tamaki2017::decompose(std::shared_ptr<Graph> g)
{
    //This might not be the smartest, but the easiest to get to run
    
    //Write graph to tmp file
    //Feed to Tamaki-2017
    //Read output and remove tmp file
    
    system("java -Xmx30g -Xms30g -Xss10m tw.exact.MainDecomposer < ex001.gr > ex001.td");
    return "This is a td";
}

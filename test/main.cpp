#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "test/graph_generator.h"
#include <time.h>
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/tamaki-2017.h"
#include "test/test_runner.h"
#include <unordered_map>

int main(int argc, char *argv[])
{
    if(argc % 2 == 0) {
        std::cout << "Not key-value pairs" << std::endl;
        return 1;
    }
    
    std::unordered_map<std::string, std::string> argMap;
    
    for(int i = 1; i < argc; i = i+2) {
        argMap[argv[i]] = argv[i+1];
    }
    
    //Initialise random seed
    int randomSeed = time(NULL);
    if(argMap.count("-seed")) {
        randomSeed = std::stoi(argMap["-seed"]);
    }
    srand(randomSeed);
    
    //run single test
    if(argMap.count("-test")) {
        int testNum = std::stoi(argMap["-test"]);
        TestRunner::RunTest(testNum);
    }
    
    //Run several tests
    if(argMap.count("-mask")) {
        int testMask = std::stoi(argMap["-mask"]);
        TestRunner::RunTestFromMask(testMask);
    }
    
    
    return 0;
}

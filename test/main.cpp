#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "test/graph_generator.h"
#include <time.h>
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/tamaki-2017.h"
#include "test/test_runner.h"

int main(int argc, char *argv[])
{
    int testMask = -1;
    int randomSeed = time(NULL);
    if(argc > 1) {
        std::string firstArg = argv[1];
        if(firstArg.compare("run") == 0) {
            std::cout << "run algo on given graph" << std::endl;
            return 0;
        } else if (firstArg.compare("-s") == 0) {
            randomSeed = std::stoi(argv[2]);
            if(argc > 3) {
                testMask = std::stoi(argv[3]);
            }
        } else {
            testMask = std::stoi(firstArg);
        }
    }
    //initialise random seed
    srand(randomSeed);
    //Run tests
    TestRunner::RunTestFromMask(testMask);
    
    
    return 0;
}

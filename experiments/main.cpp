#include <iostream>
#include "homomorphism/graph.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "experiments/graph_generator.h"
#include <time.h>
#include "homomorphism/tree_decomposition.h"
#include "homomorphism/tamaki-2017.h"
#include "homomorphism/tamaki_runner.h"
#include "experiments/test_runner.h"
#include <unordered_map>
#include "experiments/test_settings.h"
#include "homomorphism/main.h"

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "use -help" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::string> argMap;
    
    TestSettings settings;
    
    for(int i = 1; i < argc; i = i+2) {
        std::string arg = argv[i];
        if(arg.compare("-help") == 0) {
            TestRunner::PrintHelp();
        } else {
            std::string value = argv[i+1];
            argMap[arg] = value;
        }
    }
    
    
    //Set TreeWidthSolver settings
    if(argMap.count("-tws")) {
        if(argMap["-tws"].compare("tamaki") == 0) {
            TamakiRunner t;
            settings.SetTWS(&t);
        }
    } else {
        TamakiRunner t;
        settings.SetTWS(&t);
    }
    
    //Set random seed
    int randomSeed = time(NULL);
    if(argMap.count("-seed")) {
        randomSeed = std::stoi(argMap["-seed"]);
        settings.SetRandomSeed(randomSeed);
    }
    
    //Set single test
    if(argMap.count("-test")) {
        int testNum = std::stoi(argMap["-test"]);
        settings.SetSingleTest(testNum);
    }
    
    //Set several tests
    if(argMap.count("-mask")) {
        int testMask = std::stoi(argMap["-mask"]);
        settings.SetTestMask(testMask);
    }
    
    if(argMap.count("-run")) {
        std::cout << "This should run the agorithm on files " << argMap["-run"] << std::endl;
    }
    
    if(argMap.count("-time")) {
        int time = std::stoi(argMap["-time"]);
        settings.SetPrTestTime(time);
    } else {
        settings.SetPrTestTime(10);
    }
    
    TestLogger logger(std::cout);
    
    TestRunner runner(settings, logger);
    runner.Run();
    
    return 0;
}

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
#include "experiments/readable_logger.h"
#include "experiments/csv_logger.h"

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "use -help" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::string> argMap;
    
    TestSettings settings;
    
    for(int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(arg.compare("-help") == 0) {
            TestRunner::PrintHelp();
            return 0;
        } else {
            if(i+1 < argc) {
                std::string value = argv[i+1];
                if (value.rfind("-", 0) != 0) {
                    argMap[arg] = "";
                } else {
                    argMap[arg] = value;
                }
            } else {
                argMap[arg] = "";
            }
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
    
    if(argMap.count("-all")) {
        settings.SetRunAll(true);
    }
    
    
    if(argMap.count("-run")) {
        std::cout << "This should run the agorithm on files provided but does nothing"<< std::endl;
    }
    
    if(argMap.count("-time")) {
        int time = std::stoi(argMap["-time"]);
        settings.SetPrTestTime(time);
    } else {
        settings.SetPrTestTime(5);
    }
    
    TestLogger *logger;
    
    if(argMap.count("-csv")) {
        CSVLogger csvLogger(std::cout);
        logger = &csvLogger;
    } else {
        ReadableLogger readLogger(std::cout);
        logger = &readLogger;
    }
    
    TestRunner runner(settings, *logger);
    runner.Run();
    
    return 0;
}

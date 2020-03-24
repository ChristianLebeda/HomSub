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

    std::set<std::string> arguments {"-help", "-test", "-group", "-all", "-csv", "-seed", "-time",
                                     "-createspasm", "-convertgr", "-in", "-out"};

    for(int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(arguments.find(arg) == arguments.end()) {
            std::cout << "Unknown argument " << arg << std::endl;
            std::cout << "Use -help" << std::endl;
            return 1;
        }
        if(arg.compare("-help") == 0) {
            TestRunner::PrintHelp();
            return 0;
        } else {
            if(i+1 < argc) {
                std::string value = argv[i+1];
                
                if (value.rfind('-', 0) != 0) {
                    argMap[arg] = value;
                    i++;
                } else {
                    argMap[arg] = "";
                }
            } else {
                argMap[arg] = "";
            }
        }
    }
    
    
    //Set TreeWidthSolver settings
    if(argMap.count("-tws")) {
        if(argMap["-tws"] == "tamaki") {
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

    if(argMap.count("-all") || !argMap.count("-test")) {
        settings.SetRunAll(true);
    }
    
    if(argMap.count("-run")) {
        std::cout << "This should run the algorithm on files provided but does nothing"<< std::endl;
    }
    
    if(argMap.count("-time")) {
        int time = std::stoi(argMap["-time"]);
        settings.SetPrTestTime(time);
    } else {
        settings.SetPrTestTime(5);
    }

    settings.SetRunSpasmCreation(argMap.count("-createspasm"));

    settings.SetRunConvertGr(argMap.count("-convertgr"));

    if(argMap.count("-in")) {
        settings.SetIn(argMap["-in"]);
    }

    if(argMap.count("-out")) {
        settings.SetOut(argMap["-out"]);
    }

    if(argMap.count("-group")) {
        if(argMap["-group"] == "a" || argMap["-group"] == "(a)" || argMap["-group"] == "all") {
            settings.SetGroup(true, true);
        } else if(argMap["-group"] == "c" || argMap["-group"] == "(c)" || argMap["-group"] == "correctness") {
            settings.SetGroup(true, false);
        } else if(argMap["-group"] == "p" || argMap["-group"] == "(p)" || argMap["-group"] == "performance") {
            settings.SetGroup(false, true);
        } else {
            std::cout << "Unknown value for group. Use: correctness, performance or all" << std::endl;
            return 1;
        }
    } else {
        settings.SetGroup(false, true);
    }
    
    TestLogger *logger;

    if(argMap.count("-csv")) {
        CSVLogger csvLogger(std::cout);
        logger = &csvLogger;
    } else {
        ReadableLogger readLogger(std::cout);
        logger = &readLogger;
    }
    
    settings.SetRepetitions(5);
    
    TestRunner runner(settings, *logger);
    runner.Run();
    
    return 0;
}

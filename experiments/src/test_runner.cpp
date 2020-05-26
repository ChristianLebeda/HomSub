#include "experiments/test_runner.h"

#include <iostream>
#include <experiments/graph_generator.h>

#include "experiments/test_factory.h"
#include "experiments/graph_files_experiments.h"
#include "experiments/sanity_test_factory.h"

#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/helper_functions.h"
#include "homomorphism/main.h"


void TestRunner::Run() {
    logger_.NotifyRunStart();

    if(settings_.GetCreateGraphSize() != 0) {
        srand(settings_.GetRandomSeed());
        auto g = AdjacencyMatrixGraph::testGraph();
        for(int i = 0; i < settings_.GetRepetitions(); i++) {
            GraphGenerator::EdgeProbabilityGraph(g, settings_.GetCreateGraphSize(), settings_.GetEdgeProbability());
            std::cout << g->toGr();
        }
        return;
    }

    if(settings_.GetCreateSpasm()) {
        auto sp = Main::spasmFromGraph(settings_.GetIn())->serialize();
        HelperFunctions::saveToFile(sp, settings_.GetOut());
        return;
    }

    if(settings_.GetCreateSpasmDecmop()) {
        auto sp = Main::decomposedSpasmFromGraph(settings_.GetIn())->serialize();
        HelperFunctions::saveToFile(sp, settings_.GetOut());
        return;
    }

    if(settings_.GetRunTimed()) {
        auto start = std::chrono::steady_clock::now();
        long long count = 0;
        if(settings_.GetTimedDegree()) {
            count = Main::EmbeddingsSpasmGraphDegree(settings_.GetIn(), settings_.GetOut());
        } else {
            count = Main::EmbeddingsSpasmDecompositionGraph(settings_.GetIn(), settings_.GetOut());
        }
        auto stop = std::chrono::steady_clock::now();
        auto time = ((double)(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000;
        std::cout << (settings_.GetTimedDegree() ? "degree," : "treewidth,") << settings_.GetOut()
                        << "," << count << ",," << time << std::endl;
        return;
    }

    if(settings_.GetRunCount()) {
        std::cout << Main::subgraphsFiles(settings_.GetIn(), settings_.GetOut()) << std::endl;
        return;
    }

    if(settings_.GetRunCreateSpasm()) {
        GraphFilesExperiments::CreateAllSpasms(settings_, logger_);
        return;
    }
    if(settings_.GetRunConvertGr()) {
        GraphFilesExperiments::ConvertAllToGr(settings_, logger_);
        return;
    }

    if(settings_.GetRunSanity()) {
        SanityTestFactory::runAllTests(settings_, logger_);
        logger_.NotifyFailed();
    }

    if(settings_.GetRunPerformance()) {
        srand(settings_.GetRandomSeed());
        if (settings_.ShouldRunSingleTest()) {
            RunTest(settings_.GetSingleTest());
        }

        if (settings_.GetRunAll()) {
            RunTestFromList(TestFactory::GetAllTests());
        }
    }
}

void TestRunner::RunTestFromMask(int mask)
{
    for(int i = 0; i < 32; i++) {
        if((1 << i) & mask) {
            RunTest(i);
        }
    }
}

void TestRunner::RunTest(int testNum)
{
    std::function<void(TestSettings&, TestLogger&)> t = TestFactory::GetTest(testNum);
    if(t) {
        t(settings_, logger_);
    }
}

void TestRunner::RunTestFromList(const std::vector<std::function<void (TestSettings &, TestLogger &)>>& tests) {
    for(auto t : tests) {
        t(settings_, logger_);
    }
}

void TestRunner::PrintHelp()
{
    std::cout
        << "Give the program a sequence of parameters in order to adjust execution. Supported parameters are described here:\n" << std::endl
        << "NOTE: This list is currently incomplete" << std::endl
        << "-help      | Get this help screen" << std::endl
        //<< "-list     | List all tests" << std::endl
        << "-test t    | Run a specific test based on its number" << std::endl
        << "-group g   | Runs a test group: correctness (c), performance (p) or all (a)" << std::endl
        << "             Performance group is default" << std::endl
        << "-rep r     | Specify how maby times the repeated experiments should run" << std::endl
        << "-csv       | Output test results formatted as csv" << std::endl
        << "-seed      | Specify the seed used by the random graphs" << std::endl
        << "-time      | Set the timout limit for incremental tests" << std::endl
        << "-in        | Specifies the path to the input file" << std::endl
        << "-out       | Specifies the path for the output file" << std::endl
        << "-spasms    | Converts all graphs from the input file to spasms" << std::endl
        << "-convertgr | Converts the input file from graph6 to .gr format" << std::endl
        //<< "-mask m   | Run several tests masked by given signed integer (-1 runs all)" << std::endl
        //<< "-run h g | Count occurences of pattern h in host g" << std::endl
        << std::endl;
}

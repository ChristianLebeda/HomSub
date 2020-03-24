#include "experiments/graph_files_experiments.h"

#include <chrono>

#include "experiments/test_logger.h"
#include "homomorphism/adjacency_matrix_graph.h"
#include "homomorphism/main.h"


void GraphFilesExperiments::CreateAllSpasms(TestSettings &settings, TestLogger &logger) {
    logger.NotifyTestStart("CreatingSpasms");

    if(settings.GetIn().empty() || settings.GetOut().empty()) {
        std::cerr << "You must specify an input and output file" << std::endl;
        return;
    }

    std::ifstream input(settings.GetIn());
    std::ofstream output(settings.GetOut());
    auto test = settings.GetIn();
    std::string line;
    int duration, idx = 0;
    auto start = std::chrono::steady_clock::now(), stop = std::chrono::steady_clock::now();

    if(!input.is_open()) {
        std::cerr << "Could not open file " << settings.GetIn() << std::endl;
        return;
    }

    while(input >> line) {
        start = std::chrono::steady_clock::now();

        output << Main::spasmFromGraph(AdjacencyMatrixGraph::fromGraph6(line, false))->serialize();

        stop = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        logger.Log("", idx, duration);
        idx++;
    }
}

void GraphFilesExperiments::ConvertAllToGr(TestSettings &settings, TestLogger &logger) {
    logger.NotifyTestStart("ConvertGr");

    if(settings.GetIn().empty() || settings.GetOut().empty()) {
        std::cerr << "You must specify an input and output file" << std::endl;
        return;
    }

    std::string line;
    std::ifstream input(settings.GetIn());
    std::ofstream output(settings.GetOut());
    auto start = std::chrono::steady_clock::now();

    if(!input.is_open()) {
        std::cerr << "Could not open file " << settings.GetIn() << std::endl;
        return;
    }

    while(input >> line) {
        output << AdjacencyMatrixGraph::fromGraph6(line, false)->toGr();
    }

    auto stop = std::chrono::steady_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    logger.Log("", 0, duration);
}

#ifndef EXPERIMENTS_GRAPH_FILES_EXPERIMENTS_H
#define EXPERIMENTS_GRAPH_FILES_EXPERIMENTS_H

#include "experiments/test_settings.h"
#include "experiments/test_logger.h"

class GraphFilesExperiments {
public:
    static void CreateAllSpasms(TestSettings& settings, TestLogger& logger);
    static void ConvertAllToGr(TestSettings& settings, TestLogger& logger);
};

#endif

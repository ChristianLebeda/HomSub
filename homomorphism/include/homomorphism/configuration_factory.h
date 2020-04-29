#ifndef HOMOMORPHISM_CONFIGURATION_FACTORY_H
#define HOMOMORPHISM_CONFIGURATION_FACTORY_H

#include "homomorphism/dynamic_programming_counter.h"
#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/pathdecomposition_counter.h"
#include "homomorphism/edge_consistency_precomputation.h"

class ConfigurationFactory {
public:
    static HomomorphismSettings defaultSettings(size_t n, size_t maxWidth);
    static HomomorphismSettings PrecomputedSettings(size_t n, size_t maxWidth,
                                                    std::shared_ptr<EdgeConsistencyPrecomputation> precomputation);
    static HomomorphismSettings iteratorRemapper(size_t n, size_t maxWidth);
    static PathdecompotisionSettings DefaultPathSettings(size_t n, size_t maxWidth);
    static PathdecompotisionSettings PrecomputedPathSettings(size_t n, size_t maxWidth,
                                                        std::shared_ptr<EdgeConsistencyPrecomputation> precomputation);
    static DynamicProgrammingSettings DefaultDynamicSettings(size_t n, size_t maxWidth,
                                             std::shared_ptr<EdgeConsistencyPrecomputation> precomputationLeast,
                                             std::shared_ptr<EdgeConsistencyPrecomputation> precomputationSecond);
};

#endif

#ifndef HOMOMORPHISM_CONFIGURATION_FACTORY_H
#define HOMOMORPHISM_CONFIGURATION_FACTORY_H

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/pathdecomposition_counter.h"

class ConfigurationFactory {
public:
    static HomomorphismSettings defaultSettings(size_t n, size_t maxWidth);
    static HomomorphismSettings iteratorRemapper(size_t n, size_t maxWidth);
    static PathdecompotisionSettings DefaultPathSettings(size_t n, size_t maxWidth);
};

#endif

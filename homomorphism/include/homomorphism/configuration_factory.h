#ifndef HOMOMORPHISM_CONFIGURATION_FACTORY_H
#define HOMOMORPHISM_CONFIGURATION_FACTORY_H

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/pathdecomposition_counter.h"

class ConfigurationFactory {
public:
    static HomomorphismSettings defaultSettings();
    static HomomorphismSettings iteratorRemapper();
    static PathdecompotisionSettings DefaultPathSettings();
};

#endif

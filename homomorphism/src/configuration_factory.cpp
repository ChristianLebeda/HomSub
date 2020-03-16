#include "homomorphism/configuration_factory.h"

#include "homomorphism/calculation_remapper.h"
#include "homomorphism/iterator_remapper.h"


HomomorphismSettings ConfigurationFactory::defaultSettings() {
    return {std::make_shared<CalculationRemapper>(), std::make_shared<ForgetHandler>(),
            std::make_shared<IntroduceHandler>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}


HomomorphismSettings ConfigurationFactory::iteratorRemapper() {
    return {std::make_shared<IteratorRemapper>(), std::make_shared<ForgetHandler>(),
            std::make_shared<IntroduceHandler>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}

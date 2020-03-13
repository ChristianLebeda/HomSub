#include "homomorphism/configuration_factory.h"

#include "homomorphism/calculation_remapper.h"

HomomorphismSettings ConfigurationFactory::defaultSettings() {
    return {std::make_shared<CalculationRemapper>(), std::make_shared<ForgetHandler>(),
            std::make_shared<IntroduceHandler>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}

#include <homomorphism/introduce_handler_compute.h>
#include "homomorphism/configuration_factory.h"

#include "homomorphism/calculation_remapper.h"
#include "homomorphism/forget_handler_combined.h"
#include "homomorphism/iterator_remapper.h"


HomomorphismSettings ConfigurationFactory::defaultSettings(size_t n, size_t maxWidth) {
    return {std::make_shared<CalculationRemapper>(), std::make_shared<ForgetHandlerLast>(n, maxWidth),
            std::make_shared<IntroduceHandlerCompute>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}

HomomorphismSettings ConfigurationFactory::iteratorRemapper(size_t n, size_t maxWidth) {
    return {std::make_shared<IteratorRemapper>(), std::make_shared<ForgetHandlerLast>(n, maxWidth),
            std::make_shared<IntroduceHandlerCompute>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}

PathdecompotisionSettings ConfigurationFactory::DefaultPathSettings(size_t n, size_t maxWidth) {
    return {std::make_shared<ForgetHandlerCombined>(n, maxWidth),
            std::make_shared<IntroduceHandlerCompute>(),
            std::make_shared<VectorAllocator>()};
}

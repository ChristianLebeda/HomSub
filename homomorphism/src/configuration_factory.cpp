#include <homomorphism/introduce_handler_compute.h>
#include "homomorphism/configuration_factory.h"

#include "homomorphism/calculation_remapper.h"
#include "homomorphism/forget_handler_last.h"
#include "homomorphism/iterator_remapper.h"


HomomorphismSettings ConfigurationFactory::defaultSettings(size_t n, size_t k) {
    return {std::make_shared<CalculationRemapper>(), std::make_shared<ForgetHandlerLast>(n, k),
            std::make_shared<IntroduceHandlerCompute>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}

HomomorphismSettings ConfigurationFactory::iteratorRemapper(size_t n, size_t k) {
    return {std::make_shared<IteratorRemapper>(), std::make_shared<ForgetHandlerLast>(n, k),
            std::make_shared<IntroduceHandlerCompute>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocator>()};
}

PathdecompotisionSettings ConfigurationFactory::DefaultPathSettings(size_t n, size_t k) {
    return {std::make_shared<ForgetHandlerAny>(n, k),
            std::make_shared<IntroduceHandlerCompute>(),
            std::make_shared<VectorAllocator>()};
}

#include "homomorphism/introduce_handler_compute.h"
#include "homomorphism/introduce_handler_least_precomputed.h"
#include "homomorphism/vector_allocator_default.h"
#include "homomorphism/vector_allocator_pooling.h"
#include "homomorphism/configuration_factory.h"

#include "homomorphism/calculation_remapper.h"
#include "homomorphism/forget_handler_combined.h"
#include "homomorphism/iterator_remapper.h"
#include "homomorphism/introduce_handler_precomputed.h"


HomomorphismSettings ConfigurationFactory::defaultSettings(size_t n, size_t maxWidth) {
    return {std::make_shared<CalculationRemapper>(), std::make_shared<ForgetHandlerLast>(n, maxWidth),
            std::make_shared<IntroduceHandlerCompute>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocatorPooling>(BagSizes(n, maxWidth))};
}

HomomorphismSettings ConfigurationFactory::PrecomputedSettings(size_t n, size_t maxWidth,
                            std::shared_ptr<EdgeConsistencyPrecomputation> precomputation) {
    return {std::make_shared<CalculationRemapper>(), std::make_shared<ForgetHandlerLast>(n, maxWidth),
            std::make_shared<IntroduceHandlerLeastPrecomputed>(precomputation), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocatorPooling>(BagSizes(n, maxWidth))};
}

HomomorphismSettings ConfigurationFactory::iteratorRemapper(size_t n, size_t maxWidth) {
    return {std::make_shared<IteratorRemapper>(), std::make_shared<ForgetHandlerLast>(n, maxWidth),
            std::make_shared<IntroduceHandlerCompute>(), std::make_shared<JoinHandler>(),
            std::make_shared<VectorAllocatorPooling>(BagSizes(n, maxWidth))};
}

PathdecompotisionSettings ConfigurationFactory::DefaultPathSettings(size_t n, size_t maxWidth) {
    return {std::make_shared<ForgetHandlerCombined>(n, maxWidth),
            std::make_shared<IntroduceHandlerCompute>(),
            std::make_shared<VectorAllocatorPooling>(BagSizes(n, maxWidth))};
}

PathdecompotisionSettings ConfigurationFactory::PrecomputedPathSettings(size_t n, size_t maxWidth,
                        std::shared_ptr<EdgeConsistencyPrecomputation> precomputation) {
    return {std::make_shared<ForgetHandlerCombined>(n, maxWidth),
            std::make_shared<IntroduceHandlerLeastPrecomputed>(precomputation),
            std::make_shared<VectorAllocatorPooling>(BagSizes(n, maxWidth))};
}

PathdecompotisionSettings ConfigurationFactory::PrecomputedPathSettingsNonpooled(size_t n, size_t maxWidth,
        std::shared_ptr<EdgeConsistencyPrecomputation> precomputation) {
    return {std::make_shared<ForgetHandlerCombined>(n, maxWidth),
            std::make_shared<IntroduceHandlerLeastPrecomputed>(precomputation),
            std::make_shared<VectorAllocatorDefault>(BagSizes(n, maxWidth))};
}

DynamicProgrammingSettings ConfigurationFactory::DefaultDynamicSettings(size_t n, size_t maxWidth,
        std::shared_ptr<EdgeConsistencyPrecomputation> precomputationLeast,
        std::shared_ptr<EdgeConsistencyPrecomputation> precomputationSecond) {
    return {std::make_shared<ForgetHandlerCombined>(n, maxWidth),
            std::make_shared<IntroduceHandlerPrecomputed>(n, maxWidth, precomputationLeast, precomputationSecond),
            std::make_shared<JoinHandler>(), std::make_shared<VectorAllocatorPooling>(BagSizes(n, maxWidth))};
}

DynamicProgrammingSettings ConfigurationFactory::DynamicSettingsNonpooled(size_t n, size_t maxWidth,
        std::shared_ptr<EdgeConsistencyPrecomputation> precomputationLeast,
        std::shared_ptr<EdgeConsistencyPrecomputation> precomputationSecond) {
    return {std::make_shared<ForgetHandlerCombined>(n, maxWidth),
            std::make_shared<IntroduceHandlerPrecomputed>(n, maxWidth, precomputationLeast, precomputationSecond),
            std::make_shared<JoinHandler>(), std::make_shared<VectorAllocatorDefault>(BagSizes(n, maxWidth))};
}

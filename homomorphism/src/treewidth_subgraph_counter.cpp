#include "homomorphism/treewidth_subgraph_counter.h"

#include <atomic>
#include <tuple>

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/configuration_factory.h"
#include "homomorphism/homomorphism_counter_interface.h"
#include <thread>

std::shared_ptr<TreewidthSubgraphCounter> TreewidthSubgraphCounter::instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g) {
	return std::make_shared<TreewidthSubgraphCounter>(spasm, g);
}

long TreewidthSubgraphCounter::compute() {
    long count = 0;

    auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g_, spdc_->width());
    auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g_, spdc_->width());
    DynamicProgrammingSettings settings = ConfigurationFactory::DefaultDynamicSettings(g_->vertCount(), spdc_->width(), pre1, pre2);
    PathdecompotisionSettings set = ConfigurationFactory::PrecomputedPathSettings(g_->vertCount(), spdc_->width(), pre1);

    for (size_t i = 0; i < spdc_->size(); i++)
    {
        auto next = (*spdc_)[i];
        if(next.decomposition->IsPathDecomposition()) {
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = PathdecompositionCounter(next.graph, g_, npd, set);
            count += hc.compute() * next.coefficient;
        } else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = DynamicProgrammingCounter(next.graph, g_, ntd, settings);
            count += hc.compute() * next.coefficient;
        }
    }

    return count;
}

long TreewidthSubgraphCounter::computeParallel() {
    
    int threadCount = 4;
    
    auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g_, spdc_->width());
    auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g_, spdc_->width());
    
    std::vector<std::vector<long>> coeffs(threadCount);
    std::vector<std::vector<std::shared_ptr<HomomorphismCounterInterface>>> hcs(threadCount);
    
    std::vector<PathdecompotisionSettings> pdSettings;
    std::vector<DynamicProgrammingSettings> dpSettings;
    
    //Create settings objects
    for(int i = 0; i < threadCount; i++) {
        pdSettings.push_back(ConfigurationFactory::PrecomputedPathSettings(g_->vertCount(), spdc_->width(), pre1));
        dpSettings.push_back(ConfigurationFactory::DefaultDynamicSettings(g_->vertCount(), spdc_->width(), pre1, pre2));
    }

    //Setup all calls
    for (size_t i = 0; i < spdc_->size(); i++)
    {
        auto next = (*spdc_)[i];
        if(next.decomposition->IsPathDecomposition()) {
            
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = std::make_shared<PathdecompositionCounter>(next.graph, g_, npd, pdSettings[i%threadCount]);
            
            coeffs[i%threadCount].push_back(next.coefficient);
            hcs[i%threadCount].push_back(hc);
        } else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = std::make_shared<DynamicProgrammingCounter>(next.graph, g_, ntd, dpSettings[i%threadCount]);
            coeffs[i%threadCount].push_back(next.coefficient);
            hcs[i%threadCount].push_back(hc);

        }
        
    }
    
    
    std::atomic<int> counter(0);
    
    auto t = [](std::vector<long> coeffs, std::vector<std::shared_ptr<HomomorphismCounterInterface>> counters, std::atomic<int> &counter) {
        long threadCount = 0;
        for(int i = 0; i < coeffs.size(); i++) {
            threadCount += counters[i]->compute() * coeffs[i];
        }
        
        counter += threadCount;
        return;
    };
    
    std::thread threads[threadCount];
    
    //Start each thread
    for(int i = 0; i < threadCount; i++) {
        threads[i] = std::thread(t, coeffs[i], hcs[i], std::ref(counter));
    }
    
    for(int i = 0; i < threadCount; i++) {
        threads[i].join();
    }
    
    return counter;
}

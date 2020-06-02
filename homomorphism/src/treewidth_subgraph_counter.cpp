#include "homomorphism/treewidth_subgraph_counter.h"

#include <atomic>
#include <tuple>

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/configuration_factory.h"
#include "homomorphism/homomorphism_counter_interface.h"
//#include <thread>

std::shared_ptr<TreewidthSubgraphCounter> TreewidthSubgraphCounter::instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g, bool usePool) {
	return std::make_shared<TreewidthSubgraphCounter>(spasm, g, usePool);
}

long TreewidthSubgraphCounter::compute() {
    long count = 0;

    auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g_, spdc_->width());
    auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g_, spdc_->width());
    auto settings = pool_ ?
            ConfigurationFactory::DefaultPrecomputedSettings(g_->vertCount(), spdc_->width(), pre1, pre2) :
            ConfigurationFactory::NonpoolingPrecomputedSettings(g_->vertCount(), spdc_->width(), pre1, pre2);

    for (size_t i = 0; i < spdc_->size(); i++)
    {
        auto next = (*spdc_)[i];
        if(next.decomposition->IsPathDecomposition()) {
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = PathdecompositionCounter(next.graph, g_, npd, settings.second);
            count += hc.compute() * next.coefficient;
        } else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = DynamicProgrammingCounter(next.graph, g_, ntd, settings.first);
            count += hc.compute() * next.coefficient;
        }
    }

    return count;
}

long TreewidthSubgraphCounter::computeParallel(int threadCount) {
    // This implementation is currently removed, as it created issues on some platforms
    return compute();

    /*
    auto pre1 = EdgeConsistencyPrecomputation::InitializeLeast(g_, spdc_->width());
    auto pre2 = EdgeConsistencyPrecomputation::InitializeSecond(g_, spdc_->width());
    
    
    std::vector<PathdecompotisionSettings> pdSettings;
    std::vector<DynamicProgrammingSettings> dpSettings;
    
    //Create settings objects
    for(int i = 0; i < threadCount; i++) {
        //TODO: There is a bug in the sorting below resulting in pools being shared among threads
        auto settings = //pool_ ?
                        //ConfigurationFactory::DefaultPrecomputedSettings(g_->vertCount(), spdc_->width(), pre1, pre2) :
                        ConfigurationFactory::NonpoolingPrecomputedSettings(g_->vertCount(), spdc_->width(), pre1, pre2);
        pdSettings.push_back(settings.second);
        dpSettings.push_back(settings.first);
    }
    
    std::vector<std::tuple<int, long, std::shared_ptr<HomomorphismCounterInterface>>> computations;

    //Setup all computatoins
    for (size_t i = 0; i < spdc_->size(); i++)
    {
        auto next = (*spdc_)[i];
        if(next.decomposition->IsPathDecomposition()) {
            
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = std::make_shared<PathdecompositionCounter>(next.graph, g_, npd, pdSettings[i%threadCount]);
            
            std::tuple<int, long, std::shared_ptr<HomomorphismCounterInterface>> computation;
            
            std::get<0>(computation) = npd->getWidth();
            std::get<1>(computation) = next.coefficient;
            std::get<2>(computation) = hc;
            computations.push_back(computation);
            
        } else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = std::make_shared<DynamicProgrammingCounter>(next.graph, g_, ntd, dpSettings[i%threadCount]);

            std::tuple<int, long, std::shared_ptr<HomomorphismCounterInterface>> computation;
            
            std::get<0>(computation) = ntd->getWidth();
            std::get<1>(computation) = next.coefficient;
            std::get<2>(computation) = hc;
            computations.push_back(computation);
        }
        
    }
    
    //Sort based in width
    sort(computations.begin(), computations.end(),
    [](const std::tuple<int, long, std::shared_ptr<HomomorphismCounterInterface>> & a, const std::tuple<int, long, std::shared_ptr<HomomorphismCounterInterface>> & b) -> bool
        {
            return std::get<0>(a) > std::get<0>(b);
        }
    );
    
    std::vector<std::vector<long>> coeffs(threadCount);
    std::vector<std::vector<std::shared_ptr<HomomorphismCounterInterface>>> hcs(threadCount);
    
    for(int i = 0; i < computations.size(); i++) {
        coeffs[i%threadCount].push_back(std::get<1>(computations[i]));
        hcs[i%threadCount].push_back(std::get<2>(computations[i]));
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
    
    return counter; */
}

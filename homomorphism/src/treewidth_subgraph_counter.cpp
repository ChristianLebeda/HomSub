#include "homomorphism/treewidth_subgraph_counter.h"

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
    
    std::cout << count << std::endl;
	return count;
}

long TreewidthSubgraphCounter::computeParallel() {
    
    int threadCount = 3;
    
    HomomorphismSettings settings = ConfigurationFactory::defaultSettings(g_->vertCount(), spdc_->width());
    PathdecompotisionSettings set = ConfigurationFactory::DefaultPathSettings(g_->vertCount(), spdc_->width());

    
    std::vector<std::vector<long>> coeffs(threadCount);
    std::vector<std::vector<PathdecompositionCounter>> hcs(threadCount);

    //Setup all calls
    for (size_t i = 0; i < spdc_->size(); i++)
    {
        auto next = (*spdc_)[i];
        if(next.decomposition->IsPathDecomposition()) {
            
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = PathdecompositionCounter(next.graph, g_, npd, set);
            
            coeffs[i%threadCount].push_back(next.coefficient);
            hcs[i%threadCount].push_back(hc);
        } else {
            //auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            //auto hc = std::make_shared<HomomorphismCounter>(next.graph, g_, ntd, settings);
            
            //coeffs[i%threadCount].push_back(next.coefficient);
            //hcs[i%threadCount].push_back(hc);

        }
    }
    
    
    std::atomic<int> counter(0);
    
    auto t = [](std::vector<long> coeffs, std::vector<PathdecompositionCounter> counters, std::atomic<int> &counter) {
        long localCount = 0;
        for(int i = 0; i < coeffs.size(); i++) {
            localCount += counters[i].compute() * coeffs[i];
        }
        
        counter += localCount;
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
     
    
    /*
    long sequentialCounter = 0;
    for(int i = 0; i < threadCount; i++) {
        for(int j = 0; j < coeffs[i].size(); j++) {
            sequentialCounter+= hcs[i][j]->compute() * coeffs[i][j];
        }
    }
    */

    std::cout << counter << std::endl;
    
    return 5;
}

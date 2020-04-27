#include "homomorphism/treewidth_subgraph_counter.h"

#include <tuple>

#include "homomorphism/homomorphism_counter.h"
#include "homomorphism/calculation_remapper.h"
#include "homomorphism/configuration_factory.h"
#include <thread>

std::shared_ptr<TreewidthSubgraphCounter> TreewidthSubgraphCounter::instatiate(std::shared_ptr<SpasmDecomposition> spasm, std::shared_ptr<Graph> g) {
	return std::make_shared<TreewidthSubgraphCounter>(spasm, g);
}

long TreewidthSubgraphCounter::compute() {
	long count = 0;

    HomomorphismSettings settings = ConfigurationFactory::defaultSettings(g_->vertCount(), spdc_->width());
    PathdecompotisionSettings set = ConfigurationFactory::DefaultPathSettings(g_->vertCount(), spdc_->width());

	for (size_t i = 0; i < spdc_->size(); i++)
	{
		auto next = (*spdc_)[i];
		if(next.decomposition->IsPathDecomposition()) {
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = PathdecompositionCounter(next.graph, g_, npd, set);
            count += hc.compute() * next.coefficient;
		} else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = HomomorphismCounter(next.graph, g_, ntd, settings);
            count += hc.compute() * next.coefficient;
		}
	}

	return count;
}

long TreewidthSubgraphCounter::computeParallel() {
    int threadCount = 2;
    
    //std::vector<long> counts(threadCount, 0);

    HomomorphismSettings settings = ConfigurationFactory::defaultSettings(g_->vertCount(), spdc_->width());
    PathdecompotisionSettings set = ConfigurationFactory::DefaultPathSettings(g_->vertCount(), spdc_->width());

    //Array containing each call to hc.compute grouped by thread
    std::vector<std::vector<std::function<long()>>> jobs(threadCount);
    
    //Setup all calls
    for (size_t i = 0; i < spdc_->size(); i++)
    {
        auto next = (*spdc_)[i];
        if(next.decomposition->IsPathDecomposition()) {
            auto npd = NicePathDecomposition::FromTd(next.decomposition);
            auto hc = PathdecompositionCounter(next.graph, g_, npd, set);
            
            long coefficient = next.coefficient;
            jobs[i%threadCount].push_back([&] {
                return hc.compute() * coefficient;;
            });
        } else {
            auto ntd = NiceTreeDecomposition::FromTd(next.decomposition);
            auto hc = HomomorphismCounter(next.graph, g_, ntd, settings);
            
            long coefficient = next.coefficient;
            jobs[i%threadCount].push_back([&] {
                return hc.compute() * coefficient;;
            });
        }
    }
    
    std::vector<std::thread> threads(threadCount);
    
    std::atomic<long> atomicCount(0);
    
    //Start each thread
    for(int i = 0; i < threadCount; i++) {
        auto t = [jobs, i](std::atomic<long>& count) { //What does the capture mean for speed? Maybe things lock up
            long localCount = 0;
            for(int j = 0; j < jobs[i].size(); j++) {
                localCount += jobs[i][j]();
            }
            count += localCount;
        };
        threads.push_back(std::thread(t, std::ref(atomicCount)));
    }
    
    //Wait for each thread
    for(int i = 0; i < threadCount; i++) {
        threads[i].join();
    }

    return atomicCount;
}


#include <stdio.h>
#include "homomorphism/traversal_homomorphism_counter.h"
#include <unordered_set>
#include <iostream>

bool TraversalHomomorphismCounter::CheckHomomorphism(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> hTraversal, std::vector<size_t> gTraversal) {
    int k = hTraversal.size();
    
    //Create mapping
    std::vector<size_t> mapping(k, 0);
    for(int i = 0; i < k; i++) {
        mapping[hTraversal[i]] = gTraversal[i];
    }
    
    //For all verts in h
    for(int i = 0; i < k; i++) {
        //Check that edges in mapping er preserved
        for(size_t nei : h->getNeighbourhood(i)) {
            if(!g->edgeExist(mapping[i], mapping[nei])) {
                return false;
            }
        }
    }
    
    return true;
}

int TraversalHomomorphismCounter::Count(std::shared_ptr<EdgeSetGraph> h, std::shared_ptr<EdgeSetGraph> g) {
    std::vector<size_t> hTraversal = GetFirstTraversal(h);
    
    size_t count = 0;
    auto traversals = GetKTraversals(g, h->vertCount());
    std::cout << "Amount of traversals: " << traversals.size() << std::endl;
    for(auto gTraversal : GetKTraversals(g, h->vertCount())) {
        if(CheckHomomorphism(h, g, hTraversal, gTraversal)) count++;
    }
    
    
    return count;
}

std::vector<std::vector<size_t>> TraversalHomomorphismCounter::GetKTraversals(std::shared_ptr<EdgeSetGraph> g, int k)
{
    std::vector<size_t> empty;
    return GetKTraversalsUtil(g, empty, k);
}

std::vector<std::vector<size_t>> TraversalHomomorphismCounter::GetKTraversalsUtil(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> visited, int k) {
    
    //These choives contain the open neighbourhood (no repeated verts might be wrong)
    std::unordered_set<size_t> choices;
    choices.clear();
    
    //Fill all options as first choice
    if(visited.size() == 0) {
        for(int i = 0; i < g->vertCount(); i++) {
            choices.insert(i);
        }
    } else {
        choices = GetOpenNeighbourhood(g, visited);
    }
    
    //try each available choice
    std::vector<std::vector<size_t>> result;
    for(size_t choice : choices) {
        std::vector<size_t> withChoice = visited;
        withChoice.push_back(choice);
        if(withChoice.size() == k) { //Return if traversal has size k
            result.push_back(withChoice);
        } else {
            std::vector<std::vector<size_t>> recursiveResult = GetKTraversalsUtil(g, withChoice, k); //Recurse if still not finished
            for(auto traversal : recursiveResult) {
                result.push_back(traversal);
            }
        }
    }
    return result;
}

std::vector<size_t> TraversalHomomorphismCounter::GetFirstTraversal(std::shared_ptr<EdgeSetGraph> g)
{
    std::vector<size_t> traversal {0};
    for(int i = 1; i < g->vertCount(); i++) {
        std::unordered_set<size_t> on = GetOpenNeighbourhood(g, traversal);
        traversal.push_back(*on.begin());
    }
    return traversal;
}

std::unordered_set<size_t> TraversalHomomorphismCounter::GetOpenNeighbourhood(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> verts)
{
    std::unordered_set<size_t> on;
    on.clear();
    
    for(size_t v : verts) {
        for(size_t vn : g->getNeighbourhood(v)) {
            on.insert(vn);
        }
    }
    
    return on;
}

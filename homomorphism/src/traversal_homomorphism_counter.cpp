
#include <stdio.h>
#include "homomorphism/traversal_homomorphism_counter.h"
#include <unordered_set>
#include <iostream>

bool TraversalHomomorphismCounter::CheckHomomorphism(EdgeSetGraph h, EdgeSetGraph g, std::vector<size_t> mapping) {
    return true;
}

int TraversalHomomorphismCounter::Count(EdgeSetGraph h, EdgeSetGraph g) {
    
    return 0;
}

std::vector<std::vector<size_t>> TraversalHomomorphismCounter::GetKTraversals(std::shared_ptr<EdgeSetGraph> g, int k)
{
    std::vector<size_t> empty;
    return GetKTraversalsUtil(g, empty, k);
}

std::vector<std::vector<size_t>> TraversalHomomorphismCounter::GetKTraversalsUtil(std::shared_ptr<EdgeSetGraph> g, std::vector<size_t> visited, int k) {
    
    //Find open neighbourhood
    std::unordered_set<size_t> choices;
    choices.clear();
    
    //Fill all options as first choice
    if(visited.size() == 0) {
        for(int i = 0; i < g->vertCount(); i++) {
            choices.insert(i);
        }
    }
    
    //If along path, add open neighbourhood
    for(size_t v : visited) {
        for(size_t n : g->getNeighbourhood(v)) {
            if(std::find(visited.begin(), visited.end(), n) == visited.end()) {
                choices.insert(n);
            }
        }
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

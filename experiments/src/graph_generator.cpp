#include "experiments/graph_generator.h"

#include <vector>

 void GraphGenerator::CompleteGrid(std::shared_ptr<Graph> g, int rows, int columns)
{
    g->clear(rows*columns);
    
    for(int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if(c < columns - 1) { //add row edge
                g->addEdge(rows * c + r, rows * (c+1) + r );
            }
            if(r < rows - 1) { // add column edge
                g->addEdge(rows * c + r, rows * c + (r+1) );
            }
        }
    }
}

void GraphGenerator::CompleteBinaryTree(std::shared_ptr<Graph> g, int depth) {
    size_t verts = ~(-1 << depth);
    g->clear(verts);
    for(int i = 1; i < verts; i++) {
        g->addEdge(i, ((i+1) >> 1) - 1);
    }
}

//Can run forever
void GraphGenerator::RandomConnectedGraph(std::shared_ptr<Graph> g, size_t verts, size_t edges)
{
    g->clear(verts);
    for(int i = 1; i < verts; i++) {
        size_t connector = RandomSize(i);
        g->addEdge(i, connector);
    }
    
    while(g->edgeCount() < edges) {
        //Add random edge
        size_t u = RandomSize(verts);
        size_t v = RandomSize(verts);
        if(u == v) continue;
        if(!g->edgeExist(u, v)) {
            g->addEdge(u, v);
        }
    }
}

void GraphGenerator::RandomGraph(std::shared_ptr<Graph> g, size_t verts, size_t edges)
{
    g->clear(verts);

    while(g->edgeCount() < edges) {
        //Add random edge
        size_t u = RandomSize(verts);
        size_t v = RandomSize(verts);
        if(u == v || g->edgeExist(u, v)) continue;
        g->addEdge(u, v);
    }
}

size_t GraphGenerator::RandomSize(size_t max)
{
    return rand() % max;
}

float GraphGenerator::RandomFloat()
{
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void GraphGenerator::Path(std::shared_ptr<Graph> g, int length) {
    g->clear(length);
    for(int i = 0 ;i < length - 1; i++) {
        g->addEdge(i, i+1);
    }
}

void GraphGenerator::Cycle(std::shared_ptr<Graph> g, int length) {
    Path(g, length);
    g->addEdge(length-1, 0);
}

void GraphGenerator::EdgeProbabilityGraph(std::shared_ptr<Graph> g, size_t verts, float probability)
{
    g->clear(verts);
    for(int i = 0; i < verts; i++) {
        for(int j = 0; j < verts; j++) {
            if(i < j && RandomFloat() < probability) {
                g->addEdge(i, j);
            }
        }
    }
}

void GraphGenerator::VertexPairs(std::shared_ptr<Graph> g, int pairCount) {
    g->clear(pairCount*2);
    for(int i = 0; i < pairCount; i++) {
        g->addEdge(i*2, i*2+1);
    }
}

void GraphGenerator::Clique(std::shared_ptr<Graph> g, int size)
{
    g->clear(size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(i < j) {
                g->addEdge(i, j);
            }
        }
    }
}

void GraphGenerator::Star(std::shared_ptr<Graph> g, int size) {
    g->clear(size);
    for(int i = 1; i < size;i++) {
        g->addEdge(0, i);
    }
}

void GraphGenerator::MaxDegreeRandomGraph(std::shared_ptr<Graph> g, size_t n, size_t maxDegree) {
    g->clear(n);
    
    for(int i = 0; i < n; i++) {
        size_t targetDegree = RandomSize(maxDegree);
        size_t currentDegree = g->getNeighbourhood(i).size();
        
        while(currentDegree < targetDegree) {
            size_t randomVert = RandomSize(n);
            
            if(!g->edgeExist(i, randomVert) &&
               i != randomVert &&
               g->getNeighbourhood(randomVert).size() < maxDegree)
            {
                g->addEdge(i, randomVert);
                currentDegree++;
            }
        }
    }
}

void GraphGenerator::FromGraph(std::shared_ptr<Graph> destination, std::shared_ptr<Graph> source) {
    destination->clear(source->vertCount());
    
    for(size_t u = 0; u < source->vertCount(); u++) {
        auto neighbours = source->getNeighbourhood(u);
        for(size_t v : neighbours) {
            destination->addEdge(u, v);
        }
    }
}

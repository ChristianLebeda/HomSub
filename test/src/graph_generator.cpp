#include "test/graph_generator.h"

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

void GraphGenerator::RandomConnectedGrid(std::shared_ptr<Graph> g, int rows, int columns)
{
    for(int c = 0; c < columns; c++) {
        for(int r = 0; r < rows; r++) {
            size_t neighbours = g->getNeighbourhood(rows * c + r).size();
            if(!neighbours) {
                size_t toAdd = RandomSize(4);
            }
            
            
        }
    }
}

void GraphGenerator::CompleteBinaryTree(std::shared_ptr<Graph> g, int depth) {
    size_t verts = ~(-1 << depth);
    g->clear(verts);
    for(int i = 2; i < verts+1; i++) {
        g->addEdge(i-1, (i >> 1)-1);
        std::cout << "connected " << i-1 << " to " << (i >> 1)-1 << std::endl;
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

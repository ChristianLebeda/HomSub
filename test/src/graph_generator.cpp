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

#include "homomorphism/nauty.h"

#include <iostream>

#include <homomorphism/helper_functions.h>
#include "homomorphism/pipe_handler.h"

void Nauty::Test(std::vector<SpasmEntry> spasm) {
    PipeHandler pipe = PipeHandler::openNauty();

    std::ostringstream str;

    // Canonical mode
    str << "c\n";

    for(auto& entry : spasm) {
        // Define graph
        str << "n=" << entry.graph->vertCount() << "\n";
        str << "g\n" << entry.graph->toNautyFormat() << "\n";

        // Execute nauty and display graph
        str << "x\n b\n";
    }

    str << "q";;

    pipe.writeLine(str.str());

    // Has to close input pipe
    // pipe.closePipes();

    for (auto & i : spasm) {
       std::cout << HelperFunctions::trimDreadnautOutput(pipe, i.graph->vertCount()) << std::endl;
    }
}

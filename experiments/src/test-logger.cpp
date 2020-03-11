//
//  test-logger.cpp
//  test
//
//  Created by Jonas Mortensen on 03/03/2020.
//

#include <iostream>
#include "experiments/test-logger.h"

std::string TestLogger::subStepToString(SubStep step) {
    switch (step) {
        case SubStep::CREATE_SPASM:
            return "CREATE_SPASM";
            break;
        case SubStep::DECOMPOSE_SPASM:
            return "DECMOPOSE_SPASM";
        default:
            return "UKNOWN";
            break;
    }
}

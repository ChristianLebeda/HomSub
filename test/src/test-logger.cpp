//
//  test-logger.cpp
//  test
//
//  Created by Jonas Mortensen on 03/03/2020.
//

#include <iostream>
#include "test/test-logger.h"

void TestLogger::NotifyTestStart(std::string name) {
    currentTestName_ = name;
}

void TestLogger::NotifyTestEnd(float duration)
{
}

void TestLogger::NotifyTestSubstep(SubStep step, std::string note, float duration) {
    stream_ << currentTestName_ << "," << subStepToString(step) << "," << note << "," << duration << std::endl;
}

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

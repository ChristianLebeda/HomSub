//
//  test-logger.cpp
//  test
//
//  Created by Jonas Mortensen on 03/03/2020.
//

#include <iostream>
#include "experiments/test-logger.h"

void TestLogger::NotifyTestStart(std::string name) {
    currentTestName_ = name;
    stream_ << currentTestName_ << ":" << std::endl;
}

void TestLogger::NotifyTestEnd(float duration)
{
    stream_ << std::endl;
}

void TestLogger::NotifyTestSubstep(SubStep step, std::string note, float duration) {
    if(note.length() > 0) {
        stream_ << subStepToString(step) << " - " << note << ": " << duration << std::endl;
    } else {
        stream_ << subStepToString(step) << ": " << duration << std::endl;
    }
}

void TestLogger::NotifyTestAssert(std::string note,bool passed) {
    if(passed) {
        stream_ << note << ": PASSED" << std::endl;
    } else {
        stream_ << note << ": FAILED" << std::endl;
    }
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

//
//  csv_logger.cpp
//  experiments
//
//  Created by Jonas Mortensen on 11/03/2020.
//

#include <stdio.h>
#include <iostream>
#include "experiments/csv_logger.h"

void CSVLogger::NotifyTestStart(std::string name)
{
    currentTestName_ = name;
}

void CSVLogger::NotifyTestEnd(float duration)
{
    
}

void CSVLogger::NotifyTestSubstep(SubStep step, std::string note, float duration)
{
    logCSV(TestLogger::subStepToString(step), note, std::to_string(duration));
}

void CSVLogger::NotifyTestIterative(int n, std::string note, float duration)
{
    logCSV("n = " + std::to_string(n), note, std::to_string(duration));
}

void CSVLogger::NotifyTestAssert(std::string note, bool passed)
{
    if(passed) {
        logCSV("", note, "PASSED");
    } else {
        logCSV("", note, "FAILED");
    }
}

void CSVLogger::NotifyFailed()
{
}

void CSVLogger::NotifyRunStart()
{
    stream_ << "testName,info,coment,result" << std::endl;
}

void CSVLogger::logCSV(std::string info, std::string comment, std::string result) {
    stream_ << currentTestName_ << "," << info << "," << comment << "," << result << std::endl;
}

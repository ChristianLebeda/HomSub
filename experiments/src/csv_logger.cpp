#include "experiments/csv_logger.h"

#include <iostream>

void CSVLogger::NotifyTestStart(std::string name)
{
    currentTestName_ = name;
}

void CSVLogger::NotifyTestEnd(float duration)
{
    
}

void CSVLogger::NotifyTestSubstep(SubStep step, std::string note, float duration)
{
    //logCSV(TestLogger::subStepToString(step), note, std::to_string(duration));
}

void CSVLogger::NotifyTestIterative(int n, std::string note, float duration)
{
    //logCSV("n = " + std::to_string(n), note, std::to_string(duration));
}

void CSVLogger::NotifyTestAssert(std::string note, bool passed)
{
    if(passed) {
        //logCSV("", note, "PASSED");
    } else {
        //logCSV("", note, "FAILED");
    }
}

void CSVLogger::NotifyFailed()
{
}

void CSVLogger::NotifyRunStart()
{
    stream_ << "testName,comment,n,k,i,result" << std::endl;
}

void CSVLogger::Log(std::string comment, int n, float duration)
{
    stream_ << currentTestName_ << "," << comment << "," << n << ",,," << duration << std::endl;
}

void CSVLogger::Log(std::string comment, int n, int k, float duration)
{
    stream_ << currentTestName_ << "," << comment << "," << n << "," << k << ",," << duration << std::endl;
}

void CSVLogger::Log(std::string comment, int n, int k, int i, float duration)
{
    stream_ << currentTestName_ << "," << comment << "," << n << "," << k << "," << i << "," << duration << std::endl;
}

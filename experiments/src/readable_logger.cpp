#include <stdio.h>
#include "experiments/readable_logger.h"
#include <iostream>

void ReadableLogger::NotifyTestStart(std::string name)
{
    currentTestName_ = name;
    stream_ << currentTestName_ << ":" << std::endl;
}

void ReadableLogger::NotifyTestEnd(float duration)
{
    stream_ << std::endl;
}

void ReadableLogger::NotifyTestSubstep(SubStep step, std::string note, float duration)
{
    if(note.length() > 0) {
        stream_ << TestLogger::subStepToString(step) << " - " << note << ": " << duration << std::endl;
    } else {
        stream_ << TestLogger::subStepToString(step) << ": " << duration << std::endl;
    }
}

void ReadableLogger::NotifyTestIterative(int n, std::string note, float duration)
{
    if(note.length() > 0) {
        stream_ << n << " - " << note << ": " << duration << std::endl;
    } else {
        stream_ << "n = " << n << ": " << duration << std::endl;
    }
}

void ReadableLogger::NotifyTestAssert(std::string note,bool passed)
{
    if(passed) {
        stream_ << note << ": PASSED" << std::endl;
    } else {
        failed_++;
        stream_ << note << ": FAILED" << std::endl;
    }
}

void ReadableLogger::NotifyFailed()
{
    if(failed_) {
        //error_ << "Failed " << failed_ << " tests" << std::endl;
        stream_ << "Failed " << failed_ << " tests" << std::endl;
        failed_ = 0;
    }
}


void ReadableLogger::NotifyRunStart()
{
    
}

void ReadableLogger::Log(std::string comment, int n, float duration)
{
    
}

void ReadableLogger::Log(std::string comment, int n, int k, float duration)
{
    
}

void ReadableLogger::Log(std::string comment, int n, int k, int i, float duration)
{
    
}

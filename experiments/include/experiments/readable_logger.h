#ifndef EXPERIMENTS_READABLE_LOGGER_H
#define EXPERIMENTS_READABLE_LOGGER_H

#include <string>
#include "experiments/test_logger.h"

class ReadableLogger : public TestLogger {
public:
    ReadableLogger(std::ostream& stream) : stream_(stream), failed_(0), currentTestName_("") {};
    void NotifyTestStart(std::string name);
    void NotifyTestEnd(float duration);
    void NotifyTestSubstep(SubStep step, std::string note, float duration);
    void NotifyTestIterative(int n, std::string note, float duration);
    void NotifyTestAssert(std::string note,bool passed);
    void NotifyFailed();
    void NotifyRunStart();
    void Log(std::string comment, int n, float duration);
    void Log(std::string comment, int n, int k, float duration);
    void Log(std::string comment, int n, int k, int i, float duration);
private:
    size_t failed_;
    std::ostream &stream_;
    std::string currentTestName_;
};

#endif /* readable_logger_h */

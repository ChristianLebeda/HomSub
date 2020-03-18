#ifndef CSV_LOGGER_H
#define CSV_LOGGER_H

#include "experiments/test-logger.h"


class CSVLogger : public TestLogger {
public:
    CSVLogger(std::ostream& stream) : stream_(stream), currentTestName_("") {};
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
    std::ostream &stream_;
    std::string currentTestName_;
};

#endif /* csv_logger_h */

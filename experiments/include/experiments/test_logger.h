#ifndef EXPERIMENTS_TEST_LOGGER_H
#define EXPERIMENTS_TEST_LOGGER_H

#include <string>

enum SubStep {CREATE_SPASM, DECOMPOSE_SPASM, RUN_ALG};
enum TestingKeyword {TAMAKI};

class TestLogger {
public:
    virtual void NotifyTestStart(std::string name) = 0;
    virtual void NotifyTestEnd(float duration) = 0;
    virtual void NotifyTestSubstep(SubStep step, std::string note, float duration) = 0;
    virtual void NotifyTestIterative(int n, std::string note, float duration) = 0;
    virtual void NotifyTestAssert(std::string note,bool passed) = 0;
    virtual void NotifyFailed() = 0;
    virtual void NotifyRunStart() = 0;
    virtual void Log(std::string comment, int n, float duration) = 0;
    virtual void Log(std::string comment, int n, int k, float duration) = 0;
    virtual void Log(std::string comment, int n, int k, int i, float duration) = 0;
    static std::string subStepToString(SubStep step);
};

#endif /* test_logger_h */

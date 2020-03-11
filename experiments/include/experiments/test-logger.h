#ifndef TEST_TEST_LOGGER_h
#define TEST_TEST_LOGGER_h

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
    static std::string subStepToString(SubStep step);
};

#endif /* test_logger_h */

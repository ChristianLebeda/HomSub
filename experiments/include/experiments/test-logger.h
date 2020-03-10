#ifndef TEST_TEST_LOGGER_h
#define TEST_TEST_LOGGER_h

#include <string>

enum SubStep {CREATE_SPASM, DECOMPOSE_SPASM, RUN_ALG};
enum TestingKeyword {TAMAKI};

class TestLogger {
public:
    explicit TestLogger(std::ostream& stream, std::ostream& error) : stream_(stream), error_(error), failed_(0) {};
    void NotifyTestStart(std::string name);
    void NotifyTestEnd(float duration);
    void NotifyTestSubstep(SubStep step, std::string note, float duration);
    void NotifyTestAssert(std::string note,bool passed);
    void NotifyFailed();
private:
    size_t failed_;
    std::ostream &stream_, &error_;
    std::string currentTestName_;
    std::string subStepToString(SubStep step);
};

#endif /* test_logger_h */

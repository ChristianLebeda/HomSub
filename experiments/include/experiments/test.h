#ifndef EXPERIMENTS_TEST_H
#define EXPERIMENTS_TEST_H
#include <string>
class Test
{
public:
    Test(const std::string &name, const std::string &description, bool incremental, void (*run)(int)) : name_(name), description_(description), incremental_(incremental), run_(run) {};

    std::string GetName() const {
        return name_;
    }

    std::string GetDescription() const {
        return description_;
    }

    bool isIncremental() const {
        return incremental_;
    }

    void Run(int i) {
        run_(i);
    }
private:
    std::string name_;
    std::string description_;
    bool incremental_;
    void (*run_)(int);
};

#endif /* test_h */

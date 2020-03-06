#ifndef TEST_h
#define TEST_h
#include <string>
class Test
{
public:
    Test(std::string name, std::string description, bool incremental, void (*run)(int)) : name_(name), description_(description), run_(run), incremental_(incremental) {};
    std::string GetName();
    std::string GetDescription();
    bool isIncremental() {
        return incremental_;
    }
    void Run(int i);
private:
    std::string name_;
    std::string description_;
    bool incremental_;
    void (*run_)(int);
};

#endif /* test_h */

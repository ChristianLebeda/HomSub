#ifndef TEST_h
#define TEST_h
#include <string>
class Test
{
public:
    Test(std::string name, std::string description, void (*run)()) : name_(name), description_(description), run_(run) {};
    std::string GetName();
    std::string GetDescription();
    void Run();
private:
    std::string name_;
    std::string description_;
    void (*run_)();
};

#endif /* test_h */

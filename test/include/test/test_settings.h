#ifndef TEST_SETTINGS_h
#define TEST_SETTINGS_h

#include "homomorphism/tree_width_solver.h"

class TestSettings {
public:
    TestSettings() : randomSeed_(-1), testMask_(-1), singleTest_(-1), runTestMask_(false), runSingleTest_(false), tws_(NULL) {};
    void SetRandomSeed(int seed) {
        randomSeed_ = seed;
    };
    int GetRandomSeed() {
        return randomSeed_;
    }
    void SetTWS(TreeWidthSolver *tws) {
        tws_ = tws;
    }
    void SetTestMask(int mask) {
        testMask_ = mask;
        runTestMask_ = true;
    };
    int GetTestMask() {
        return testMask_;
    }
    void SetSingleTest(int test) {
        singleTest_ = test;
        runSingleTest_ = true;
    };
    int GetSingleTest() {
        return singleTest_;
    }
    bool ShouldRunTestMask(){
        return runTestMask_;
    };
    bool ShouldRunSingleTest(){
        return runSingleTest_;
    }
private:
    int randomSeed_;
    int testMask_;
    int singleTest_;
    bool runTestMask_;
    bool runSingleTest_;
    TreeWidthSolver *tws_;
};


#endif /* test_settings_h */

#ifndef TEST_SETTINGS_h
#define TEST_SETTINGS_h

#include "homomorphism/tree_width_solver.h"

class TestSettings {
public:
    void SetRandomSeed(int seed) {
        randomSeed_ = seed;
    };
    int GetRandomSeed() {
        return randomSeed_;
    }
    void SetTWS(TreeWidthSolver *tws) {
        tws_ = tws;
    };
    void SetTestMask(int mask) {
        testMask_ = mask;
        runTestMask_ = true;
    };
    int GetTestMask() {
        return testMask_;
    };
    void SetSingleTest(int test) {
        singleTest_ = test;
        runSingleTest_ = true;
    };
    int GetSingleTest() {
        return singleTest_;
    };
    bool ShouldRunTestMask(){
        return runTestMask_;
    };
    bool ShouldRunSingleTest(){
        return runSingleTest_;
    };
    void SetPrTestRuntime(float runtime) {
        prTestRuntime_ = runtime;
    };
    int GetPrTestRuntime() {
        return prTestRuntime_;
    }
private:
    int randomSeed_;
    int testMask_;
    int singleTest_;
    bool runTestMask_;
    bool runSingleTest_;
    int prTestRuntime_;
    TreeWidthSolver *tws_;
};


#endif /* test_settings_h */

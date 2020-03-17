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
    void SetRunAll(bool run) {
        runAll_ = run;
    }
    bool GetRunAll() {
        return runAll_;
    }
    void SetSingleTest(int test) {
        singleTest_ = test;
        runSingleTest_ = true;
    };
    int GetSingleTest() {
        return singleTest_;
    };
    bool ShouldRunSingleTest(){
        return runSingleTest_;
    };
    void SetPrTestTime(float time) {
        prTestTime_ = time;
    };
    int GetPrTestTime() {
        return prTestTime_;
    }
private:
    int randomSeed_;
    int singleTest_;
    bool runSingleTest_;
    bool runAll_;
    int prTestTime_;
    TreeWidthSolver *tws_;
};


#endif /* test_settings_h */

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
    void SetGroup(bool runSanity, bool runPerformance) {
        runSanity_ = runSanity;
        runPerformance_ = runPerformance;
    }
    bool GetRunSanity() {
        return runSanity_;
    }
    bool GetRunPerformance() {
        return runPerformance_;
    }
    int GetPrTestTime() {
        return prTestTime_;
    }
    int GetRepetitions() {
        return repetitions_;
    }
    void SetRepetitions(int repetitions) {
        repetitions_ = repetitions;
    }
private:
    int randomSeed_;
    int singleTest_ = 0;
    bool runSingleTest_ = false;
    bool runAll_ = false;
    bool runSanity_;
    bool runPerformance_;
    int prTestTime_;
    int repetitions_;
    TreeWidthSolver *tws_;
};


#endif /* test_settings_h */

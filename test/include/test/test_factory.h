//
//  test_factory.h
//  test
//
//  Created by Jonas Mortensen on 26/02/2020.
//

#ifndef TEST_FACTORY_h
#define TEST_FACTORY_h
#include "test/test.h"
#include <memory>
class TestFactory
{
public:
    static std::unique_ptr<Test> GetTest(int i);
    static int TestCount();
private:
    static void Test0(int i);
    static void Test1(int i);
    static void Test2(int i);
    static void Test3(int i);
    static void Test4(int i);
    static void Test5(int i);
};

#endif /* test_factory_h */

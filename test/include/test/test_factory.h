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
    static void Test0();
    static void Test1();
    static void Test2();
    static void Test3();
    static void Test4();
};

#endif /* test_factory_h */

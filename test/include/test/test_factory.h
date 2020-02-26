//
//  test_factory.h
//  test
//
//  Created by Jonas Mortensen on 26/02/2020.
//

#ifndef TEST_FACTORY_h
#define TEST_FACTORY_h
#include "test/test.h"
class TestFactory
{
public:
    static Test GetTest(int i);
private:
    static void Test0();
    static void Test1();
};

#endif /* test_factory_h */

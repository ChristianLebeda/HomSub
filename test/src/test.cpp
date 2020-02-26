#include "test/test.h"
#include <stdio.h>

std::string Test::GetName()
{
    return name_;
}

std::string Test::GetDescription()
{
    return description_;
}

void Test::Run() {
    run_();
}

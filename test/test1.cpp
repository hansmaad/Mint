#include "mint.hpp"

struct Test1 {};

TEST_CASE(Test1, Case1)
{
    int i = 2;
    ASSERT_THAT(i, Is.EqualTo(2.6));
}

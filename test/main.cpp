#include <iostream>
#include <string>
#include "mint.hpp"

#include <boost/test/unit_test.hpp>

struct IntTest
{
};

TEST_CASE(IntTest, Minus)
{
    int result = 3 - 1;
    ASSERT_THAT(1, Is.EqualTo(2));
}

struct StringTest
{
    std::string text;
};

TEST_CASE(StringTest, Concat)
{
    text = std::string("Hello") + "World";
}

TEST_CASE(IntTest, Plus)
{
    int result = 1 + 2;
    ASSERT_THAT(result, Is.EqualTo(4));
}




int main()
{
    auto& test = Mint::TestModuleInstance();
    test.Main();
    return 0;
}


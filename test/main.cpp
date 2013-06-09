#include <iostream>
#include "mint.hpp"


struct IntTest
{
    IntTest()
    {
        std::cout << "IntTest Setup\n";
    }

    ~IntTest()
    {
        std::cout << "IntTest TearDown\n";
    }
    std::string text;
};


TEST_CASE(IntTest, Test1)
{
    text += "Test1";
    std::cout << text << "\n";
}

TEST_CASE(IntTest, Test2)
{
    text += "Test2";
    std::cout << text << "\n";
}


int main()
{
    auto& test = Mint::TestModuleInstance();
    test.Main();
    return 0;
}


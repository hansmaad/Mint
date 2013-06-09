#include <iostream>
#include "mint.hpp"


struct IntTest : Mint::TestFixture<IntTest>
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

const bool casedummy = Mint::TestModuleInstance().Register([](Mint::TestReporter& r) { IntTest::Runner().RunTestCases(r);});

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
    std::cout << "Hello World!" << std::endl;
    return 0;
}


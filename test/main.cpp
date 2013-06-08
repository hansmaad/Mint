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

};

struct Case2 : Mint::TestCase, IntTest { void Run() override; };
inline std::unique_ptr<Case2> CreateCase2() { return std::unique_ptr<Case2>(new Case2); }
const bool d1 = IntTest::Runner().Register(CreateCase2);
void Case2::Run()
{
    std::cout << "Case2\n";
}

const bool casedummy = Mint::TestModuleInstance().Register([](Mint::TestReporter& r) { IntTest::Runner().RunTestCases(r);});



int main()
{
    auto& test = Mint::TestModuleInstance();
    test.Main();
    std::cout << "Hello World!" << std::endl;
    return 0;
}


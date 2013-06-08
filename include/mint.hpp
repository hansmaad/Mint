#ifndef MINT_HPP_
#define MINT_HPP_


#include <vector>
#include <memory>
#include <functional>


namespace Mint
{

class TestReporter
{
public:
};

class TestFixtureBase
{
public:
    virtual ~TestFixtureBase() {}
    virtual void RunTestCases(TestReporter& report) const = 0;
};

struct TestCase
{
    virtual void Run() = 0;
    virtual ~TestCase() {}
};

template<typename Fixture>
class TestFixture
{
public:
    struct TestCaseRunner
    {
        void RunTestCases(TestReporter& report)
        {
            for(auto&& testCaseCreator : testCases)
            {
                auto testCase = testCaseCreator();
                testCase->Run();
            }
        }

        bool Register(std::function<std::unique_ptr<TestCase>(void)> testCaseCreator)
        {
            testCases.push_back(std::move(testCaseCreator));
            return true;
        }

        std::vector<std::function<std::unique_ptr<TestCase>(void)> > testCases;
    };

    static TestCaseRunner& Runner()
    {
        static TestCaseRunner test;
        return test;
    }

protected:

    TestReporter reporter;
};



class TestModule
{
public:
    bool Register(std::function<void(TestReporter&)> fixture)
    {
        fixtures.emplace_back(std::move(fixture));
    }

    void Main()
    {
        TestReporter reporter;
        for(const auto& fixture : fixtures)
        {
            fixture(reporter);
        }
    }

private:
    std::vector<std::function<void(TestReporter&)>> fixtures;

};


inline TestModule& TestModuleInstance()
{
    static TestModule module;
    return module;
}

}

#endif

#ifndef MINT_HPP_
#define MINT_HPP_


#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>

namespace Mint
{

class TestModule
{
public:
    bool Register(std::string testFixtureName,
                  std::string testCaseName,
                  std::function<void(void)> test)
    {
        tests.emplace_back(std::move(testFixtureName),
                           std::move(testCaseName),
                           std::move(test));
    }

    void Main()
    {        
        OrderTestsByFixture();
        for(const auto& test : tests)
        {
            std::cout << "Running " <<
                test.testFixture << '.' <<
                test.testCase << "\n";
            test.test();
        }
    }

private:
    struct TestDefinition
    {
        TestDefinition(std::string testFixture,
                       std::string testCase,
                       std::function<void(void)> test) :
            testFixture(std::move(testFixture)),
            testCase(std::move(testCase)),
            test(std::move(test))
        {
        }

        std::string testFixture;
        std::string testCase;
        std::function<void(void)> test;
    };

    void OrderTestsByFixture()
    {
        std::sort(begin(tests), end(tests),
                  [](const TestDefinition& lh, const TestDefinition& rh)
                  { return lh.testFixture < rh.testFixture ;});
    }

    std::vector<TestDefinition> tests;

};


inline TestModule& TestModuleInstance()
{
    static TestModule module;
    return module;
}


template<typename T>
struct EqualConstraint
{
    EqualConstraint(T expected) : expected(expected)
    {
    }

    template<typename A>
    void Check(const A& actual, int lineNumber) const
    {
        if (actual != expected)
            std::cout << "Line " << lineNumber << ": "
                      << "Expected: " << expected
                      << " but was " << actual << "\n";
    }
    T expected;
};


struct ConstraintHelper
{
    template<typename V>
    EqualConstraint<V> EqualTo(V value) const
    {
        return EqualConstraint<V>(std::move(value));
    }
};



}

namespace
{
    const Mint::ConstraintHelper Is;
}

#define STRINGIZE_I(s) #s
#define STRINGIZE(s) STRINGIZE_I(s)

#define CREATOR_NAME(testcase) Create ## testcase
#define DUMMY_NAME(testcase) dummy ## testcase

#define TEST_CASE_4_(fixture, testcase, creator, dummy) struct testcase : fixture  \
{ void Run(); };  \
namespace {  \
const bool dummy = Mint::TestModuleInstance().Register(#fixture, #testcase, [](){testcase t; t.Run();}); \
} \
void testcase ::Run()

#define TEST_CASE_4(fixture, testcase, creator, dummy) TEST_CASE_4_(fixture, testcase, creator, dummy)

#define TEST_CASE(fixture, testcase) TEST_CASE_4(fixture, testcase, CREATOR_NAME(testcase), DUMMY_NAME(testcase))


#define ASSERT_THAT(actual, constraint) \
    constraint.Check(actual, __LINE__);

#endif  // MINT_HPP_

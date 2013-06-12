#ifndef MINT_HPP_
#define MINT_HPP_


#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <algorithm>
#include <sstream>

namespace Mint
{
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
    
class TestReport
{
public:
    void RunningTest(const std::string& fixture, const std::string& test)
    {
        currentFixture = fixture;
        currentTest = test;
    }
    
    void Error(const char* file, int lineNumber, std::string msg)
    {
   	std::cout << file << " (line " << lineNumber << "): Error in "
   	    << currentFixture << "." << currentTest  << "  " << msg << "\n";
    }
    
    std::string currentFixture, currentTest;
};

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
        return true;
    }

    void Main()
    {        
        OrderTestsByFixture();
        for(const auto& test : tests)
        {
            Report().RunningTest( test.testFixture, test.testCase);
            test.test();
        }
    }

    TestReport& Report()
    {
        return report;
    }
    
private:
    void OrderTestsByFixture()
    {
        std::sort(begin(tests), end(tests),
                  [](const TestDefinition& lh, const TestDefinition& rh)
                  { return lh.testFixture < rh.testFixture ;});
    }

    std::vector<TestDefinition> tests;
     TestReport report;
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
    bool Check(const A& actual) const
    {
        return actual == expected;
    }
    
    template<typename A>
    std::string WriteMessage(const A& actual) const
    {
        std::stringstream msg;
        msg  << "Expected: " << expected
                  << " but was " << actual;
        return msg.str();
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
    if (!constraint.Check(actual)) \
      Mint::TestModuleInstance().Report().Error(__FILE__ , __LINE__, constraint.WriteMessage(actual)); 

#endif  // MINT_HPP_

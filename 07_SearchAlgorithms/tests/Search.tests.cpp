#include <gtest/gtest.h>
#include <Search/Search.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include "ParametersList.h"
#include "TestsFunctions.h"

using namespace std;

class SearchParamTest : public ::testing::TestWithParam<struct ParametersList<int> > {};

TEST_P(SearchParamTest, Linear)
{
    vector<int>* values = GetParam()._arr;
    auto begin = values->begin();
    auto end = values->end();

    for (auto it = begin; it != end; it++) {
        ASSERT_EQ(*LinearSearch(begin, end, *it), *it);
    }

    ASSERT_ANY_THROW(LinearSearch(begin, end, 10001));
}

TEST_P(SearchParamTest, Binary)
{
    vector<int>* values = GetParam()._arr;
    auto begin = values->begin();
    auto end = values->end();

    for (auto it = begin; it != end; it++) {
        ASSERT_EQ(*BinarySearch(begin, end, *it), *it);
    }

    ASSERT_ANY_THROW(BinarySearch(begin, end, 10001));
}

TEST_P(SearchParamTest, Fibonacci)
{
    vector<int>* values = GetParam()._arr;
    auto begin = values->begin();
    auto end = values->end();

    for (auto it = begin; it != end; it++) {
        ASSERT_EQ(*FibonacciSearch(begin, end, *it), *it);
    }

    ASSERT_ANY_THROW(FibonacciSearch(begin, end, 10001));
}

TEST_P(SearchParamTest, Interpolation)
{
    vector<int>* values = GetParam()._arr;
    auto begin = values->begin();
    auto end = --values->end();

    for (auto it = begin; it != end; it++) {
        ASSERT_EQ(*InterpolationSearch(begin, end, *it), *it);
    }

    ASSERT_ANY_THROW(InterpolationSearch(begin, end, 10001));

}

TEST_P(SearchParamTest, IndexedSequentional)
{
    vector<int>* values = GetParam()._arr;
    auto begin = values->begin();
    auto end = --values->end();

    for (auto it = begin; it != end; it++) {
        ASSERT_EQ(*IndexedSequentialSearch(begin, end, *it, 10), *it);
    }

    ASSERT_ANY_THROW(IndexedSequentialSearch(begin, end, 10001, 100));
}


INSTANTIATE_TEST_CASE_P
(
        SearchParamTest,
        SearchParamTest,
        ::testing::Values(
                ParametersList<int>{GetRandomVector(100)},
                ParametersList<int>{GetRandomVector(1000)},
                ParametersList<int>{GetRandomVector(10000)}
        )
);
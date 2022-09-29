#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "TestFunctions.h"
#include "ParametersList.h"
#include <LSDSort/LSDSort.h>
#include "TimeIt.h"

#define TEST_ARR_LENGTH 1000

using namespace std;

class LSDSortParamTest : public ::testing::TestWithParam<struct StringParametersList> {
};

TEST_P(LSDSortParamTest, LSDSort) {
    int size = GetParam()._size;
    string *arr = GetParam()._arr;

    auto lsd = TimeIt(LSDSort);
    lsd(arr, size, 10);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

void STLSort(string* start, int size) {
    sort(start, start + size);
}

TEST_P(LSDSortParamTest, STL_Sort) {
    int size = GetParam()._size;
    string *arr = GetParam()._arr;

    auto sort = TimeIt(STLSort);
    sort(arr, size);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

const int valuesCount = 10;
auto values = new string[valuesCount]{
    "cpp",
    "python",
    "javascript",
    "go",
    "php",
    "kotlin",
    "swift",
    "java",
    "sql",
    "html :)"
};

INSTANTIATE_TEST_CASE_P
(
        LSDSortParamTest,
        LSDSortParamTest,
        ::testing::Values(
                StringParametersList{TEST_ARR_LENGTH, GetRandomSortedStringArr(TEST_ARR_LENGTH, 10)},
                StringParametersList{TEST_ARR_LENGTH, GetRandomReversedStringArr(TEST_ARR_LENGTH, 10)},
                StringParametersList{TEST_ARR_LENGTH, GetRandomStringArr(TEST_ARR_LENGTH, 10)},
                StringParametersList{TEST_ARR_LENGTH, GetRandomStringArrWithDuplicates(TEST_ARR_LENGTH, values, valuesCount)}
        )
);
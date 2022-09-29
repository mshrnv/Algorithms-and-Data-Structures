#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "TestFunctions.h"
#include "ParametersList.h"
#include <QuickSort/QuickSort.h>
#include "TimeIt.h"

#define TEST_ARR_LENGTH 1000

using namespace std;

class QuickSortParamTest : public ::testing::TestWithParam<struct ParametersList> {};

TEST_P(QuickSortParamTest, QuickSort) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto quick = TimeIt(QuickSort);
    quick(arr, 0, size - 1);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

TEST_P(QuickSortParamTest, DNFQuickSort) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto quick = TimeIt(DNFQuickSort);
    quick(arr, 0, size - 1);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

void STLSort(int* arr, int size)
{
    sort(arr, arr + size);
}

TEST_P(QuickSortParamTest, STL_Sort) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto sort = TimeIt(STLSort);
    sort(arr, size);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

const int valuesCount = 10;
auto values = new int[valuesCount]{1, 2, 3,
                                   4, 5, 6,
                                   7, 8, 9, 0};

INSTANTIATE_TEST_CASE_P
(
        QuickSortParamTest,
        QuickSortParamTest,
        ::testing::Values(
                ParametersList{TEST_ARR_LENGTH, GetRandomSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomReverseSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArrWithDuplicates(TEST_ARR_LENGTH, values, valuesCount)}
        )
);
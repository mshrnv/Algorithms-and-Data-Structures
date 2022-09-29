#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "TestFunctions.h"
#include "ParametersList.h"
#include <MergeSort/MergeSort.h>
#include "TimeIt.h"

#define TEST_ARR_LENGTH 1000000

using namespace std;

class MergeSortParamTest : public ::testing::TestWithParam<struct ParametersList> {};

TEST_P(MergeSortParamTest, MergeSortIterative) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto merge = TimeIt(MergeSortIterative);
    merge(arr, size);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

TEST_P(MergeSortParamTest, MergeSortRecursive) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto merge = TimeIt(MergeSortRecursive);
    merge(arr, 0, size - 1);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

void STLStableSort(int* arr, int size)
{
    stable_sort(arr, arr + size);
}

TEST_P(MergeSortParamTest, STL_StableSort) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto stable = TimeIt(STLStableSort);
    stable(arr, size);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

const int valuesCount = 10;
auto values = new int[valuesCount]{1, 2, 3,
                                   4, 5, 6,
                                   7, 8, 9, 0};

INSTANTIATE_TEST_CASE_P
(
        MergeSortParamTest,
        MergeSortParamTest,
        ::testing::Values(
                ParametersList{TEST_ARR_LENGTH, GetRandomSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomReverseSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArrWithDuplicates(TEST_ARR_LENGTH, values, valuesCount)}
        )
);
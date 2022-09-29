#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "TestFunctions.h"
#include "ParametersList.h"
#include <HeapSort/HeapSort.h>
#include "TimeIt.h"

#define TEST_ARR_LENGTH 1000

using namespace std;

class HeapSortParamTest : public ::testing::TestWithParam<struct ParametersList> {
};

TEST_P(HeapSortParamTest, HeapSort) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto heap = TimeIt(HeapSort);
    heap(arr, size);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

void STLHeapSort(int* start, int size) {
    make_heap(start, start + size);
    sort_heap(start, start + size);
}

TEST_P(HeapSortParamTest, STL_HeapSort) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto heap = TimeIt(STLHeapSort);
    heap(arr, size);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

const int valuesCount = 10;
auto values = new int[valuesCount]{1, 2, 3,
                                   4, 5, 6,
                                   7, 8, 9, 0};

INSTANTIATE_TEST_CASE_P
(
        HeapSortParamTest,
        HeapSortParamTest,
        ::testing::Values(
                ParametersList{TEST_ARR_LENGTH, GetRandomSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomReverseSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArrWithDuplicates(TEST_ARR_LENGTH, values, valuesCount)}
        )
);
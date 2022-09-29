#include <gtest/gtest.h>
#include <algorithm>
#include "TestFunctions.h"
#include "ParametersList.h"
#include <ShellSort/ShellSort.h>
#include "TimeIt.h"
#include <cmath>

#define TEST_ARR_LENGTH 1000

using namespace std;

class ShellSortParamTest : public ::testing::TestWithParam<struct ParametersList> {};

TEST_P(ShellSortParamTest, Shell_h1) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto steps = GenerateSteps(size, [](int item){return 3 * item + 1;});
    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}




TEST_P(ShellSortParamTest, TEST) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto steps = GenerateSteps(size, H1());
//    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}





TEST_P(ShellSortParamTest, Shell_h1) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto steps = GenerateSteps(size, [](int item){return 3 * item + 1;});
    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

TEST_P(ShellSortParamTest, Shell_h2) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto steps = GenerateSteps(size, [](int item){return 2 * item + 1;});
    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

TEST_P(ShellSortParamTest, Shell_h3) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    int index = 0;
    auto steps = GenerateSteps(size, [&index](int item){
        if (index % 2 != 0) {
            return 9 * pow(2, index) - 9 * pow(2, index++ / 2) + 1;
        } else {
            return 8 * pow(2, index) - 6 * pow(2, index++ + 1 / 2) + 1;
        }
    });    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

TEST_P(ShellSortParamTest, Shell_h4) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    int index = 0;
    auto steps = GenerateSteps(size, [&index](int item){
        if (index % 2)
            return item * 3;
        else
            return item * 2;
    });
    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

TEST_P(ShellSortParamTest, Shell_h5) {
    int size = GetParam()._size;
    int *arr = GetParam()._arr;

    auto steps = GenerateSteps(size, [](int item){return 2 * item;});
    auto shell = TimeIt(ShellSort);
    shell(arr, size, steps);

    ASSERT_TRUE(std::is_sorted(arr, arr + size));
}

void STLSort(int* arr, int size)
{
    std::sort(arr, arr + size);
}

TEST_P(ShellSortParamTest, STL_Sort) {
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
        ShellSortParamTest,
        ShellSortParamTest,
        ::testing::Values(
                ParametersList{TEST_ARR_LENGTH, GetRandomSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomReverseSortedArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArr(TEST_ARR_LENGTH)},
                ParametersList{TEST_ARR_LENGTH, GetRandomArrWithDuplicates(TEST_ARR_LENGTH, values, valuesCount)}
        )
);
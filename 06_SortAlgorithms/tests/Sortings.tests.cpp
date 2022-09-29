#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include "TestFunctions.h"
#include <ShellSort/ShellSort.h>
#include <QuickSort/QuickSort.h>
#include <HeapSort/HeapSort.h>
#include <MergeSort/MergeSort.h>
#include <LSDSort/LSDSort.h>
#include "../lib/table/VariadicTable.h"
#include "TimeIt.h"
#include "ShellSort/Functors.h"

using namespace std;


TEST(SortTest, CompareTable) {
    VariadicTable<std::string, int, int> table({"Sort name", "Array size", "Execution time(ms)"});

    const int size = 100000;
    int* randomArr = GetRandomArr(size);
    long long time;

    int arr[size];
    copy(randomArr, randomArr + size, arr);
    auto heap = TimeIt(HeapSort);
    time = heap(arr, size);
    table.addRow("HeapSort", size, time);

    copy(randomArr, randomArr + size, arr);
    auto mergeIter = TimeIt(MergeSortIterative);
    time = mergeIter(arr, size);
    table.addRow("MergeSort Iterative", size, time);

    copy(randomArr, randomArr + size, arr);
    auto mergeRec = TimeIt(MergeSortRecursive);
    time = mergeRec(arr, 0, size - 1);
    table.addRow("MergeSort Recursive", size, time);

    copy(randomArr, randomArr + size, arr);
    auto quick = TimeIt(QuickSort);
    time = quick(arr, 0, size - 1);
    table.addRow("QuickSort Iterative", size, time);

    copy(randomArr, randomArr + size, arr);
    auto dnf = TimeIt(DNFQuickSort);
    time = quick(arr, 0, size - 1);
    table.addRow("DNF QuickSort", size, time);

    auto strArr = GetRandomStringArr(size, 10);
    auto lsd = TimeIt(LSDSort);
    time = lsd(strArr, size, 10);
    table.addRow("LSDSort", size, time);

    copy(randomArr, randomArr + size, arr);
    auto shell1 = TimeIt(ShellSort);
    auto steps = GenerateSteps(size, [](int item){return 3 * item + 1;});
    time = shell1(arr, size, steps);
    table.addRow("ShellSort (h1)", size, time);

    copy(randomArr, randomArr + size, arr);
    auto shell2 = TimeIt(ShellSort);
    steps = GenerateSteps(size, [](int item){return 2 * item + 1;});
    time = shell2(arr, size, steps);
    table.addRow("ShellSort (h2)", size, time);

    copy(randomArr, randomArr + size, arr);
    auto shell3 = TimeIt(ShellSort);
    int index = 0;
    steps = GenerateSteps(size, [&index](int item){
        if (index % 2 != 0) {
            return 9 * pow(2, index) - 9 * pow(2, index++ / 2) + 1;
        } else {
            return 8 * pow(2, index) - 6 * pow(2, index++ + 1 / 2) + 1;
        }
    });
    time = shell3(arr, size, steps);
    table.addRow("ShellSort (h3)", size, time);

    copy(randomArr, randomArr + size, arr);
    auto shell4 = TimeIt(ShellSort);
    index = 0;
    steps = GenerateSteps(size, [&index](int item){
        if (index % 2)
            return item * 3;
        else
            return item * 2;
    });
    time = shell4(arr, size, steps);
    table.addRow("ShellSort (h4)", size, time);

    copy(randomArr, randomArr + size, arr);
    auto shell5 = TimeIt(ShellSort);
    steps = GenerateSteps(size, [](int item){return 2 * item;});
    time = shell5(arr, size, steps);
    table.addRow("ShellSort (h5)", size, time);


    table.print(cout);
}
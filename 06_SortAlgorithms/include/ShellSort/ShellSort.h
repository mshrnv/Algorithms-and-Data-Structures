//
// Created by Misha Shoronov on 03.05.2022.
//

#ifndef SORTINGS_SHELLSORT_H
#define SORTINGS_SHELLSORT_H

#include <iostream>
#include <stack>

using namespace std;

void ShellSort(int* arr, int size, stack<int> steps) {
    auto steps = Genera (pred)
    while (!steps.empty()) {
        int step = steps.top();
        for (int i = step; i < size; i++) {
            for (int j = i; j >= step && arr[j] < arr[j - step]; j -= step) {
                swap(arr[j], arr[j - step]);
            }
        }
        steps.pop();
    }
}

#endif //SORTINGS_SHELLSORT_H

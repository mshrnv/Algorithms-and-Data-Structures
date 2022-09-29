//
// Created by Misha Shoronov on 04.05.2022.
//

#include <string>

using namespace std;

char CharAt(std::string str, int index) {
    return str[index];
}

void LSDSort(std::string *arr, int size, int radix) {

    int R = 256;
    auto sorted = new std::string[size];

    for (int d = radix - 1; d >= 0; d--) {
        int *count = new int[R + 1];

        for (int i = 0; i < size; i++) {
            count[CharAt(arr[i], d) + 1]++;
        }

        for (int r = 0; r < R; r++)
            count[r + 1] += count[r];

        for (int i = 0; i < size; i++)
            sorted[count[CharAt(arr[i], d)]++] = arr[i];

        for (int i = 0; i < size; i++)
            arr[i] = sorted[i];
    }
}
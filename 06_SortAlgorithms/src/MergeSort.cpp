//
// Created by Misha Shoronov on 03.05.2022.
//

#include <iostream>
#include <MergeSort/MergeSort.h>

using namespace std;

void Merge(int *arr, int start, int end, int mid) {
    int merged[end + 1];
    int i = start;
    int k = start;
    int j = mid + 1;

    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            merged[k] = arr[i];
            k++;
            i++;
        } else {
            merged[k] = arr[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        merged[k] = arr[i];
        k++;
        i++;
    }

    while (j <= end) {
        merged[k] = arr[j];
        k++;
        j++;
    }

    for (i = start; i < k; i++) {
        arr[i] = merged[i];
    }
}

void MergeSortRecursive(int *arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        MergeSortRecursive(arr, start, mid);
        MergeSortRecursive(arr, mid + 1, end);
        Merge(arr, start, end, mid);
    }
}

void MergeSortIterative(int *arr, int size) {
    for (int currentSize = 1; currentSize < size; currentSize *= 2) {
        for (int start = 0; start < size - 1; start += 2 * currentSize) {
            int mid = min(start + currentSize - 1, size - 1);
            int end = min(start + 2 * currentSize - 1, size - 1);
            Merge(arr, start, end, mid);
        }
    }
}


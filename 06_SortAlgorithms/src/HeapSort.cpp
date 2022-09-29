//
// Created by Misha Shoronov on 03.05.2022.
//
#include <iostream>
#include <HeapSort/HeapSort.h>

using namespace std;

void Heapify(int *arr, int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        swap(arr[root], arr[largest]);
        Heapify(arr, size, largest);
    }
}

void HeapSort(int *arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        Heapify(arr, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}
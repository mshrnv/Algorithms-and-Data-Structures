//
// Created by Misha Shoronov on 03.05.2022.
//
#include <iostream>
#include <QuickSort/QuickSort.h>
#include <stack>

using namespace std;

int Partition(int* arr , int start, int pivot)
{
    int i = start;
    while(i < pivot)
    {
        if(arr[i] > arr[pivot] && i == pivot-1)
        {
            swap(arr[i], arr[pivot]);
            pivot--;
        }

        else if(arr[i] > arr[pivot])
        {
            swap(arr[pivot - 1], arr[pivot]);
            swap(arr[i], arr[pivot]);
            pivot--;
        }

        else i++;
    }
    return pivot;
}


void QuickSort(int *arr, int start, int end) {
    stack<pair<unsigned, unsigned> > stack;
    stack.push(make_pair(start, end));

    while (!stack.empty()) {
        start = get<0>(stack.top());
        end = get<1>(stack.top());
        stack.pop();

        int p = Partition(arr, start, end);

        if (p - 1 > start) {
            stack.push(make_pair(start, p - 1));
        }

        if (p + 1 < end) {
            stack.push(make_pair(p + 1, end));
        }
    }
}

void DNFPartition(int a[], int low, int high, int &i, int &j) {
    if (high - low <= 1) {
        if (a[high] < a[low])
            swap(a[high], a[low]);
        i = low;
        j = high;
        return;
    }

    int mid = low;
    int pivot = a[high];
    while (mid <= high) {
        if (a[mid] < pivot)
            swap(a[low++], a[mid++]);
        else if (a[mid] == pivot)
            mid++;
        else if (a[mid] > pivot)
            swap(a[mid], a[high--]);
    }

    i = low - 1;
    j = mid;
}

void DNFQuickSort(int a[], int low, int high) {
    if (low >= high)
        return;

    int i, j;

    DNFPartition(a, low, high, i, j);

    DNFQuickSort(a, low, i);
    DNFQuickSort(a, j, high);
}
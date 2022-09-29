//
// Created by Misha Shoronov on 04.05.2022.
//

#ifndef SORTINGS_TESTFUNCTIONS_H
#define SORTINGS_TESTFUNCTIONS_H

#include <iostream>
#include <stack>
using namespace std;

void PrintArr(int *arr, int size)
{
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void PrintStringArr(string *arr, int size)
{
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename PredType>
stack<int> GenerateSteps(int size, PredType pred)
{
    stack<int> steps;
    int step = 1;
    steps.push(step);

    while (step < size) {
        step = pred(step);
        steps.push(step);
    }

    return steps;
}

int GetRandomNumber()
{
    return rand() % 100000;
}

int* GetRandomArr(int num)
{
    int *arr = new int[num];
    for (int i = 0; i < num; ++i) {
        arr[i] = GetRandomNumber();
    }

    return arr;
}

int* GetRandomSortedArr(int num)
{
    int* arr = GetRandomArr(num);
    sort(arr, arr + num);
    return arr;
}

int* GetRandomReverseSortedArr(int num)
{
    int* arr = GetRandomSortedArr(num);
    reverse(arr, arr + num);
    return arr;
}

int* GetRandomArrWithDuplicates(int num, int* values, int values_count)
{
    int *arr = new int[num];
    for (int i = 0; i < num; ++i) {
        arr[i] = values[GetRandomNumber() % values_count];
    }

    return arr;
}

std::string GetRandomString(int length)
{
    static const char alphanum[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string resultString;
    resultString.reserve(length);

    for (int i = 0; i < length; ++i) {
        resultString += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return resultString;
}

string* GetRandomStringArr(int size, int wordLength)
{
    string *arr = new string[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = GetRandomString(wordLength);
    }

    return arr;
}

string* GetRandomSortedStringArr(int num, int wordLength)
{
    string* arr = GetRandomStringArr(num, wordLength);
    sort(arr, arr + num);
    return arr;
}

string* GetRandomReversedStringArr(int num, int wordLength)
{
    string* arr = GetRandomSortedStringArr(num, wordLength);
    reverse(arr, arr + num);
    return arr;
}

string* GetRandomStringArrWithDuplicates(int num, string* values, int values_count)
{
    string *arr = new string[num];
    for (int i = 0; i < num; ++i) {
        arr[i] = values[GetRandomNumber() % values_count];
    }

    return arr;
}

#endif //SORTINGS_TESTFUNCTIONS_H

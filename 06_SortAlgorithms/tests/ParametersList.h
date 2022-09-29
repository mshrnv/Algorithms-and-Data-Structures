//
// Created by Misha Shoronov on 04.05.2022.
//

#ifndef SORTINGS_PARAMETERSLIST_H
#define SORTINGS_PARAMETERSLIST_H
#include <string>

using namespace std;

struct ParametersList {
    int _size;
    int *_arr;

    ParametersList(int size, int *arr) {
        _size = size;
        _arr = arr;
    }
};

struct StringParametersList {
    int _size;
    string *_arr;

    StringParametersList(int size, string *arr) {
        _size = size;
        _arr = arr;
    }
};

#endif //SORTINGS_PARAMETERSLIST_H

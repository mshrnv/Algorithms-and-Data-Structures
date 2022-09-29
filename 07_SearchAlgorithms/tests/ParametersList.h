//
// Created by Misha Shoronov on 05.06.2022.
//

#ifndef SEARCH_PARAMETERSLIST_H
#define SEARCH_PARAMETERSLIST_H

#include <vector>

using namespace std;

template <typename T>
struct ParametersList {
    vector<T>* _arr;

    ParametersList(vector<T>* arr) {
        _arr = arr;
    }
};

#endif //SEARCH_PARAMETERSLIST_H

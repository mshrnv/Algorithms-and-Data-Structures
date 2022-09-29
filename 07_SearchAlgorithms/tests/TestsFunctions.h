#ifndef SEARCH_TESTSFUNCTIONS_H
#define SEARCH_TESTSFUNCTIONS_H

#include <vector>

using namespace std;

vector<int>* GetRandomVector(size_t size)
{
    vector<int>* values = new vector<int>();

    for (size_t i = 0; i < size; ++i) {
        values->push_back(rand() % 10000);
    }

    std::sort(values->begin(), values->end());

    return values;
}

#endif //SEARCH_TESTSFUNCTIONS_H

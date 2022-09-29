#ifndef SEARCH_SEARCH_H
#define SEARCH_SEARCH_H

#include <algorithm>
#include <iterator>
#include <iostream>
#include <exception>

using namespace std;

template<typename IterType, typename T>
IterType LinearSearch(IterType first, IterType last, T value) {
    while (first < last) {
        if (*first == value)
            return first;
        first++;
    }

    throw exception(range_error("Not found"));
}

template<typename IterType, typename T, typename PredType = std::less<T> >
IterType BinarySearch(IterType first, IterType last, T value, PredType pred = PredType()) {
    while (first <= last) {
        IterType middle = first;
        std::advance(middle, std::distance(first, last) / 2);

        if (*middle == value) {
            return middle;
        }

        if (pred(value, *middle)) {
            last = --middle;
        } else {
            first = ++middle;
        }
    }

    throw exception(range_error("Not found"));
}

template<typename IterType, typename T, typename PredType = std::less<T> >
IterType FibonacciSearch(IterType first, IterType last, T value, PredType pred = PredType()) {
    int current = 1;
    int previous = 0;
    int size = distance(first, last);
    int currentSize = 0;
    int step = 1;
    IterType it = first;

    while (currentSize < size && step > 0) {
        step = min(size - currentSize - 1, current);
        advance(it, step);
        currentSize += step;

        if (*it == value) {
            return it;
        }

        if (pred(value, *it)) {
            auto itPrev = it;
            advance(itPrev, -current);
            return LinearSearch(itPrev, it, value);
        } else {
            swap(current, previous);
            current += previous;
        }

    }

    throw exception(range_error("Not found"));
}


template<typename IterType, typename T>
IterType InterpolationSearch(IterType first, IterType last, T value) {

    IterType it;

    while (*first < value && *last > value && *first != *last) {
        it = first;
        advance(it, ((value - *first) * distance(first, last)) / (*last - *first));

        if (*it == value)
            return it;

        if (*it < value) {
            first = ++it;
        } else if (*it > value) {
            last = --it;
        }
    }

    if (*first == value)
        return first;

    if (*last == value)
        return last;

    throw exception(range_error("Not found"));
}

template<typename IterType, typename T, typename PredType = std::less<T> >
IterType IndexedSequentialSearch(IterType first, IterType last, T value, int step, PredType pred = PredType()) {
    int size = distance(first, last);
    int currentSize = 0;
    IterType it = first;

    while (it < last && step > 0) {
        step = min(size - currentSize - 1, step);

        advance(it, step);
        currentSize += step;

        if (value == *it)
            return it;

        if (pred(value, *it)) {
            auto itPrev = it;
            advance(itPrev, -step);
            return LinearSearch(itPrev, it, value);
        }
    }

    throw exception(range_error("Not found"));
}

#endif //SEARCH_SEARCH_H

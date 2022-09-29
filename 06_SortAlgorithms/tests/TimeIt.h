//
// Created by Misha Shoronov on 11.05.2022.
//

#ifndef SORTINGS_TIMEIT_H
#define SORTINGS_TIMEIT_H

#include <iostream>
#include <chrono>

template <class> struct Decorator;

template <typename R, class... Args>
struct Decorator<R(Args ...)>
{
    Decorator(std::function<R(Args ...)> f) : f_(f) {}

    int operator()(Args ... args)
    {
        auto begin = std::chrono::steady_clock::now();
        f_(args...);
        auto end = std::chrono::steady_clock::now();
        auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << "Execution time: " << milliSeconds.count() << " ms" <<endl;
        return milliSeconds.count();
    }
    std::function<R(Args ...)> f_;
};

template<typename R, class... Args>
Decorator<R(Args...)> TimeIt(R (*f)(Args ...))
{
    return Decorator<R(Args...)>(std::function<R(Args...)>(f));
}

#endif //SORTINGS_TIMEIT_H

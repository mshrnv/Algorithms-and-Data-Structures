#ifndef SET_DOUBLEFUNCTOR_H
#define SET_DOUBLEFUNCTOR_H

#include <math.h>

class DoubleFunctor
{
public:
    DoubleFunctor() {}

    bool operator() (double a, double b) const
    {
        return abs(a) == abs(b);
    }
};

#endif //SET_DOUBLEFUNCTOR_H

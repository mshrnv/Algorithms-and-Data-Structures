#ifndef SET_CONEFUNCTOR_H
#define SET_CONEFUNCTOR_H

#include "Cone/Cone.h"

class ConeFunctor
{
public:
    bool operator()(Cone *a, Cone *b)
    {
        return a->CalculateSquare() == b->CalculateSquare();
    }
};

#endif //SET_CONEFUNCTOR_H

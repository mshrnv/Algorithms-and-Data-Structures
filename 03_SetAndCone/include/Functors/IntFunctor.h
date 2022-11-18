#ifndef SET_INTFUNCTOR_H
#define SET_INTFUNCTOR_H

class IntFunctor
{
public:
    IntFunctor() {}

    bool operator() (int a, int b) const
    {
        return a == b;
    }
};

#endif //SET_INTFUNCTOR_H

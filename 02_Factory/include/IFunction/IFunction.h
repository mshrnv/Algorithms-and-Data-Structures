#ifndef IFUNCTION_IFUNCTION_H
#define IFUNCTION_IFUNCTION_H

#include <iostream>
#include <utility>

using namespace std;

class IFunction
{
public:
    virtual ~IFunction() {};
    virtual pair<double, double> Solve(double x) = 0;
    virtual void Save(ostream& stream) = 0;
};

typedef std::shared_ptr<IFunction> FunctionPtr;
typedef IFunction* (*IFunctionPtr)(ifstream& stream);

#endif //IFUNCTION_IFUNCTION_H

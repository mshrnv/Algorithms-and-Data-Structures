#ifndef IFUNCTION_HYPERBOLAFUNCTION_H
#define IFUNCTION_HYPERBOLAFUNCTION_H

#include "IFunction.h"
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

class HyperbolaFunction: public IFunction
{
public:
    HyperbolaFunction(double a, double b);
    ~HyperbolaFunction() {};
    pair<double, double> Solve(double x) final;
    void Save(ostream& stream) override;
    static IFunction* Load(ifstream& stream);
private:
    double _a;
    double _b;
};

HyperbolaFunction::HyperbolaFunction(double a, double b): _a(a), _b(b) {}

pair<double, double> HyperbolaFunction::Solve(double x)
{
    pair<double, double> result;

    result.first = sqrt(pow(_b, 2) * ((pow(x, 2) / pow(_a, 2)) - 1));
    result.second = -result.first;

    return result;
}

void HyperbolaFunction::Save(ostream& stream)
{
    stream << "Hyperbola " << _a << " " << _b << endl;
}

IFunction* HyperbolaFunction::Load(ifstream &stream)
{
    double a;
    double b;

    stream >> a >> b;

    return new HyperbolaFunction(a, b);
}

#endif //IFUNCTION_HYPERBOLAFUNCTION_H

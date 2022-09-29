#ifndef IFUNCTION_ELLIPSEFUNCTION_H
#define IFUNCTION_ELLIPSEFUNCTION_H

#include "IFunction.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>

using namespace std;

class EllipseFunction: public IFunction
{
public:
    EllipseFunction(double a, double b);
    ~EllipseFunction() {};
    pair<double, double> Solve(double x) final;
    void Save(ostream& stream) override;
    static IFunction* Load(ifstream& stream);
private:
    double _a;
    double _b;
};

EllipseFunction::EllipseFunction(double a, double b): _a(a), _b(b) {}

pair<double, double> EllipseFunction::Solve(double x)
{
    pair<double, double> result;

    result.first = sqrt(pow(_b, 2) * (1 - ((pow(x, 2) / pow(_a, 2)))));
    result.second = -result.first;

    return result;
}

void EllipseFunction::Save(ostream& stream)
{
    stream << "Ellipse " << _a << " " << _b << endl;
}

IFunction* EllipseFunction::Load(ifstream &stream)
{
    double a;
    double b;

    stream >> a >> b;

    return new EllipseFunction(a, b);
}

#endif //IFUNCTION_ELLIPSEFUNCTION_H

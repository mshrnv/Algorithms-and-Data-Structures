#ifndef SET_CONE_H
#define SET_CONE_H

#include <math.h>
#include <ostream>

using namespace std;

class Cone {
public:
    Cone();
    Cone(double height, double radius);
    Cone(const Cone& other);
    Cone(Cone&& other);
    ~Cone();

    void InitializeFrom(const Cone& other);
    Cone operator=(const Cone& other);
    Cone operator=(Cone&& other);

    double GetRadius();
    double GetHeight();
    void SetRadius(double radius);
    void SetHeight(double height);
    double CalculateSquare();

    bool operator==(const Cone& other) const;
    bool operator!=(const Cone& other) const;
    friend ostream &operator<<(ostream& os, const Cone& cone);

private:
    double _height;
    double _radius;
};


Cone::Cone()
{
    _height = 0;
    _radius = 0;
}

Cone::Cone(double height, double radius)
{
    this->_height = height;
    this->_radius = radius;
}

void Cone::InitializeFrom(const Cone& other)
{
    this->_height = other._height;
    this->_radius = other._radius;
}

Cone::Cone(const Cone& other)
{
    InitializeFrom(other);
}

Cone::Cone(Cone&& other)
{
    InitializeFrom(other);

    other._height = 0;
    other._radius = 0;
}

Cone::~Cone()
{
    _height = 0;
    _radius = 0;
}

Cone Cone::operator=(const Cone& other)
{
    if (this != &other) {
        InitializeFrom(other);
    }

    return *this;
}

Cone Cone::operator=(Cone&& other)
{
    if (this != &other) {
        InitializeFrom(other);

        other._height = 0;
        other._radius = 0;
    }

    return *this;
}

double Cone::GetHeight()
{
    return this->_height;
}

double Cone::GetRadius()
{
    return this->_radius;
}

void Cone::SetHeight(double height)
{
    this->_height = height;
}

void Cone::SetRadius(double radius)
{
    this->_radius = radius;
}

double Cone::CalculateSquare()
{
    return M_PI * _radius * (sqrt(pow(_radius, 2) + pow(_height, 2)) + _radius);
}

bool Cone::operator==(const Cone& other) const
{
    return _height == other._height && _radius == other._radius;
}

bool Cone::operator!=(const Cone& other) const
{
    return !(other == *this);
}

ostream &operator<<(ostream& os, const Cone& cone)
{
    os << "Cone(";
    os << "_height: " << cone._height << "; _radius: " << cone._radius;
    os << ")" << endl;
    return os;
}

#endif //SET_CONE_H

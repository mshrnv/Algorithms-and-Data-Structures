#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <Rectangle/Rectangle.h>

using namespace std;

int& Rectangle::Count()
{
    static int object_counter = 0;
    return object_counter;
}

char* Rectangle::CreateRectangleName(int n)
{
    std::string int_string = std::to_string(n);
    const char* number = int_string.c_str();
    const char* rectangle = "Rectangle_";

    char* rectangleName = new char[strlen(rectangle) + strlen(number) + 1];
    strcpy(rectangleName, rectangle);
    strcat(rectangleName, number);

    return rectangleName;
}

Rectangle::Rectangle()
{
    _name = CreateRectangleName(++Count());
    _point = Point(0, 0);
    _height = 0;
    _width = 0;
}

Rectangle::Rectangle(int x, int y, int height, int width)
{
    if (height < 0 || width < 0)
        throw std::runtime_error("Invalid size of Rectangle");

    _name = CreateRectangleName(++Count());
    _point = Point(x, y);
    _height = height;
    _width = width;
}

Rectangle::~Rectangle()
{
    _name = nullptr;
    --Count();
}

Point Rectangle::GetPoint() const
{
    return _point;
}

int Rectangle::GetHeight() const
{
    return _height;
}

int Rectangle::GetWidth() const
{
    return _width;
}

char* Rectangle::GetName() const
{
    return _name;
}

void Rectangle::SetPoint(Point point)
{
    _point = point;
}

void Rectangle::SetHeight(int height)
{
    if (height < 0)
        throw std::runtime_error("Invalid size of Rectangle");

    _height = height;
}

void Rectangle::SetWidth(int width)
{
    if (width < 0)
        throw std::runtime_error("Invalid size of Rectangle");

    _width = width;
}

void Rectangle::SetName(char* name)
{
    _name = name;
}

Rectangle::Rectangle(const Rectangle& other)
{
    _name = other._name;
    _point = other._point;
    _height = other._height;
    _width = other._width;

    ++Count();
}

Rectangle::Rectangle(Rectangle&& other)
{
    _name = other.GetName();
    _width = other.GetWidth();
    _height = other.GetHeight();
    _point = other.GetPoint();

    other._width = 0;
    other._height = 0;
    other._point = Point(0, 0);
    other._name = nullptr;

    ++Count();
}

const Rectangle& Rectangle::operator=(const Rectangle& other)
{
    if (this == &other)
        return *this;

    _width = other._width;
    _height = other._height;
    _point = other._point;

    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other)
{
    if (this == &other)
        return *this;

    _width = other._width;
    _height = other._height;
    _point = other._point;

    other._width = 0;
    other._height = 0;
    other._point = Point(0, 0);
    other._name = nullptr;

    return *this;
}

Rectangle operator+ (const int number, const Rectangle& rectangle)
{
    Rectangle resultRectangle;

    resultRectangle.SetPoint(rectangle._point);
    resultRectangle.SetWidth(rectangle._width + number);
    resultRectangle.SetHeight(rectangle._height + number);

    return resultRectangle;
}

Rectangle operator+ (const Rectangle& rectangle, const int number)
{
    Rectangle resultRectangle;

    resultRectangle.SetPoint(rectangle._point);
    resultRectangle.SetWidth(rectangle._width + number);
    resultRectangle.SetHeight(rectangle._height + number);

    return resultRectangle;
}

Rectangle Rectangle::GetIntersection(const Rectangle first, const Rectangle second)
{

    Rectangle resultRectangle;

    int y = min(first._point.y, second._point.y);
    int x = max(first._point.x, second._point.x);
    int height = y - max(first._point.y - first._height, second._point.y - second._height);
    int width = min(first._point.x + first._width, second._point.x + second._width) - x;

    if (width <= 0 || height <= 0)
        return resultRectangle;

    resultRectangle._point.x = x;
    resultRectangle._point.y = y;
    resultRectangle._width = width;
    resultRectangle._height = height;

    return resultRectangle;
}

Rectangle Rectangle::GetSmallestRectangleContaining(const Rectangle first, const Rectangle second)
{
    Rectangle resultRectangle;

    int y = max(first._point.y, second._point.y);
    int x = min(first._point.x, second._point.x);
    int height = y - min(first._point.y - first._height, second._point.y - second._height);
    int width = max(first._point.x + first._width, second._point.x + second._width) - x;

    resultRectangle._point.x = x;
    resultRectangle._point.y = y;
    resultRectangle._width = width;
    resultRectangle._height = height;

    return resultRectangle;
}

ostream& operator<<(ostream& out, const Rectangle& object)
{
    out << object.GetName() << ":" << endl;
    out << "Width: " << object.GetWidth() << endl;
    out << "Height: " << object.GetHeight() << endl;
    out << "Left corner point: x=" << object.GetPoint().x << ", y=" << object.GetPoint().y << endl << endl;

    return out;
}

bool Rectangle::operator==(const Rectangle& other)
{
    return _height == other._height && _width == other._width && _point.x == other._point.x &&
           _point.y == other._point.y;
}

bool Rectangle::operator!=(const Rectangle& other)
{
    return _height != other._height || _width != other._width || _point.x != other._point.x ||
           _point.y != other._point.y;
}

int Rectangle::getArea()
{
    return _height * _width;
}

int Rectangle::getPerimeter()
{
    return 2 * (_height + _width);
}
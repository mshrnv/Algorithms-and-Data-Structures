#ifndef RECTANGLE_RECTANGLE_H
#define RECTANGLE_RECTANGLE_H

#include <iostream>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int x, int y) {
        this -> x = x;
        this -> y = y;
    }
};

class Rectangle {
public:
    Rectangle();
    Rectangle(int x, int y, int height, int width);
    Rectangle(const Rectangle& object);
    Rectangle(Rectangle&& other);
    ~Rectangle();

    const Rectangle& operator= (const Rectangle& other);
    Rectangle& operator= (Rectangle&& other);
    friend Rectangle operator+ (const int number, const Rectangle& rectangle);
    friend Rectangle operator+ (const Rectangle& rectangle, const int number);
    bool operator== (const Rectangle& other);
    bool operator!= (const Rectangle& other);

    static Rectangle GetSmallestRectangleContaining(const Rectangle first, const Rectangle second);
    static Rectangle GetIntersection(const Rectangle first, const Rectangle second);
    int getArea();
    int getPerimeter();

    char* GetName() const;
    Point GetPoint() const;
    int GetHeight() const;
    int GetWidth() const;

    void SetName(char* name);
    void SetPoint(Point point);
    void SetHeight(int height);
    void SetWidth(int width);

    friend ostream& operator<< (ostream& out, const Rectangle& other);

private:

    char* _name;
    Point _point = Point(0,0);
    int _height = 0;
    int _width = 0;

    char* CreateRectangleName(int n);
    int& Count();
};

#endif //RECTANGLE_RECTANGLE_H

#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
using namespace std;

namespace ProjectLibrary
{

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y)
    {
        cout << "Coordinates are: (" << x << ", " << y << ")" << endl;
    }
};


class Triangle
{
private:
    Point p1,p2,p3;

public:
    // controlla se i punti sono collineari
    bool collineari(Point p1, Point p2, Point p3);

    // ritorna il circocentro
    Point CircoCentro(Point p1, Point p2, Point p3);

    // controlla se un nuovo punto q è nel circocerchio del triangolo
    bool isInTheCircle(const Point& q);
};







}



#endif // __EMPTY_H

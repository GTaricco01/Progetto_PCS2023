#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>

using namespace std;

namespace ProjectLibrary
{

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
    /*{
        cout << "Coordinates are: (" << x << ", " << y << ")" << endl;
    }*/

    friend inline Point operator - (const Point& p1, const Point& p2)
    {
        return Point(p1.x-p2.x,p1.y-p2.y);
    }
    friend inline double operator * (const Point& p1, const Point& p2)
    {
        return p1.x*p2.x + p1.y*p2.y;
    }
    friend inline double norm(const Point& p)
    {
        return sqrt(p.x*p.x + p.y*p.y);
    }
};


class Triangle
{
private:
    Point p1,p2,p3;

public:
    Triangle(Point& p1, Point& p2, Point& p3) : p1(p1), p2(p2), p3(p3){}

    // controlla se i punti sono collineari
    bool Collineari(Point p1, Point p2, Point p3, double tol = 1e-12);

    // calcola il circocentro
    Point CircoCentro(Point p1, Point p2, Point p3);

    // controlla se un nuovo punto q è nel circocerchio del triangolo
    bool IsInTheCircle(Point& p1, Point& p2, Point& p3, Point& d);
};







}



#endif // __EMPTY_H

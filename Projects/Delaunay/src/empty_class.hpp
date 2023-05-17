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

// calcola il lato
struct Edge
{
    Point p1, p2, e;
    Edge(Point p1, Point p2)
    {
        e.x = p2.x-p1.x;
        e.y = p2.y-p2.y;
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

};







}



#endif // __EMPTY_H

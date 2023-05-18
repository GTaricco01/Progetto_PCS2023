#include "empty_class.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include "eigen\eigen"

namespace ProjectLibrary
{

Point CircoCentro(Point p1, Point p2, Point p3)
{
    Point c;

    return c;
}

bool Triangle::isInTheCircle(const Point& q) {
    Eigen::Matrix3d M;
    M << p1.x-q.x, p1.y-q.y, (p1.x-q.x)*(p1.x-q.x)+(p1.y-q.y)*(p1.y-q.y),
         p2.x-q.x, p2.y-q.y, (p2.x-q.x)*(p2.x-q.x)+(p2.y-q.y)*(p2.y-q.y),
         p3.x-q.x, p3.y-q.y, (p3.x-q.x)*(p3.x-q.x)+(p3.y-q.y)*(p3.y-q.y);
    return (M.determinant() > 0); //da considerare tolleranza
}

}

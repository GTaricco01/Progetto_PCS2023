#include "empty_class.hpp"
#include <complex>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Eigen/Eigen"

using namespace Eigen;
using namespace ProjectLibrary;

namespace ProjectLibrary
{

Point Triangle::CircoCentro()
{
    Point cc;
    Point lato12, lato23, lato31;
    lato12 = p2-p1;
    lato23 = p3-p2;
    lato31 = p1-p3;

    double alpha, beta, gamma;
    alpha = acos(lato12*lato31/(norm(lato12) * norm(lato31)));
    beta  = acos(lato12*lato23/(norm(lato12) * norm(lato23)));
    gamma = acos(lato23*lato31/(norm(lato23) * norm(lato31)));

    cc=Point((p1.x*sin(2*alpha) + p2.x*sin(2*beta) + p3.x*sin(2*gamma))/(sin(2*alpha)+sin(2*beta)+sin(2*gamma)),
             (p1.y*sin(2*alpha) + p2.y*sin(2*beta) + p3.y*sin(2*gamma))/(sin(2*alpha)+sin(2*beta)+sin(2*gamma)));

    return cc;
}

bool Triangle::isInTheCircle(const Point& q) {
    Eigen::Matrix3d M;
    M << p1.x-q.x, p1.y-q.y, (p1.x-q.x)*(p1.x-q.x)+(p1.y-q.y)*(p1.y-q.y),
         p2.x-q.x, p2.y-q.y, (p2.x-q.x)*(p2.x-q.x)+(p2.y-q.y)*(p2.y-q.y),
         p3.x-q.x, p3.y-q.y, (p3.x-q.x)*(p3.x-q.x)+(p3.y-q.y)*(p3.y-q.y);
    return (M.determinant() > 0); //da considerare tolleranza
}

bool Triangle::Collineari(double tol)
{
    // sono collineari se l'area del triangolo è minore della tolleranza
    double alpha;
    Point lato12, lato31;
    lato12 = p2-p1;
    lato31 = p1-p3;
    alpha = acos(lato12*lato31/(norm(lato12) * norm(lato31)));

    return (alpha <= tol);
}

bool Triangle::IsInTheCircle(Point& d)
{
    // assuming points are ordered in counterclockwise order

    Matrix<double, 3, 3> mat;
    mat << p1.x-d.x, p1.y-d.y, (p1.x-d.x)*(p1.x-d.x) + (p1.y-d.y)*(p1.y-d.y),
        p2.x-d.x, p2.y-d.y, (p2.x-d.x)*(p2.x-d.x) + (p2.y-d.y)*(p2.y-d.y),
        p3.x-d.x, p3.y-d.y, (p3.x-d.x)*(p3.x-d.x) + (p3.y-d.y)*(p3.y-d.y);

    return (mat.determinant() > 0);
}

// controllo su tutti i punti
bool Point::isCounter(vector<Point> points)
{
    unsigned int n = points.size();
    // ultimo punto con il primo
    int s = (points[0].x-points[n-1].x)*(points[0].y+points[n-1].y);

    for (unsigned int i = 1; i < n; i++)
    {
        s += (points[i].x-points[i-1].x)*(points[i].y+points[i-1].y);
    }

    return (s < 0); // se è zero? boh
}

// controllo sul singolo triangolo
bool Triangle::isCounterClockWise()
{
    int s = (p2.x-p1.x)*(p2.y+p1.y) +
            (p3.x-p2.x)*(p3.y+p2.y) +
            (p1.x-p3.x)*(p1.y+p3.y);

    return (s < 0);
}
/*
vector<Point> Reader::MakeVector()
{
    file.open(input);
    getline(file,line);
    while (!file.eof())
    {
        double id, x, y;
        getline(file,line);
        istringstream cast(line);

        cast >> id >> x >> y;
        points.push_back(Point(x,y));
    }

    for (Point p : points)
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    return points;
}
*/

}













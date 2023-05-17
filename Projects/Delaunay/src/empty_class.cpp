#include "empty_class.hpp"
#include <complex>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Eigen/Eigen"

using namespace Eigen;
namespace ProjectLibrary
{



Point CircoCentro(Point p1, Point p2, Point p3)
{
    Point cc;
    Point lato12, lato23, lato31;
    lato12 = p2-p1;
    lato23 = p3-p2;
    lato31 = p1-p3;

    double alpha = 0.0, beta = 0.0, gamma = 0.0;
    alpha = acos(lato12*lato31/(norm(lato12) * norm(lato31)));
    beta= acos(lato12*lato23/(norm(lato12) * norm(lato23)));
    gamma = acos(lato23*lato31/(norm(lato23) * norm(lato31)));

    cc=Point((p1.x*sin(2*alpha) + p2.x*sin(2*beta) + p3.x*sin(2*gamma))/(sin(2*alpha)+sin(2*beta)+sin(2*gamma)),
             (p1.y*sin(2*alpha) + p2.y*sin(2*beta) + p3.y*sin(2*gamma))/(sin(2*alpha)+sin(2*beta)+sin(2*gamma)));

    return cc;
}

bool Collineari(Point& p1, Point& p2, Point& p3, double tol = 1e-12)
{
    // sono collineari se l'area del triangolo è minore della tolleranza
    double area, alpha;
    Point lato12, lato31;
    lato12 = p2-p1;
    lato31 = p1-p3;
    alpha = acos(lato12*lato31/(norm(lato12) * norm(lato31)));

    area = .5 * sin(alpha) * norm(lato12) * norm(lato31);
    if (area <= tol)
        return true;
    else
        return false;
}

bool IsInTheCircle(const Point& q) {
    Matrix<3, 3, double> M;
    M<< p1.x-q.x;
}

}

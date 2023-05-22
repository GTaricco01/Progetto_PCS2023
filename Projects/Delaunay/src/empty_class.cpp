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

bool Collineari(const Point &p1, const Point &p2, const Point &p3, double tol)
{
    // sono collineari se l'area del triangolo è minore della tolleranza
    double prodotto;
    Point lato12, lato31;
    lato12 = p2-p1;
    lato31 = p1-p3;
    prodotto = prod(lato12,lato31);

    return (abs(prodotto) <= tol);

}
bool Triangle::IsInTheCircle(const Point& d)
{
    // assuming points are ordered in counterclockwise order

    Matrix<double, 3, 3> mat;
    mat << p1.x-d.x, p1.y-d.y, (p1.x-d.x)*(p1.x-d.x) + (p1.y-d.y)*(p1.y-d.y),
        p2.x-d.x, p2.y-d.y, (p2.x-d.x)*(p2.x-d.x) + (p2.y-d.y)*(p2.y-d.y),
        p3.x-d.x, p3.y-d.y, (p3.x-d.x)*(p3.x-d.x) + (p3.y-d.y)*(p3.y-d.y);

    return (mat.determinant() > 0);
}

// controllo su tutti i punti
bool isCounter(vector<Point> points)
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

map<unsigned int, Point> Reader::MakeVector(const string& input)
{
    file.open(input);
    getline(file,line);
    while (!file.eof())
    {
        double id, x, y;
        getline(file,line);
        istringstream cast(line);

        cast >> id >> x >> y;
        points.insert(pair<unsigned int, Point> (id,Point(x,y)));
    }
    /*
    for (Point p : points)
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }*/
    return points;
}


// due cicli: while e for. While vero o falso controllo se il triangolo continua a non avere punti alò'interno del suo cirxocentro
// con il For itero sui punti e controllo se stanno dentro il circocentro
vector<Triangle> Triangulation::Delaunay(map<unsigned int, Point>& points)
{
    bool flag = true;
    while (flag)
    {
        Triangle t;
        t = Triangle(Point(points[0].x,points[0].y),
                     Point(points[1].x,points[1].y),
                     Point(points[2].x,points[2].y));
        for (unsigned int i = 3; i < points.size(); i++)
        {


            if (!t.isCounterClockWise())
            {
                ......
                    flag = False;
            }

        }

    }








    return triangles;
}












}













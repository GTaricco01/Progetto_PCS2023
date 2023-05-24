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

void Triangulation::Connect(unsigned int& index, Triangle& t, Point& d)
{
    index = 0;
    t.p1;
}

// due cicli: while e for. While vero o falso controllo se il triangolo continua a non avere punti alò'interno del suo cirxocentro
// con il For itero sui punti e controllo se stanno dentro il circocentro
map<unsigned int, Triangle> Triangulation::Delaunay(map<unsigned int, Point>& points)
{
    unsigned int n = points.size();
    // define super triangle
    double minX, minY, maxX, maxY;
    minX = points[0].x;
    minY = points[0].y;
    maxX = minX;
    maxY = minY;

    for (unsigned int i = 1; i < n; i++)
    {
        minX = min(minX, points[i].x);
        minY = min(minY, points[i].y);
        maxX = max(maxX, points[i].x);
        maxY = max(maxY, points[i].y);
    }

    // width e height della scatola che racchiude i punti
    double dx, dy;
    dx = maxX - minX;
    dy = maxY - minY;

    // punti medi di questi lati
    double midX, midY;
    midX = (maxX + minX) / 2;
    midY = (maxY + minY) / 2;

    // punti scelti fuori dal dataset in modo tale da assicurare che il super triangolo contenga tutti i punti
    Point p1, p2, p3;
    p1 = Point(minX - 2 * dx, minY - dy / 2);
    p2 = Point(maxX + 2 * dx, minY - dy / 2);
    p3 = Point(midX, 2 * maxY + dy);
    // così ho la garanzia che ogni punto del dataset sia racchiuso dal triangolo

    Triangle tmax = Triangle(p1, p2, p3);
    triangles.insert(pair<unsigned int, Triangle> (0,tmax));
    bool flag = false;
    while (!flag)
    {
        unsigned int i = 0;
        for (unsigned int j = 0; j < n; j++)
        {
            if (triangles[i].IsInTheCircle(points[j]))
            {
                /* togliere il triangolo corrente
                 * connettere i vertici del triangolo corrente con il punto points[j]
                 * aggiungere i triangoli creati a triangles (chiamo connect())
                 *
                 *
                 * */
                i++;
            }
        }
    }

    // bisogna aggiornare gli indici mano a mano che triangles viene riempita e svuotata









    return triangles;
}












}













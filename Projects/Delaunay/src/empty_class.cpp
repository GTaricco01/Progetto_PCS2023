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

bool Collinear(const Point &p1, const Point &p2, const Point &p3, double tol)
{
    // sono collineari se l'area del triangolo è minore della tolleranza
    double prodotto;
    Point lato12, lato31;
    lato12 = p2-p1;
    lato31 = p1-p3;
    prodotto = prod(lato12,lato31);

    return (abs(prodotto) <= tol);
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

Point Triangle::CircumCentre()
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

bool Triangle::IsInTheCircle(const Point& d)
{
    // assuming points are ordered in counterclockwise order

    Matrix<double, 3, 3> mat;
    mat << p1.x-d.x, p1.y-d.y, (p1.x-d.x)*(p1.x-d.x) + (p1.y-d.y)*(p1.y-d.y),
        p2.x-d.x, p2.y-d.y, (p2.x-d.x)*(p2.x-d.x) + (p2.y-d.y)*(p2.y-d.y),
        p3.x-d.x, p3.y-d.y, (p3.x-d.x)*(p3.x-d.x) + (p3.y-d.y)*(p3.y-d.y);

    return (mat.determinant() > 0);
}

// controllo sul singolo triangolo
bool Triangle::isCounterClockWise()
{
    int s = (p2.x-p1.x)*(p2.y+p1.y) +
            (p3.x-p2.x)*(p3.y+p2.y) +
            (p1.x-p3.x)*(p1.y+p3.y);

    return (s < 0);
}

vector<Triangle> Triangle::Connect(const Point& d)
{
    vector<Triangle> vec;
    vec.push_back(Triangle(p1, p2, d));
    vec.push_back(Triangle(p2, p3, d));
    vec.push_back(Triangle(p3, p1, d));

    return vec;
}

bool Triangulation::TrianglesShareEdge(Triangle& t1, Triangle& t2)
{
    unsigned int shared = 0;
    if (t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3)
        shared++;
    if (t1.p2 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3)
        shared++;
    if (t1.p3 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3)
        shared++;
    return shared == 2;
}




void Triangulation::Flip(Triangle& t1, Triangle& t2)
{
    Point shared1, shared2, nshared1, nshared2;

    if (t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3)
    {
        shared1 = t1.p1;
        shared2 = t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3 ? t1.p2 : t1.p3;
        nshared1 = t2.p1;
        nshared2 = t2.p2 == shared2 ? t2.p3 : t2.p2;
    }
    else if (t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3)
    {
        shared1 = t1.p2;
        shared2 = t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3 ? t1.p1 : t1.p3;
        nshared1 = t2.p1;
        nshared2 = t2.p2 == shared2 ? t2.p3 : t2.p2;
    }
    else
    {
        shared1 = t1.p3;
        shared2 = t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3 ? t1.p1 : t1.p2;
        nshared1 = t2.p1;
        nshared2 = t2.p2 == shared2 ? t2.p3 : t2.p2;
    }


    t1 = Triangle(shared1, shared2, nshared1);
    t2 = Triangle(shared1, nshared1, nshared2);


}




vector<Triangle> Triangulation::Delaunay(vector<Point>& points)
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
    double dx, dy, midX;
    dx = maxX - minX;
    dy = maxY - minY;
    midX = (maxX + minX) / 2;

    // punti scelti fuori dal dataset in modo tale da assicurare che il super triangolo contenga tutti i punti
    Point p1(minX - 2 * dx, minY - dy / 2);
    Point p2(maxX + 2 * dx, minY - dy / 2);
    Point p3(midX, 2 * maxY + dy);

    // così ho la garanzia che ogni punto del dataset sia racchiuso dal triangolo
    if (!Collinear(p1,p2,p3))
        triangles.push_back(Triangle(p1,p2,p3));

    for (const Point& p : points)
    {
        vector<Triangle> invalidTriangles;
        for (Triangle& t : triangles)
        {
            if (!Collinear(t.p1, t.p2, t.p3))
            {
                if (t.IsInTheCircle(p))
                {
                    invalidTriangles.push_back(t);
                }
            }
        }

        // find the boundary edges of the polygon formed by invalid triangles
        vector<pair<Point,Point>> boundaryEdges;
        for (const Triangle& t : invalidTriangles)
        {
            boundaryEdges.emplace_back(t.p1, t.p2);
            boundaryEdges.emplace_back(t.p2, t.p3);
            boundaryEdges.emplace_back(t.p3, t.p1);
        }

        // remove invalid triangles from the triangulation
        triangles.erase(remove_if(triangles.begin(), triangles.end(),
                                  [&](const Triangle& t)
                                  {
                                    return find(invalidTriangles.begin(),invalidTriangles.end(),t) != invalidTriangles.end();
                                  }), triangles.end());
        pair<Point,Point> aux;
        for (const auto& edge : boundaryEdges)
        {

            /*if(edge è in comune con due triangoli)
            {
                if(la somma degli angoli opposti all'edge <= 180°)
                {
                    allora fai il push back perché il triangolo è valido
                }
            }
            */

            triangles.push_back(Triangle(edge.first, edge.second, p));
            aux = edge;
        }
    }
    triangles.erase(remove_if(triangles.begin(), triangles.end(),
                              [&](Triangle& t)
                              {
                                  return t.p1 == p1 ||
                                         t.p1 == p2 ||
                                         t.p1 == p3 ||
                                         t.p2 == p1 ||
                                         t.p2 == p2 ||
                                         t.p2 == p3 ||
                                         t.p3 == p1 ||
                                         t.p3 == p2 ||
                                         t.p3 == p3;

                              }), triangles.end());

    for (const Triangle& t : triangles) {
        cout << "(" << t.p1.x << "," << t.p1.y << ") ";
        cout << "(" << t.p2.x << "," << t.p2.y << ") ";
        cout << "(" << t.p3.x << "," << t.p3.y << ")" << endl;
    }




    return triangles;
}


vector<Point> Reader::MakeVector(const string& input)
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
    /*
    for (Point p : points)
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }*/
    return points;
}


} // namespace ProjectLibrary

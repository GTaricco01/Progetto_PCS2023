#include "empty_class.hpp"
#include <iostream>
#include <cmath>
#include "Eigen/Eigen"

using namespace Eigen;
using namespace ProjectLibrary;

namespace ProjectLibrary
{

bool Collinear(const Point &p1, const Point &p2, const Point &p3)
{
    // sono collineari se l'area del triangolo è minore della tolleranza
    double s;
    s = prod(p2-p1, p3-p1);

    return (s == 0);
}

// controllo su tutti i punti
bool isCounter(const Point& p1, const Point& p2, const Point& p3)
{
    double s;
    s = prod(p2-p1, p3-p1);
    return (s >= 0);
}

Triangle::Triangle(const Point& _p1, const Point& _p2, const Point& _p3)
{
    // il costruttore conrolla in anticipo se i punti sono collineari e li dispone già in senso antiorario
    if(!Collinear(_p1, _p2, _p3))
    {
        if(isCounter(_p1,_p2,_p3))
        {
            p1=_p1; p2=_p2; p3=_p3;
        }
        else
        {
            p1=_p1; p2=_p3; p3=_p2;
        }
    }
    angles[0] = acos((p2-p1)*(p3-p1)/(norm(p2-p1)*norm(p3-p1)));
    angles[1] = acos((p3-p2)*(p3-p1)/(norm(p1-p2)*norm(p3-p1)));
    angles[2] = acos((p1-p3)*(p3-p1)/(norm(p2-p3)*norm(p3-p1)));
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

bool Triangle::IsInTheTriangle(const Point& d)
{
    return (isCounter(p1, p2, d) && isCounter(p2, p3, d) && isCounter(p3, p1, d));
}

vector<Triangle> Triangle::Connect(const Point& d)
{
    vector<Triangle> newTriangles;
    Triangle t1(p1, p2, d);
    Triangle t2(p2, p3, d);
    Triangle t3(p3, p1, d);

    t1.adjacent[0] = &t2;
    t1.adjacent[1] = &t3;
    t1.adjacent[2] = adjacent[2];

    t2.adjacent[0] = &t3;
    t2.adjacent[1] = &t1;
    t2.adjacent[2] = adjacent[0];

    t3.adjacent[0] = &t1;
    t3.adjacent[1] = &t2;
    t3.adjacent[2] = adjacent[1];

    newTriangles.push_back(t1);
    newTriangles.push_back(t2);
    newTriangles.push_back(t3);
    return newTriangles;
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
    triangles.push_back(Triangle(p1,p2,p3));

    for (const Point& p : points)
    {
        for (Triangle& t : triangles)
        {
            if (t.IsInTheCircle(p))
                if (t.IsInTheTriangle(p))
                {
                    vector<Triangle> newTriangles = t.Connect(p);
                    triangles.erase(find(triangles.begin(), triangles.end(), t));

                    for(const Triangle& t: newTriangles)
                    {
                        
                    }
                    triangles.push_back(newTriangles[0]);
                    triangles.push_back(newTriangles[1]);
                    triangles.push_back(newTriangles[2]);
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

    for(const Triangle& t : triangles)
    {
        cout << "(" << t.p1.x << ", " << t.p1.y << ") "
             << "(" << t.p2.x << ", " << t.p2.y << ") "
             << "(" << t.p3.x << ", " << t.p3.y << ")" << endl;
    }
}

/*
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
    return points;
}
*/

} // namespace ProjectLibrary


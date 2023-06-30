#ifndef __DELAUNATOR_HPP
#define __DELAUNATOR_HPP

#include <iostream>
#include <cmath>
#include "Eigen/Eigen"

using namespace std;

namespace ProjectLibrary {

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
};
/*
// controlla se i punti sono collineari
bool Collinear(const Point& p1, const Point& p2, const Point& p3, const double &tol = 1e-5);
*/
// controlla se i punti sono ordinati in senso antiorario
bool isCounter(const Point& p1, const Point& p2, const Point& p3);

struct Triangle
{
    Triangle() = default;
    Triangle(const int& id, const Point& p1, const Point& p2, const Point& p3);

    int id;
    Point p1, p2, p3;
    array<double,3> angles;
    array<int,3> adjacentIds = {-1, -1 , -1};

    bool IsInTheCircle(const Point& d) const;
    bool IsInTheTriangle(const Point& d) const;
    unsigned int FindAdjacent(const int& id) const;

    friend ostream& operator << (ostream& os, const Triangle& t)
    {
        os << "Id: " << t.id
           << ". P1 = (" << t.p1.x << ", " << t.p1.y << ")"
           << ", P2 = (" << t.p2.x << ", " << t.p2.y << ")"
           << ", P3 = (" << t.p3.x << ", " << t.p3.y << ").";
        return os;
    }
    friend class Triangulation;

};

class Triangulation
{
private:
    vector<Triangle> triangles;

public:
    Triangulation() = default;
    Triangulation(const vector<Triangle>& triangles): triangles(triangles) {}

    list<int> Connect(const int& id, const Point& d);
    void Flip(const int& FirstId, const unsigned int& i ,const int& SecondId, const unsigned int& j);
    void Verify(list<int>& ids);
    vector<Triangle> Delaunator(vector<Point>& points);

    friend ostream& operator << (ostream& os, const Triangulation& tt)
    {
        for (const Triangle& t : tt.triangles)
            os << t << endl;
        return os;
    }
};
}

#endif // __DELAUNATOR_HPP


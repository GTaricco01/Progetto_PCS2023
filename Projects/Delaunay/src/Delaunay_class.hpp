#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include <cmath>
#include "Eigen\Eigen"

using namespace std;

namespace ProjectLibrary
{


struct Point
{
    double x, y;
    //Point()=default;
    Point(double x = 0, double y = 0) : x(x), y(y){}

};

// override operatori di DIFFERENZA e PRODOTTO SCALARE e PRODOTTO ESTERNO tra oggetti Point
inline Point operator - (const Point& p1, const Point& p2)
{
    return Point(p1.x-p2.x,p1.y-p2.y);
}

inline double operator * (const Point& p1, const Point& p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}

inline double prod(const Point& p1, const Point& p2)
{
    return p1.x*p2.y - p2.x*p1.y;
}

inline bool operator == (const Point& p1, const Point& p2)
{
    return (p1.x==p2.x && p1.y==p2.y);
}

// creazione funzione inline NORMA per oggetto Point
inline double norm(const Point& p)
{
    return sqrt(p.x*p.x + p.y*p.y);
}


// controlla se i punti sono collineari
bool Collinear(const Point& p1, const Point& p2, const Point& p3, const double &tol = 1e-5);

bool isCounter(const Point& p1, const Point& p2, const Point& p3);


class Triangle
{
private:
    int id;
    Point p1, p2, p3;
    array<double,3> angles;

public:

    array<int,3> adjacentIds = {-1, -1 , -1};

    Triangle() = default;
    Triangle(const int& id, const Point& p1, const Point& p2, const Point& p3);

    bool IsInTheCircle(const Point& d);
    bool IsInTheTriangle(const Point& d);
    unsigned int FindAdjacent(const int& id);

    friend ostream& operator << (ostream& os, const Triangle& t)
    {
        os << "Id: " << t.id
           << " (" << t.p1.x << ", " << t.p1.y << ")"
           << " (" << t.p2.x << ", " << t.p2.y << ")"
           << " (" << t.p3.x << ", " << t.p3.y << ")";
        return os;
    }
    friend bool operator == (const Triangle& t1, const Triangle& t2);
    friend class Triangulation;

};




inline bool operator == (const Triangle& t1, const Triangle& t2)
{
    return t1.p1 == t2.p1 && t1.p2 == t2.p2 && t1.p3 == t2.p3;
}


inline bool operator == (const vector<Triangle>& t1, const vector<Triangle>& t2)
{
    return t1[0] == t2[0] && t1[1] == t2[1] && t1[2] == t2[2];
}


class Triangulation
{
private:
    vector<Triangle> triangles;

public:
    Triangulation() = default;
    Triangulation(const vector<Triangle>& triangles): triangles(triangles) {}

    vector<Triangle> Delaunator(vector<Point> &points);

    bool TrianglesShareEdge(const Triangle& t1, const Triangle& t2, array<Point,2>& point);
    list<int> Connect(const int& id, const Point& d);
    void Verify(list<int>& ids);
    void Flip(const int& FirstId, const unsigned int& i ,const int& SecondId, const unsigned int& j);

    friend ostream& operator << (ostream& os, const Triangulation& tt)
    {
        for (const Triangle& t : tt.triangles)
            os << t << endl;
        return os;
    }
};



}
#endif // __EMPTY_H


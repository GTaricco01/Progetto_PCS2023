#ifndef __DELAUNATOR_CLASS_H
#define __DELAUNATOR_CLASS_H

#include <iostream>
#include <cmath>
#include "Eigen/Eigen"

using namespace std;

namespace ProjectLibrary
{
struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
};


// override operatori di differenza fra oggetti Point
inline Point operator - (const Point& p1, const Point& p2)
{
    return Point(p1.x-p2.x,p1.y-p2.y);
}

// operatore prodotto scalare tra punti
inline double operator * (const Point& p1, const Point& p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}

// operatore prodotto esterno
inline double prod(const Point& p1, const Point& p2)
{
    return p1.x*p2.y - p2.x*p1.y;
}

// operatore uguaglianza tra oggetti Point
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
// controlla se i punti sono ordinati in senso antiorario
bool isCounter(const Point& p1, const Point& p2, const Point& p3);
// controlla se nel vettore di input sono presenti ripetizioni
vector<Point> Repetitions(vector<Point>& p);

struct Triangle
{
    Triangle() = default;
    Triangle(const int& id, const Point& p1, const Point& p2, const Point& p3);

    int id;
    Point p1, p2, p3;
    array<double,3> angles;
    array<int,3> adjacentIds = {-1, -1 , -1};

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
    vector<Triangle> Delaunator(vector<Point> &points);

    friend ostream& operator << (ostream& os, const Triangulation& tt)
    {
        for (const Triangle& t : tt.triangles)
            os << t << endl;
        return os;
    }
};

}
#endif // __DELAUNATOR_CLASS_H


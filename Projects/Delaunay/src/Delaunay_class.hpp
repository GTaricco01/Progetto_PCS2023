#ifndef __EMPTY_H
#define __EMPTY_H

#include "iostream"
#include <cmath>
#include <fstream>
#include "Eigen/Eigen"

using namespace std;

namespace ProjectLibrary
{


struct Point
{
    double x, y;
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
bool Collinear(const Point& p1, const Point& p2, const Point& p3);

bool isCounter(const Point& p1, const Point& p2, const Point& p3);

bool isCounter(const vector<Point> points);



class Triangle
{
private:
    int id;
    Point p1, p2, p3;
    array<double,3> angles;
    array<int,3> adjacentIds = {-1, -1 , -1};

public:
    Triangle() = default;
    Triangle(const int& id, const Point& _p1, const Point& _p2, const Point& _p3);

    // calcola il circocentro
    bool IsInTheCircle(const Point& d);
    bool IsInTheTriangle(const Point& d);
    bool Verify();

    vector<Triangle> Connect(const Point& d);
    vector<Triangle> Flip(const unsigned int& i, const unsigned int& j);

    //friend ostream& operator << (ostream& os, const Triangle& t);
    friend bool operator == (const Triangle& t1, const Triangle& t2);
    friend class Triangulation;
    
};

/*
ostream& operator << (ostream& os, const Triangle& t)
{
    os << "(" << t.p1.x << ", " << t.p1.y << ")";
    return os;
}
*/

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
    //void Delaunay(vector<Point> &points);
    //friend ostream& operator << (ostream& os, const Triangulation& tt);
    vector<Triangle> Delaunay(vector<Point> &points);
    bool TrianglesShareEdge(Triangle& t1, Triangle& t2, array<Point,2>& point);

};

/*
ostream& operator << (ostream& os, const Triangulation& tt)
{
    for (const Triangle& t : tt.triangles)
        os<<t<<endl;
    return os;
}
*/

//classe Reader: legge da file di input e crea vettore in cui sono memorizzati gli oggetti Point
class Reader
{
private:
    string input;
    string line;
    ifstream file;
    vector<Point> points;
public:
    Reader() = default;
    vector<Point> MakeVector(const string& input);
};


}
#endif // __EMPTY_H


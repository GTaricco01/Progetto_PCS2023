#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "map"

using namespace std;

namespace ProjectLibrary
{


struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
    /*{
        cout << "Coordinates are: (" << x << ", " << y << ")" << endl;
    }*/

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

struct Lato
{
    Point p1, p2, lato;
    Lato(Point& p1, Point& p2) : p1(p1), p2(p2), lato(p2-p1){}

};

// controlla se i punti sono collineari
bool Collineari(const Point& p1, const Point& p2, const Point& p3, double tol = 1e-5);


bool isCounter(const vector<Point> points);



struct Triangle
{
    Point p1,p2,p3;
    Triangle() = default;
    Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3){}

    // calcola il circocentro
    Point CircoCentro();

    // controlla se un nuovo punto q è nel circocerchio del triangolo
    bool IsInTheCircle(const Point& d);

    // controllo counterclockwise
    bool isCounterClockWise();

    vector<Triangle> Connect(const Point& d);

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
    map<unsigned int, Triangle> triangles;

    void Flip(Triangle& t1, Triangle& t2);
    void RemoveInvalid();

public:
    map<unsigned int, Triangle> Delaunay(map<unsigned int, Point>& points);

};



// classe Reader: legge da file di input e crea vettore in cui sono memorizzati gli oggetti Point
class Reader
{
private:
    string input;
    string line;
    ifstream file;
    map<unsigned int,Point> points;
public:
    Reader() = default;
    map<unsigned int, Point> MakeVector(const string& input);
};

}
#endif // __EMPTY_H

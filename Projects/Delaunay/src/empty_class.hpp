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

struct Lato
{
    Point p1, p2, lato;
    Lato(Point& p1, Point& p2) : p1(p1), p2(p2), lato(p2-p1){}

};

// controlla se i punti sono collineari
bool Collineari(const Point& p1, const Point& p2, const Point& p3, double tol = 1e-5);


bool isCounter(const vector<Point> points);


// creazione funzione inline NORMA per oggetto Point
inline double norm(const Point& p)
{
    return sqrt(p.x*p.x + p.y*p.y);
}


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


class Triangle
{
protected:
    Point p1,p2,p3;

public:
    Triangle() = default;
    Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3){}

    // calcola il circocentro
    Point CircoCentro();

    // controlla se un nuovo punto q è nel circocerchio del triangolo
    bool IsInTheCircle(const Point& d);

    // controllo counterclockwise
    bool isCounterClockWise();

};

class Triangulation
{
private:
    map<unsigned int, Triangle> triangles;



public:
    map<unsigned int, Triangle> Delaunay(map<unsigned int, Point>& points);
    void Connect(unsigned int& index, Triangle& t, Point& d);
    void Flip(Triangle& t1, Triangle& t2);

    friend class Triangle;
};

}
#endif // __EMPTY_H

#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
<<<<<<< HEAD
#include <cmath>
=======
#include <fstream>
#include <sstream>
>>>>>>> 88fa5606a08a3dfe82ee3fb1984b1ab9efa50c80

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
    bool isCounter(const vector<Point> points);

};

// override operatori di somma e differenza tra oggetti Point
inline Point operator - (const Point& p1, const Point& p2)
{
    return Point(p1.x-p2.x,p1.y-p2.y);
}
inline double operator * (const Point& p1, const Point& p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}

// creazione funzione inline NORMA per oggetto Point
inline double norm(const Point& p)
{
    return sqrt(p.x*p.x + p.y*p.y);
}
/*
// classe Reader: legge da file di input e crea vettore in cui sono memorizzati gli oggetti Point
class Reader
{
private:
    string input;
    string line;
    ifstream file;
    vector<Point> points;
public:
    Reader() = default;
    vector<Point> MakeVector();
};
*/

class Triangle
{
public:
    Point p1,p2,p3;

public:
    Triangle(Point& p1, Point& p2, Point& p3) : p1(p1), p2(p2), p3(p3){}

    // controlla se i punti sono collineari
    bool Collineari(double tol = 1e-12);

    // calcola il circocentro
    Point CircoCentro();

    // controlla se un nuovo punto q è nel circocerchio del triangolo
    bool IsInTheCircle(const Point& d);

    // controllo counterclockwise
    bool isCounterClockWise(Triangle t);

};


}
#endif // __EMPTY_H

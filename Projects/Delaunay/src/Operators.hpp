#ifndef __OPERATORS_HPP
#define __OPERATORS_HPP

#include "Delaunator.hpp"

namespace ProjectLibrary {
// override operatore di differenza fra oggetti Point
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

// operatore uguaglianza tra oggetti Triangle
inline bool operator == (const Triangle& t1, const Triangle& t2)
{
    return (
        (t1.p1 == t2.p1 && t1.p2 == t2.p2 && t1.p3 == t2.p3) ||
        (t1.p1 == t2.p1 && t1.p2 == t2.p3 && t1.p3 == t2.p2) ||
        (t1.p1 == t2.p2 && t1.p2 == t2.p1 && t1.p3 == t2.p3) ||
        (t1.p1 == t2.p2 && t1.p2 == t2.p3 && t1.p3 == t2.p1) ||
        (t1.p1 == t2.p3 && t1.p2 == t2.p1 && t1.p3 == t2.p2) ||
        (t1.p1 == t2.p3 && t1.p2 == t2.p2 && t1.p3 == t2.p1));
}
// creazione funzione inline NORMA per oggetto Point
inline double norm(const Point& p)
{
    return sqrt(p.x*p.x + p.y*p.y);
}

// operatore di uguaglianza tra vettori di oggetti Point
inline bool operator == (const vector<Point>& vec_p1, const vector<Point>& vec_p2)
{
    unsigned int n = vec_p1.size(); // se n = 0 considero gli oggetti uguali
    bool equal = true;

    for (unsigned int i = 0; i < n; i++)
    {
        if (!(vec_p1[i] == vec_p2[i]))
        {
            equal = false;
            break;
        }
    }
    return equal;
}

// operatore di uguaglianza vettori di triangoli

inline bool operator == (const vector<Triangle>& vec_t1, const vector<Triangle>& vec_t2)
{
    unsigned int n = vec_t1.size(); // se n = 0 considero gli oggetti uguali
    bool equal = true;

    for (unsigned int i = 0; i < n; i++)
    {
        if (!(vec_t1[i] == vec_t2[i]))
        {
            equal = false;
            break;
        }
    }
    return equal;
}



}
#endif // __OPERATORS_HPP

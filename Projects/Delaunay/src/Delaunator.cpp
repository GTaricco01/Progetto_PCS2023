#include <iostream>
#include <cmath>
#include "Eigen/Eigen"
#include "Delaunator.hpp"
#include "Operators.hpp"

using namespace Eigen;
using namespace ProjectLibrary;

namespace ProjectLibrary
{
//funzioni cotrollo punti: isCounter
bool isCounter(const Point& p1, const Point& p2, const Point& p3)
{
    double s;
    s = prod(p2-p1, p3-p1);
    return (s >= 0);
}

vector<Point> Repetitions(vector<Point>& vecp)
{
    for (unsigned int i = 0; i < vecp.size(); i++)
    {
        for (unsigned int j = 0; j < vecp.size(); j++)
        {
            if (j != i)
            {
                if (vecp[j] == vecp[i])
                {
                    vecp.erase(vecp.begin()+j);
                }
            }
        }
    }
    return vecp;
}

//metodi Triangle: Costruttore IsInTheCircle IsIntTheTriangle
Triangle::Triangle(const int& id, const Point& p1, const Point& p2, const Point& p3):
    id(id), p1(p1), p2(p2), p3(p3)
{
    // se c'è un punto che cade su un lato, il metodo Flip() legge l'angolo di 180° e lo flippa in automatico
    angles[0] = acos((p2-p1)*(p3-p1)/(norm(p2-p1)*norm(p3-p1)));
    angles[1] = acos((p3-p2)*(p1-p2)/(norm(p3-p2)*norm(p1-p2)));
    angles[2] = acos((p1-p3)*(p2-p3)/(norm(p1-p3)*norm(p2-p3)));
}

//controllo che il punto d sia nel circocerchio
bool Triangle::IsInTheCircle(const Point& d)
{
    Matrix<double, 3, 3> mat;
    mat << p1.x-d.x, p1.y-d.y, (p1.x-d.x)*(p1.x-d.x) + (p1.y-d.y)*(p1.y-d.y),
        p2.x-d.x, p2.y-d.y, (p2.x-d.x)*(p2.x-d.x) + (p2.y-d.y)*(p2.y-d.y),
        p3.x-d.x, p3.y-d.y, (p3.x-d.x)*(p3.x-d.x) + (p3.y-d.y)*(p3.y-d.y);

    return (mat.determinant() > 0);
}

//controllo che il punto d sia nel triangolo
bool Triangle::IsInTheTriangle(const Point& d)
{
    return (isCounter(p1, p2, d) && isCounter(p2, p3, d) && isCounter(p3, p1, d));
}

//ritorna l'indice del lato adiacente al triangolo id, in caso non lo trova (non dovrebbe succedere nel nostro codice) ritorna 3
unsigned int Triangle::FindAdjacent(const int& id)
{
    unsigned int j=0;
    while (j<3)
    {
        if (adjacentIds[j] == id)
            return j;
        j++;
    }
    return 3;

}

//metodi Triangulation: Connect, Verify, Flip

//connette il punto d ai vertici del triangolo che lo contiene
list<int> Triangulation::Connect(const int& id, const Point& d)
{
    Triangle t = triangles[id];
    Triangle t1(id, t.p1, t.p2, d);
    Triangle t2(triangles.size(), t.p2, t.p3, d);
    Triangle t3(triangles.size()+1, t.p3, t.p1, d);

    t1.adjacentIds[0] = t2.id;
    t1.adjacentIds[1] = t3.id;
    t1.adjacentIds[2] = t.adjacentIds[2];
    //qui l'id è già giusto
    //triangles[t.adjacentIds[2]].adjacentIds[triangles[t.adjacentIds[2]].FindAdjacent(id)]=id;

    t2.adjacentIds[0] = t3.id;
    t2.adjacentIds[1] = t1.id;
    t2.adjacentIds[2] = t.adjacentIds[0];
    triangles[t.adjacentIds[0]].adjacentIds[triangles[t.adjacentIds[0]].FindAdjacent(id)]=t2.id;

    t3.adjacentIds[0] = t1.id;
    t3.adjacentIds[1] = t2.id;
    t3.adjacentIds[2] = t.adjacentIds[1];
    triangles[t.adjacentIds[1]].adjacentIds[triangles[t.adjacentIds[1]].FindAdjacent(id)]=t3.id;

    triangles[id] = t1;
    triangles.push_back(t2);
    triangles.push_back(t3);

    list<int> Ids = {id, t2.id, t3.id};
    return Ids;
}

// Verify controlla che sia verificata l'ipotesi di delaunay, ovvero che due triangoli adiacenti abbiano una somma minore di 180°
// nel caso contrario Verify chiama il metodo flip.
// Verify sfrutta una lista di Id dei triangoli, ogni volta che un triangolo supera il controllo viene eliminato dalla lista
// se un due triangoli vengono fliappati, viene ripetuto il controllo sul triangolo corrente e viene aggiunto
// alla lista l'id del triangolo adiacente
void Triangulation::Verify(list<int>& ids)
{
    while (!ids.empty())
    {
        int id = ids.front();
        Triangle t = triangles[id];
        for (unsigned int i=0; i<3; i++)
        {
            if (t.adjacentIds[i] != -1)
            {
                Triangle tAd = triangles[t.adjacentIds[i]];
                unsigned int j = tAd.FindAdjacent(id);

                if(t.angles[i]+tAd.angles[j] > M_PI)
                {
                    Flip(t.id, i, tAd.id, j);
                    //ids.push_back(id);
                    ids.push_back(tAd.id);
                    //ids.pop_front();
                    break;
                }
            }
        }
        ids.pop_front();
    }
}


//Flip effettua lo scambio l'operazione di flip tra i triangoli FirstId e SecondId lungo i lato adiacente, che si trova in
//posizione i in FirstId e in posizione j in SecondId
void Triangulation::Flip(const int& FirstId, const unsigned int& i ,const int& SecondId, const unsigned int& j)
{
    Triangle t = triangles[FirstId];
    Triangle tAd = triangles[SecondId];
    vector<Point> t_points = {t.p1, t.p2, t.p3};
    vector<Point> tAd_points = {tAd.p1, tAd.p2, tAd.p3};

    Triangle t1(FirstId, t_points[i], t_points[(i+1)%3], tAd_points[j]);
    Triangle t2(SecondId, t_points[i], tAd_points[j], t_points[(i+2)%3]);

    t1.adjacentIds[0] = tAd.adjacentIds[(j+1)%3];
    t1.adjacentIds[1] = SecondId;
    t1.adjacentIds[2] = t.adjacentIds[(i+2)%3];
    triangles[FirstId] = t1;
    //aggiorna il triangolo adiacente sul primo lato
    //Triangle& tNear1 = triangles[t1.adjacentIds[0]];
    //tNear1.adjacentIds[tNear1.FindAdjacent(SecondId)]=FirstId;
    triangles[t1.adjacentIds[0]].adjacentIds[triangles[t1.adjacentIds[0]].FindAdjacent(SecondId)]=FirstId;

    t2.adjacentIds[0] = tAd.adjacentIds[(j+2)%3];
    t2.adjacentIds[1] = t.adjacentIds[(i+1)%3];
    t2.adjacentIds[2] = FirstId;
    triangles[SecondId] = t2;
    //aggiorna il triangolo adiacente al secondo lato
    //Triangle& tNear2 = triangles[t2.adjacentIds[1]];
    //tNear2.adjacentIds[tNear2.FindAdjacent(FirstId)]=SecondId;
    triangles[t2.adjacentIds[1]].adjacentIds[triangles[t2.adjacentIds[1]].FindAdjacent(FirstId)]=SecondId;
}



vector<Triangle> Triangulation::Delaunator(vector<Point>& points) // delaunator
{
    vector<Point> points_norep = Repetitions(points);
    unsigned int n = points.size();
    triangles.reserve(2*n); //allocazione preventiv di memoria

    // define super triangle
    double minX, minY, maxX, maxY;
    minX = points_norep[0].x;
    minY = points_norep[0].y;
    maxX = minX;
    maxY = minY;

    for (unsigned int i = 1; i < n; i++)
    {
        minX = min(minX, points_norep[i].x);
        minY = min(minY, points_norep[i].y);
        maxX = max(maxX, points_norep[i].x);
        maxY = max(maxY, points_norep[i].y);
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
    triangles.push_back(Triangle(0, p1, p2, p3));
    list<int> newIds;

    for (const Point& p : points_norep)
    {
        int n = triangles.size();
        for (int id = 0; id < n; id++)
        {
            Triangle t = triangles[id];
            if (t.IsInTheCircle(p))
            {
                if (t.IsInTheTriangle(p))
                {
                    newIds = Connect(id, p);
                    Verify(newIds); // qui viene chiamata la funzione di Flip()
                    break;
                }
            }
        }

    }

    //rimozione super triangle iniziale
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

    return triangles;
}


}

#include "Delaunator_class.hpp"
#include <iostream>
#include <cmath>
#include "Eigen/Eigen"
#include <vector>

using namespace Eigen;
using namespace ProjectLibrary;

namespace ProjectLibrary
{

//funzioni su punti: Collinear IsCounter
bool Collinear(const Point &p1, const Point &p2, const Point &p3, const double& tol)
{
    // sono collineari se l'area del triangolo è minore della tolleranza
    double s;
    s = prod(p2-p1, p3-p1);

    return (abs(s) <= tol);
}

bool isCounter(const Point& p1, const Point& p2, const Point& p3)
{
    double s;
    s = prod(p2-p1, p3-p1);
    return (s >= 0);
}

bool Repetitions(vector<Point>& vecp)
{
    unsigned int f = 0;
    for (unsigned int i = 1; i < vecp.size(); i++)
    {
        for (unsigned int j = 0; j < vecp.size(); j++)
        {
            if (j != i)
            {
                vecp.erase(remove_if(vecp.begin(), vecp.end(),
                                     [&] (const vector<Point>& vecp)
                                     {
                                         return vecp[i] == vecp[j];
                           }),
                           vecp.end());
                f++;
            }
        }
    }
    return f > 0; // vero se f > 0 <=> vero se ci sono ripetizioni
}

//metodi Triangle: Costruttore IsInTheCircle IsIntTheTriangle
Triangle::Triangle(const int& id, const Point& p1, const Point& p2, const Point& p3):
    id(id), p1(p1), p2(p2), p3(p3)
{
    // se c'è un punto che cade su un lato, il metodo Flip() legge l'angolo di 180° e lo flippa in automatico
    // il costruttore controlla in anticipo se i punti sono collineari e li dispone già in senso antiorario
    angles[0] = acos((p2-p1)*(p3-p1)/(norm(p2-p1)*norm(p3-p1)));
    angles[1] = acos((p3-p2)*(p1-p2)/(norm(p3-p2)*norm(p1-p2)));
    angles[2] = acos((p1-p3)*(p2-p3)/(norm(p1-p3)*norm(p2-p3)));
}

bool Triangle::IsInTheCircle(const Point& d)
{
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

unsigned int Triangle::FindAdjacent(const int& id)
{
    unsigned int j=0;
    while (j<3)
    {
        if (adjacentIds[j] == id)
            return j;
        j++;
    }
    return 1000;

}

//metodi Triangulation: Connect, Verify, Flip

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

    list<int> Ids;
    Ids.push_back(id);
    Ids.push_back(t2.id);
    Ids.push_back(t3.id);
    return Ids;
}

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
                    ids.push_back(id);
                    ids.push_back(tAd.id);
                    ids.pop_front();
                    break;
                }
            }
        }
        ids.pop_front();
    }
}



void Triangulation::Flip(const int& FirstId, const unsigned int& i ,const int& SecondId, const unsigned int& j)
{
    Triangle t = triangles[FirstId];
    Triangle tAd = triangles[SecondId];
    vector<Point> t_points = {t.p1, t.p2, t.p3};
    vector<Point> tAd_points = {tAd.p1, tAd.p2, tAd.p3};

    Triangle t1(FirstId, t_points[i], t_points[(i+1)%3], tAd_points[j]);
    Triangle t2(SecondId, t_points[i], tAd_points[j], t_points[(i+2)%3]);

    //vedere le adiacenze
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

    /*
    for (const Triangle& t : triangles)
    {
        cout << "(" << t.p1.x << ", " << t.p1.y << ") "
             << "(" << t.p2.x << ", " << t.p2.y << ") "
             << "(" << t.p3.x << ", " << t.p3.y << ")" << endl;
        cout << "Adiacenze: " << t.adjacentIds[0] << "  " << t.adjacentIds[1] << "  " << t.adjacentIds[2] << endl;
    }*/
}



vector<Triangle> Triangulation::Delaunator(vector<Point>& points) // delaunator
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
    triangles.push_back(Triangle(0, p1, p2, p3));

    for (const Point& p : points)
    {
        int n = triangles.size();
        for (int id = 0; id < n; id++)
        {
            Triangle t = triangles[id];
            if (t.IsInTheCircle(p))
            {
                if (t.IsInTheTriangle(p))
                {
                    list<int> newIds = Connect(id, p);
                    Verify(newIds); // qui viene chiamata la funzione di Flip()
                    break;
                }
            }
        }
        // cout<<"Il punto p= ("<<p.x<<","<<p.y<<") e' stato aggiunto con successo alla triangolazione"<<endl;

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


} // namespace ProjectLibrary


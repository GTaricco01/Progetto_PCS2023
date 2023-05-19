#include "empty_class.hpp"
#include <iostream>
#include <numeric>
#include <sstream>
#include <fstream>
#include "Eigen/Eigen"
#include <cmath>

using namespace std;
using namespace ProjectLibrary;
using namespace Eigen;

int main()
{
    string data1 = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/Test1.csv";
    string data2 = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/Test2.csv";
    string prova = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/prova_punti.txt";
    string line;
    ifstream file;
    vector<Point> points;

    file.open(prova);
    getline(file,line);

    while (!file.eof())
    {
        unsigned int id;
        double x,y;

        getline(file,line);
        istringstream convert(line);

        convert >> id >> x >> y;
        points.push_back(Point(x,y));
    }

    for (Point p : points)
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    cout << endl;


    Point p1,p2,p3,d;
    p1 = Point(0,1);
    p2 = Point(2,5);
    p3 = Point(-1,5);
    d = Point(1,0);

    Triangle t = Triangle(p1,p2,p3);
    Point cc = t.CircoCentro();
    cout << "(" << cc.x << ", " << cc.y << ")" << endl;


    if (t.isCounterClockWise(t))
    {

        if (t.IsInTheCircle(d))
            cout << "(" << d.x << ", " << d.y << ") is inside the circumcircle." << endl;
        else
            cout << "(" << d.x << ", " << d.y << ") is NOT inside the circumcircle." << endl;
    }














    return 0;
}

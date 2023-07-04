#include <iostream>
#include "Eigen/Eigen"

#include "Delaunator.hpp"
#include "Reader.hpp"
using namespace std;
using namespace ProjectLibrary;

int main() {
    Reader r;
    try
    {
        vector<Point> points1 = r.MakeVector("/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/Test1.csv");
        Triangulation t1;
        t1.Delaunator(points1);
        cout << t1;

        vector<Point> points2 = r.MakeVector("/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/Test2.csv");
        Triangulation t2;
        t2.Delaunator(points2);
        cout << t2;
    }
    catch(invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}

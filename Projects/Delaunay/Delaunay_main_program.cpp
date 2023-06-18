#include <iostream>
#include <vector>
#include "Eigen/Eigen"
#include "Delaunator.hpp"
#include "Reader.hpp"
using namespace std;
using namespace ProjectLibrary;

int main() {
    /*
    vector<Point> points = {
        {1., 1.},
        {1., 3.},
        {-1., 2.},
        {4., 1.},
        {3., 3.},
        {4., 3.}
    };

    Triangle t0(0, points[0], points[1], points[2]);
    t0.adjacentIds = {-1, -1, 1};
    Triangle t1(1, points[0], points[3], points[1]);
    t1.adjacentIds = {2, 0, -1};
    Triangle t2(2, points[1], points[3], points[4]);
    t2.adjacentIds = {3 ,-1, 1};
    Triangle t3(3, points[4], points[3], points[5]);
    t3.adjacentIds = {-1 ,-1, 2};

    vector<Triangle> triangles = {t0, t1, t2, t3};
    Triangulation test_flip(triangles);
    test_flip.Flip(1, 0, 2, 2);
    */

    /*vector<Point> points1 = {
        {1, 1},
        {2, 3},
        {4, 2},
        {3, 5},
        {6, 4}
    };
    Triangulation t1;
    t1.Delaunator(points1);
    cout<<t1;*/

    /*
    vector<Point> points2 = {
        {1., 1.},
        {1., 3.},
        {-1., 2.},
        {4., 1.},
        {3., 3.},
        {4., 3.}
    };
    Triangulation t2;
    t2.Delaunator(points2);
    cout<<t2;
    */


    Reader r;
    vector<Point> points = r.MakeVector("/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/prova_punti.txt");
    Triangulation t;
    t.Delaunator(points);
    cout<<t;

    /*
    Point p1 = Point(0,0);
    Point p2 = Point(1.5,0);
    Point p3 = Point(2,1);
    Point p4 = Point(1,1.5);
    vector<Triangle> triangles;
    vector<Triangle> triangles_flipped;
    Triangulation tt;
    triangles.push_back(Triangle(0,p1,p2,p3));
    triangles.push_back(Triangle(1,p1,p3,p4));
    triangles_flipped.push_back(Triangle(0,p1,p2,p4));
    triangles_flipped.push_back(Triangle(1,p2,p3,p4));

    tt.Flip(triangles[0].adjacentIds[0],)*/

    return 0;

}


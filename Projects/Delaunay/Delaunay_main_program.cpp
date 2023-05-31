#include "Delaunay_class.hpp"
#include <iostream>
#include <numeric>
#include <sstream>
#include <fstream>
#include "Eigen/Eigen"
#include <cmath>

using namespace std;
using namespace ProjectLibrary;
using namespace Eigen;

int main() {

    vector<Point> points = {
        {1, 1},
        {2, 3},
        {4, 2},
        {3, 5},
        {6, 4}
    };
    Triangulation t;
    t.Delaunay(points);

    Triangle triangle1 = { { 1.0, 1.0 }, { 2.0, 3.0 }, { 4.0, 2.0 } };
    Triangle triangle2 = { { 2.0, 3.0 }, { 4.0, 2.0 }, { 3.0, 5.0 } };
    Triangulation tt;
    if (tt.TrianglesShareEdge(triangle1, triangle2)) {
        // Flip the triangles
        tt.Flip(triangle1, triangle2);

        // Print the flipped triangles
        std::cout << "Flipped triangle 1: (" << triangle1.p1.x << ", " << triangle1.p1.y << "), "
                  << "(" << triangle1.p2.x << ", " << triangle1.p2.y << "), "
                  << "(" << triangle1.p3.x << ", " << triangle1.p3.y << ")\n";

        std::cout << "Flipped triangle 2: (" << triangle2.p1.x << ", " << triangle2.p1.y << "), "
                  << "(" << triangle2.p2.x << ", " << triangle2.p2.y << "), "
                  << "(" << triangle2.p3.x << ", " << triangle2.p3.y << ")\n";
    } else {
        std::cout << "Triangles do not share an edge. Cannot perform edge flip.\n";
    }

    return 0;
}

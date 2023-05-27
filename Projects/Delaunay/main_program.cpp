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

    return 0;
}

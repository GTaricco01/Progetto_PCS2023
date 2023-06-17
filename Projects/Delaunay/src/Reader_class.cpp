#include "Reader_class.hpp"
#include <complex>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Eigen/Eigen"

using namespace ProjectLibrary;

vector<Point> Reader::MakeVector(const string& input)
{
    file.open(input);
    getline(file,line);
    while (!file.eof())
    {
        double id, x, y;
        getline(file,line);
        istringstream cast(line);

        cast >> id >> x >> y;
        points.push_back(Point(x,y));
    }
    file.close();
    return points;
}

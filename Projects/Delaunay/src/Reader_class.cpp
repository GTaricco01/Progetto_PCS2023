#include "Reader_class.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
<<<<<<< HEAD
#include <cmath>
#include "Eigen/Eigen"
=======
using namespace ProjectLibrary;
>>>>>>> 6081afd0d2a8dd76b6a215b0b3df236d53a2efc7

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

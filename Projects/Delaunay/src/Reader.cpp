#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Eigen/Eigen"

#include "Delaunator.hpp"
#include "Operators.hpp"
#include "Reader.hpp"

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

vector<Point> Reader::cutRepetitions()
{
    for (unsigned int i = 0; i < points.size(); i++)
    {
        for (unsigned int j = 0; j < points.size(); j++)
        {
            if (j != i)
            {
                if (points[j] == points[i])
                {
                    points.erase(points.begin()+j);
                }
            }
        }
    }
    return points;
}

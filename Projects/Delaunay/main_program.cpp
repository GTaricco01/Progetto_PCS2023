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
    string input1 = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/Test1.csv";
    string input2 = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/prova_punti.txt";
    string line;
    ifstream file;
    vector<Point> points;

    file.open(input2);
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








    return 0;
}

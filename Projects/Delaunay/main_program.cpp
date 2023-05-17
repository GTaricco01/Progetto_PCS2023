#include "empty_class.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include "Eigen/Eigen"
#include "map"
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
    map<unsigned int, Vector2d> points ={};

    file.open(input2);
    getline(file,line);

    while (!file.eof())
    {
        unsigned int id;
        double x,y;

        getline(file,line);
        istringstream convert(line);

        convert >> id >> x >> y;
    }


    Vector2d a1 = {0,1};
    Vector2d a2 = {1,2};
    cout << a1[1] << endl;


    return 0;
}

#ifndef READER_CLASS_HPP
#define READER_CLASS_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include "Eigen/Eigen"
#include "Delaunay_class.hpp"

using namespace std;
using namespace ProjectLibrary;
//classe Reader: legge da file di input e crea vettore in cui sono memorizzati gli oggetti Point
class Reader
{
private:
    string input;
    string line;
    ifstream file;
    vector<Point> points;
public:
    Reader() = default;
    vector<Point> MakeVector(const string& input);
};



#endif // READER_CLASS_HPP

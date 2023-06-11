#ifndef READER_CLASS_HPP
#define READER_CLASS_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include "Delaunay_class.hpp"
using namespace std;
using namespace ProjectLibrary;

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

#ifndef __READER_HPP
#define __READER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include "Delaunator.hpp"
using namespace std;
namespace ProjectLibrary {

class Reader
{
private:
    string input;
    string line;
    ifstream file;
    vector<Point> points;
public:
    Reader() = default;
    Reader(const vector<Point>& points): points(points){}

    vector<Point> MakeVector(const string& input);
    vector<Point> cutRepetitions(vector<Point>& points);
};
}

#endif // __READER_HPP

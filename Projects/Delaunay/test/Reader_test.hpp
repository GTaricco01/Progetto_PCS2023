#ifndef __READER_TEST_H
#define __READER_TEST_H

#include <gtest/gtest.h>
#include "Reader_class.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(ImportDati, MakeVector)
{
    string input = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/punti.csv";
    vector<Point> vec_exact = {
        {1,1},
        {2,3},
        {4,2},
        {3,5},
        {6,4}
    };
    Reader vec_try;

    EXPECT_EQ(vec_try.MakeVector(input), vec_exact);
}

TEST(ImportDati, Repetitions)
{
    vector<Point> vec_rep = {
        {0,0},
        {0,1},
        {0,1}
    };
    vector<Point> vec_no_rep = {
        {0,0},
        {0,1}
    };

    EXPECT_EQ(Repetitions(vec_rep),vec_no_rep);
}

#endif // __READER_TEST_H

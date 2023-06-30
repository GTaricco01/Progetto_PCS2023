#ifndef __READER_TEST_H
#define __READER_TEST_H

#include <gtest/gtest.h>
#include "Reader.hpp"

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
    vector<Point> vvv;
    vvv = vec_try.MakeVector(input);
    EXPECT_EQ(vvv, vec_exact);
}

TEST(ImportDati, Repetitions)
{
    vector<Point> vec_rep = {
        {0,0},
        {0,1},
        {0,1}
    };
    Reader try_repetitions(vec_rep);

    vector<Point> vec_no_rep = {
        {0,0},
        {0,1}
    };

    EXPECT_EQ(try_repetitions.cutRepetitions(),vec_no_rep);
}

#endif // __READER_TEST_H

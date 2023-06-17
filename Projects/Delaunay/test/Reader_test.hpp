#ifndef __READER_TEST_H
#define __READER_TEST_H

#include <gtest/gtest.h>
#include "Reader_class.hpp"


TEST(ImportDati, MakeVector)
{
    string input = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/prova_punti.txt";
    vector<Point> vec_exact ={
        {1,0},
        {0,1},
        {2,5},
        {-1,5}
    };
    Reader vec_try;


    EXPECT_EQ(vec_exact, vec_try.MakeVector(input));
}

#endif // __READER_TEST_H

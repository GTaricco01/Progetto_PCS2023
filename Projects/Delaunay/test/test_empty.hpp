#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "empty_class.hpp"

using namespace testing;
using namespace ProjectLibrary;

//ordine anti-orario
TEST(MetodiTriangle, isCounterClockWise)
{
    Point p1 = Point(0.,0.);
    Point p2 = Point(2.,0.);
    Point p3 = Point(0.,2.);
    Triangle t = Triangle(p1, p2, p3);

    EXPECT_TRUE(t.isCounterClockWise());
}

// correttezza del circocentro
TEST(MetodiTriangle, CircoCentro)
{
    Point p1 = Point(0.,0.);
    Point p2 = Point(2.,0.);
    Point p3 = Point(0.,2.);
    Triangle t = Triangle(p1, p2, p3);
    Point expected_center = Point(1., 1.);

    EXPECT_EQ(expected_center, t.CircoCentro());
}

// correttezza formula che distingue un punto nel cerchio da un punto fuori
TEST(MetodiTriangle, IsInTheCircle)
{
    Point p1 = Point(0.,0.);
    Point p2 = Point(2.,0.);
    Point p3 = Point(0.,2.);
    Triangle t = Triangle(p1, p2, p3);
    Point expected_in = Point(1.,1.);
    Point expected_out = Point(0.,3.);

    EXPECT_TRUE(t.IsInTheCircle(expected_in));
    EXPECT_FALSE(t.IsInTheCircle(expected_out));
}

// test punti collineari
TEST(MetodiTriangle, Collineari)
{
    Point coll1 = Point(0.,0.);
    Point coll2 = Point(1.,1.);
    Point coll3 = Point(2.,2.);

    Point ncoll1 = Point(0.,0.);
    Point ncoll2 = Point(2.,0.);
    Point ncoll3 = Point(0.,2.);

    EXPECT_TRUE(Collineari(coll1, coll2, coll3));
    EXPECT_FALSE(Collineari(ncoll1, ncoll2, ncoll3));
}

TEST(MetodiTriangolazione, Connect)
{
    Point p1 = Point(1,2);
    Point p2 = Point(2,0);
    Point p3 = Point(3,2);
    Point d = Point(2,1);
    Triangle t = Triangle(p1, p2, p3);
    vector<Triangle> vecT = {Triangle(p1, p2, d),
                             Triangle(p2, p3, d),
                             Triangle(p3, p1, d)};

    EXPECT_EQ(vecT, t.Connect(d));
}

TEST(ImportDati, MakeVector)
{
    string input = "/Users/gabry/Desktop/Progetto_PCS/Projects/Delaunay/Dataset/prova_punti.txt";
    map<unsigned int, Point> vec_exact;
    vec_exact[0] = Point(1,0);
    vec_exact[1] = Point(0,1);
    vec_exact[2] = Point(2,5);
    vec_exact[3] = Point(-1,5);
    Reader vec_try;


    EXPECT_EQ(vec_exact, vec_try.MakeVector(input));
}


















#endif // __TEST_EMPTY_H

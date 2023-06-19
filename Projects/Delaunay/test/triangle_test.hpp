#ifndef __TRIANGLE_TEST_H
#define __TRIANGLE_TEST_H

#include <gtest/gtest.h>
#include "Delaunator.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(MethodsTriangle, Collinear)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);
    Point p4(4.,0.);

    EXPECT_FALSE(Collinear(p1, p2, p3));
    EXPECT_TRUE(Collinear(p1, p2, p4));
}

TEST(MethodsTriangle, isCounter)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);

    EXPECT_TRUE(isCounter(p1, p2, p3));
    EXPECT_FALSE(isCounter(p1, p3, p2));
}

// correttezza formula che distingue un punto nel cerchio da un punto fuori
TEST(MethodsTriangle, IsInTheCircle)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);
    Triangle t(0, p1, p2, p3);
    Point expected_in(1.,1.);
    Point expected_out(0.,3.);

    EXPECT_TRUE(t.IsInTheCircle(expected_in));
    EXPECT_FALSE(t.IsInTheCircle(expected_out));
}

TEST(MethodsTriangle, IsInTheTriangle)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);
    Triangle t(0, p1, p2, p3);
    Point expected_in(.5,.5);
    Point expected_out(0.,3.);

    EXPECT_TRUE(t.IsInTheTriangle(expected_in));
    EXPECT_FALSE(t.IsInTheTriangle(expected_out));
}

TEST(MethodsTriangle, FindAdjacent)
{
    Point p1(0.,0.);
    Point p2(1.,0.);
    Point p3(0.,1.);
    Point p4(1.,1.);
    Triangle t1(0, p1, p2, p3);
    t1.adjacentIds[0]=1;
    Triangle t2(1, p3, p2, p4);
    t2.adjacentIds[2]=0;

    EXPECT_EQ(0,t1.FindAdjacent(1));
    EXPECT_EQ(2,t2.FindAdjacent(0));
}

TEST(MetodiTriangolazione, Delaunator)
{
    vector<Point> vec_p = {
        {1,1},
        {4,2},
        {2,3},
        {3,5},
        {6,4}
    };
    vector<Triangle> vec_t = {
                              {Triangle(0,Point(1,1),Point(4,2),Point(2,3))},
                              {Triangle(1,Point(4,2),Point(3,5),Point(2,3))},
                              {Triangle(2,Point(4,2),Point(6,4),Point(3,5))},
                              };
    Triangulation t;
    EXPECT_EQ(t.Delaunator(vec_p),vec_t);
}
#endif // __TRIANGLE_TEST_H

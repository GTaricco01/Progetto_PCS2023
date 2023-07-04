#ifndef __TRIANGULATION_TEST_H
#define __TRIANGULATION_TEST_H

#include <gtest/gtest.h>
#include "Delaunator.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(MethodsTriangle, isCounter)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);

    EXPECT_TRUE(isCounter(p1, p2, p3));
    EXPECT_FALSE(isCounter(p1, p3, p2));
}

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

TEST(MethodsTriangulation, Delaunator)
{
    vector<Point> vec_p = {
        {1,1},
        {4,2},
        {2,3},
        {3,5},
        {6,4}
    };
    vector<Triangle> vec_t = {
                              {Triangle(0,Point(6.,4.),Point(3.,5.),Point(4.,2.))},
                              {Triangle(1,Point(1.,1.),Point(4.,2.),Point(2.,3.))},
                              {Triangle(2,Point(2.,3.),Point(4.,2.),Point(3.,5.))},
                              };
    Triangulation triangulation_try;
    EXPECT_EQ(triangulation_try.Delaunator(vec_p),vec_t);
}


TEST(MethodsTriangulation, Connect)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,3.);
    Point d(1.,1.);
    Triangle tstart(0,p1,p2,p3);

    Triangulation triangulation_try({tstart});
    list<int> l_exact = {0, 1, 2};
    vector<Triangle> triangulation_exact = {Triangle(0,p1,p2,d),Triangle(1,p2,p3,d),Triangle(2,p3,p1,d)};

    EXPECT_EQ(l_exact, triangulation_try.Connect(0,d));
    EXPECT_EQ(triangulation_try.getTriangles(), triangulation_exact);
}

/*
TEST(MethodsTriangulation, Flip)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,3.);
    Point p4(2.,2.);

    Triangle t1(0,p1,p2,p3);
    t1.adjacentIds = {1,-1,-1};
    Triangle t2(1,p2,p4,p3);
    t2.adjacentIds = {-1,0,-1};
    Triangulation triangulation_try({t1, t2});

    Triangle t1_flipped(0,p1,p2,p4);
    Triangle t2_flipped(0,p1,p4,p3);
    vector<Triangle> triangulation_exact = {t1_flipped, t2_flipped};

    triangulation_try.Flip(0,0,1,1);
    EXPECT_EQ(triangulation_try.getTriangles(), triangulation_exact);
}
*/

/*
TEST(MethodsTriangulation, Verify)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,3.);
    Point p4(2.,2.);

    Triangle t1(0,p1,p2,p3);
    t1.adjacentIds = {1,-1,-1};
    Triangle t2(1,p2,p4,p3);
    t2.adjacentIds = {-1,0,-1};
    Triangulation triangulation_try({t1, t2});

    Triangle t1_flipped(0,p1,p2,p4);
    Triangle t2_flipped(0,p1,p4,p3);
    vector<Triangle> triangulation_exact = {t1_flipped, t2_flipped};

    list<int> to_verify = {0, 1};

    triangulation_try.Verify(to_verify);
    EXPECT_EQ(triangulation_try.getTriangles(), triangulation_exact);
}
*/

#endif // __TRIANGULATION_TEST_H

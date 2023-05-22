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

#endif // __TEST_EMPTY_H

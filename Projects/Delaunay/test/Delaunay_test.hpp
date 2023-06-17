#ifndef __DELAUNAY_TEST_H
#define __DELAUNAY_TEST_H

#include <gtest/gtest.h>
#include "Delaunator_class.hpp"

using namespace testing;
using namespace ProjectLibrary;


TEST(FunzioniPoint, Collinear)
{
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);
    Point p4(4.,0.);

    EXPECT_FALSE(Collinear(p1, p2, p3));
    EXPECT_TRUE(Collinear(p1, p2, p4));
}


TEST(FunzioniPoint, isCounterClockWise)
{
    Point p1 = Point(0.,0.);
    Point p2 = Point(2.,0.);
    Point p3 = Point(0.,2.);

    EXPECT_TRUE(isCounter(p1, p2, p3));
    EXPECT_FALSE(isCounter(p1, p3, p2));
}

#endif // __TEST_EMPTY_H

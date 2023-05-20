#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "empty_class.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(MetodiTriangle, FunzioniBase)
{
    Point p1 = Point(0.,0.);
    Point p2 = Point(2.,0.);
    Point p3 = Point(0.,2.);
    Triangle t = Triangle(p1, p2, p3);
    Point ex_center = Point(1., 1.);
    Point ex_out = Point(0.,3.);
    EXPECT_TRUE(t.isCounterClockWise());
    EXPECT_EQ(ex_center, t.CircoCentro());
    EXPECT_TRUE(t.IsInTheCircle(ex_center));
    EXPECT_FALSE(t.IsInTheCircle(ex_out));

}


#endif // __TEST_EMPTY_H

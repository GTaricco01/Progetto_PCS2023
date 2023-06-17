#ifndef __OPERATORS_TEST_H
#define __OPERATORS_TEST_H

#include <gtest/gtest.h>
#include "Delaunator_class.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(Operators, Differenza)
{
    Point p1(1,1);
    Point diff(0,0);

    EXPECT_EQ(p1-p1,diff);
}

TEST(Operators, ScalarProd)
{
    Point p1(1.,1.);
    Point p2(2.,2.);
    double scalar = 4.;

    EXPECT_EQ(p1 * p2, scalar);
}

TEST(Operators, VectorProd)
{
    Point p1(1.,1.);
    Point p2(3.,2.);
    double ext = -1.;

    EXPECT_EQ(prod(p1,p2), ext);
}

TEST(Operators, Norm)
{
    Point p1(3.,4.);
    double n = 5.;

    EXPECT_EQ(norm(p1),n);
}

#endif // __OPERATORS_TEST_H

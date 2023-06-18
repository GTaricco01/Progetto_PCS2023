#ifndef __DELAUNAY_TEST_HPP
#define __DELAUNAY_TEST_HPP

#include <gtest/gtest.h>
#include "Delaunator.hpp"
#include "Operators.hpp"

using namespace testing;
using namespace ProjectLibrary;

TEST(a,b)
{
    EXPECT_EQ(1,1);
}

TEST(MetodiTriangolazione, Delaunator)
{
    cout << "cucu" << endl;
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

/*TEST(MetodiTriangolazione, Flip)
{
    Point p1 = Point(0,0);
    Point p2 = Point(1.5,0);
    Point p3 = Point(2,1);
    Point p4 = Point(1,1.5);
    vector<Triangle> triangles;
    vector<Triangle> triangles_flipped;
    Triangulation tt;
    triangles.push_back(Triangle(0,p1,p2,p3));
    triangles.push_back(Triangle(1,p1,p3,p4));
    triangles_flipped.push_back(Triangle(0,p1,p2,p4));
    triangles_flipped.push_back(Triangle(1,p2,p3,p4));

    tt.Flip(0,3,1,1);

    //EXPECT_EQ(tt,triangles_flipped);

}

TEST(MetodiTriangolazione, Flip)



*/


#endif //__DELAUNAY_TEST_HPP

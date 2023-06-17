#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>
#include "Delaunator_class.hpp"
#include "Reader_class.hpp"


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
    Point p1(0.,0.);
    Point p2(2.,0.);
    Point p3(0.,2.);

    EXPECT_TRUE(isCounter(p1, p2, p3));
    EXPECT_FALSE(isCounter(p1, p3, p2));
}

// correttezza formula che distingue un punto nel cerchio da un punto fuori
TEST(MetodiTriangle, IsInTheCircle)
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

//ricorda: se togli il controllo sull'ordinamento del costruttore dei triangoli sistema l'ordinamento del
//triangolo in questo test
TEST(MetodiTriangle, IsInTheTriangle)
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

TEST(MetodiTriangle, FindAdjacent)
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

/*
TEST(MetodiTriangolazione, Connect)
{
    Point p1 = Point(1,2);
    Point p2 = Point(2,0);
    Point p3 = Point(3,2);
    Point d = Point(2,1);
    Triangle t = Triangle(0,p1, p2, p3);
    vector<Triangle> vecT = {Triangle(p1, p2, d),
                             Triangle(p2, p3, d),
                             Triangle(p3, p1, d)};

    EXPECT_EQ(vecT, t.Connect(d));

}
*/



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

    EXPECT_EQ(vec_try.MakeVector(input), vec_exact);
}

/*
TEST(ImportDati, Repetitions)
{
    vector<Point> vec_rep = {
        {0,0},
        {0,1},
        {0,1}
    };
    vector<Point> vec_no_rep = {
        {0,0},
        {0,1},
        {0,2}
    };

    EXPECT_TRUE(Repetitions(vec_rep));
    EXPECT_FALSE(Repetitions(vec_no_rep));
}*/
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
*/







#endif // __TEST_EMPTY_H

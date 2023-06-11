#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>
#include "Delaunay_class.hpp"

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
    Point p2(0.,2.);
    Point p3(2.,0.);
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
    Triangle t = Triangle(0, p1, p2, p3);
    vector<Triangle> vecT = {Triangle(0, p1, p2, d),
                             Triangle(1, p2, p3, d),
                             Triangle(2, p3, p1, d)};

    EXPECT_EQ(vecT, t.Connect(d));
}
*/
/*
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
*/






#endif // __TEST_EMPTY_H

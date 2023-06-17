#include "delaunay_test.hpp"
#include "operators_test.hpp"
#include "reader_test.hpp"
#include "triangle_test.hpp"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

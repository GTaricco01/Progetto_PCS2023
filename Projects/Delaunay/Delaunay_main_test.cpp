#include <gtest/gtest.h>
#include "Delaunay_test.hpp"
#include "Operators_test.hpp"
#include "Reader_test.hpp"
#include "Triangle_test.hpp"

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include "gtest/gtest.h"

#include "networking.gtest"
#include "utils.gtest"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


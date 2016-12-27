#include "gtest/gtest.h"

// Include Order Determines Run Order!!!
#include "c-linkage.gtest"
#include "utils.gtest"
#include "entrance-protocol.gtest"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


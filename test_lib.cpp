#include "lib.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>

TEST(version_test_case, version_test)
{
  EXPECT_GT(lib::version_patch(), 0);
  EXPECT_GT(lib::version_major(), 0);
  EXPECT_GT(lib::version_minor(), 0);
}

TEST(factorial_test, factorial)
{
  EXPECT_EQ(lib::factorial(0), 1);
  EXPECT_EQ(lib::factorial(1), 1);
  EXPECT_EQ(lib::factorial(2), 2);
  EXPECT_EQ(lib::factorial(3), 6);
  EXPECT_EQ(lib::factorial(9), 362880);
}
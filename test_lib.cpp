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

TEST(allocator, allocate)
{
    lib::const_allocator<int,1> allocator;
    int* p{nullptr};

    EXPECT_NO_THROW(p = allocator.allocate(1));
    EXPECT_NE(p, nullptr);
    EXPECT_EQ(sizeof(allocator), sizeof(int) + sizeof(bool));
}

TEST(allocator, allocate_ten_items)
{
    lib::const_allocator<int,10> allocator;

    EXPECT_EQ(sizeof(allocator), 10 * (sizeof(int) + sizeof(bool)));
}

TEST(allocator, allocate_map)
{
    lib::const_allocator<int,2> allocator;

    using const_alocator_2 = lib::const_allocator<std::pair<const int, int>, 2>;

    std::map<int, int, std::less<int>, const_alocator_2> map;

    EXPECT_NO_THROW(map[0] = 1);
    EXPECT_NO_THROW(map[1] = 2);

    EXPECT_EQ(map[0], 1);
    EXPECT_EQ(map[1], 2);
}

// TEST(allocator, size) {
//     constexpr unsigned int n = 2;
//     using type = test_class;
//     auto radix = sizeof(void *);

//     custom::allocator<type, n> allocator;

//     auto data_size = ((sizeof(type) * n + radix - 1) / radix) * radix;
//     auto bitset_size = sizeof(std::bitset<n>);
//     EXPECT_EQ(sizeof(allocator), data_size + bitset_size);
// }
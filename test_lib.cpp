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
    using const_alocator_2 = lib::const_allocator<std::pair<const int, int>, 2>;

    std::map<int, int, std::less<int>, const_alocator_2> map;

    EXPECT_NO_THROW(map[0] = 1);
    EXPECT_NO_THROW(map[1] = 2);

    EXPECT_EQ(map[0], 1);
    EXPECT_EQ(map[1], 2);
}

TEST(container, push_back)
{
    lib::custom_list<int> list{};

    list.push_back(1);

    EXPECT_EQ(list.size(), 1);

    list.push_back(2);

    EXPECT_EQ(list.size(), 2);
}

TEST(container, iterator)
{
    lib::custom_list<int> list{};

    list.push_back(1);
    list.push_back(2);

    EXPECT_EQ(list.size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    --it;
    EXPECT_EQ(*it, 1);
}



TEST(container, range_for)
{
    lib::custom_list<int> list{};
    std::stringstream ss;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    for(const auto& i : list)
        ss<<i;

    EXPECT_EQ(ss.str(), "123");
}

TEST(container, push_front)
{
    lib::custom_list<int> list{};
    std::stringstream ss;

    list.push_front(1);
    EXPECT_EQ(list.size(), 1);

    list.push_front(2);
    EXPECT_EQ(list.size(), 2);


    for(const auto& i : list)
        ss<<i;

    EXPECT_EQ(ss.str(), "21");
}

TEST(container_allocator, push)
{
    using const_alocator_2 = lib::const_allocator<int, 2>;

    lib::custom_list<int, const_alocator_2> list;

    EXPECT_NO_THROW(list.push_back(1));
    EXPECT_NO_THROW(list.push_front(2));

    auto it = list.begin();
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 1);
}
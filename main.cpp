#include "lib.h"

#include <iostream>
#include <map>

int main(int argc, char const *argv[])
{
    std::map<int, int> factorialValues1;
    for (int i = 0; i < 10; ++i)
        factorialValues1[i] = lib::factorial(i);

    using map_alocator_10 = lib::const_allocator<std::pair<const int, int>, 10>;
    using const_map = std::map<int, int, std::less<int>, map_alocator_10>;

    const_map factorialValues2;

    for (int i = 0; i < 10; ++i)
        factorialValues2[i] = lib::factorial(i);

    for (const auto& i : factorialValues2)
        std::cout << i.first << " " << i.second;
    std::cout << std::endl;

    lib::custom_list<int> list1;
    for (int i = 0; i < 10; ++i)
        list1.push_back(i);

    using list_alocator_10 = lib::const_allocator<int, 10>;

    lib::custom_list<int, list_alocator_10> list2;
    for (int i = 0; i < 10; ++i)
        list2.push_back(i);

    for (const auto& i : list2)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}

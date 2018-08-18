#include "lib.h"

#include <iostream>
#include <map>

int main(int argc, char const *argv[])
{
    using std_map = std::map<int, int>;
    std_map factorialValues;
    for (int i = 0; i < 10; ++i) {
        factorialValues[i] = lib::factorial(i);
    }

    for (auto f : factorialValues)
        std::cout << f.first << " " << f.second << std::endl;

    using const_alocator_10 = lib::const_allocator<std::pair<const int, int>, 10>;
    using const_map = std::map<int, int, std::less<int>, const_alocator_10>;

    const_map factorialValues2;

    for (int i = 0; i < 10; ++i) {
        factorialValues2[i] = lib::factorial(i);
    }

    for (auto f : factorialValues2)
        std::cout << f.first << " " << f.second << std::endl;

    return 0;
}

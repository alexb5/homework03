#include "lib.h"

#include <iostream>
#include <map>

int main(int argc, char const *argv[])
{
    std::map<int,int> factorialValues;
    for (int i = 0; i < 10; ++i)
        factorialValues[i] = lib::factorial(i);

    for (auto f : factorialValues)
        std::cout << f.first << " " << f.second << std::endl;

    return 0;
}

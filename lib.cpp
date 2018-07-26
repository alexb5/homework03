#include "lib.h"

#include "version.h"

#include <algorithm>
#include <iostream>
#include <string>

int lib::version_major() {
    return PROJECT_VERSION_MAJOR;
}

int lib::version_minor() {
    return PROJECT_VERSION_MINOR;
}

int lib::version_patch() {
    return PROJECT_VERSION_PATCH;
}

size_t lib::factorial(int n)
{
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    size_t result{1};
    for (int i = 2; i <= n; ++i)
        result *= i;

    return result;
}

// main.cpp

#include "secant.h"
#include <iostream>

int main() {
    float a, b, delta;
    int maxitr;

    std::cout << "Enter the initial approximations: ";
    std::cin >> a >> b;
    std::cout << "Enter the maximum number of iterations: ";
    std::cin >> maxitr;
    std::cout << "Enter the error tolerance limit in the root: ";
    std::cin >> delta;

    secantMethod(a, b, maxitr, delta);

    return 0;
}

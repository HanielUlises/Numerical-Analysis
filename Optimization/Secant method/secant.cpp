// secant.cpp

#include "secant.h"
#include <iostream>
#include <cmath>

float f(float x) {
    return x * x * x - 4 * x - 9;
}

void secantMethod(float a, float b, int maxitr, float delta) {
    int itr = 1;
    float x;

    x = a - ((b - a) / (f(b) - f(a)) * f(a));
    std::cout << "At iteration " << itr << ",\t x[" << itr << "] = " << x << "\n";

    do {
        a = b;
        b = x;
        x = a - ((b - a) / (f(b) - f(a)) * f(a));
        itr++;
        std::cout << "At iteration " << itr << ",\t x[" << itr << "] = " << x << "\n";

        if (itr >= maxitr) {
            std::cout << "Sorry, more number of iterations are required\n";
            break;
        }
    } while ((fabs(b - x) > delta) && (fabs(a - x) > delta));
}

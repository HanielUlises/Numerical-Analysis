#include "secant.h"
#include <iostream>
#include <cmath>

float cubic(float x) {
    return x * x * x - 4 * x - 9;
}

// Secant method
template<typename F, typename T>
void secantMethod(F func, T a, T b, int maxitr, T delta) {
    int itr = 1;
    T x = a - ((b - a) / (func(b) - func(a))) * func(a); // First approximation
    std::cout << "At iteration " << itr << ",\t x[" << itr << "] = " << x << "\n";

    do {
        a = b;
        b = x;
        x = a - ((b - a) / (func(b) - func(a))) * func(a); // Secant formula
        itr++;
        std::cout << "At iteration " << itr << ",\t x[" << itr << "] = " << x << "\n";

        if (itr >= maxitr) {
            std::cout << "Sorry, more number of iterations are required\n";
            break;
        }
    } while ((std::fabs(b - x) > delta) && (std::fabs(a - x) > delta));
}

template<int MaxItr, typename F, typename T>
struct SecantMethodStatic {
    static void apply(F func, T a, T b, T delta) {
        secantMethod(func, a, b, MaxItr, delta);
    }
};

int main() {
    std::cout << "Testing with f(x) = x³ - 4x - 9:\n";
    secantMethod(cubic, 2.0f, 3.0f, 10, 0.0001f);

    std::cout << "\nTesting with f(x) = x² - 2:\n";
    secantMethod([](float x) { return x * x - 2; }, 1.0f, 2.0f, 10, 0.0001f);

    std::cout << "\nTesting with static iteration limit (5 iterations):\n";
    SecantMethodStatic<5, decltype(cubic), float>::apply(cubic, 2.0f, 3.0f, 0.0001f);

    return 0;
}
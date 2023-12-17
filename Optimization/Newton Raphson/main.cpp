#include <iostream>
#include "NewtonRaphson.h"

float f(float x) {
    return x - std::cos(x);
}

float df(float x) {
    return 1 + std::sin(x);
}

int main() {
    float initialGuess, tolerance;
    int maxIterations;

    std::cout << "Enter initial approximation: ";
    std::cin >> initialGuess;
    std::cout << "Enter the maximum number of iterations: ";
    std::cin >> maxIterations;
    std::cout << "Enter the error tolerance limit in the root: ";
    std::cin >> tolerance;

    try {
        NewtonRaphson<decltype(f), decltype(df)> solver(f, df);
        float root = solver.findRoot(initialGuess, maxIterations, tolerance);
        std::cout << "Root found: " << root << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

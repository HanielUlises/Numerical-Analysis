#include <iostream>
#include <cmath>

const float ERROR_TOLERANCE = 0.0000001;

// Function to calculate sine using Taylor Series
// @param x: The angle in radians
// @return: The sine of x
float calculateSineTaylorSeries(float x) {
    float sineApprox = 0.0;
    float term = x;
    int termNumber = 1;

    while (std::fabs(term) >= ERROR_TOLERANCE) {
        sineApprox += term;
        termNumber += 2;
        term *= -x * x / (termNumber * (termNumber - 1));
    }

    return sineApprox;
}

int main() {
    for(float x = 0; x <= 6.5; x += 0.25) {
        float taylorSine = calculateSineTaylorSeries(x);
        float librarySine = std::sin(x);
        float error = std::fabs(taylorSine - librarySine);

        std::cout << "\nAt x = " << x << ":\tTaylor Series Sine = " << taylorSine
                  << ",\tLibrary Sine = " << librarySine 
                  << ",\tError = " << error;
    }

    return 0;
}

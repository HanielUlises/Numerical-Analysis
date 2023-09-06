#include "euler.h"

// Recursive approach
double infiniteSeriesRecursive(int number){
    if (number == 0){
        return 1.0; // Special case for the first term in the series
    } else {
        return 1.0 / number * infiniteSeriesRecursive(number - 1);
    }
}

// For loop approach
double infiniteSeriesForLoop(int number) {
    if (number == 0) {
        return 1.0; // Special case for the first term in the series
    } else {
        // The general term for the series is 1/n!
        double term = 1.0;
        for (int i = 1; i <= number; i++) {
            term /= i;
        }
        return term;
    }
}

double approach(int number) {
    double e = 0.0;
    for (int i = 0; i <= number; i++) {
        e += infiniteSeriesForLoop(i); // You can choose either approach here
    }
    return e;
}
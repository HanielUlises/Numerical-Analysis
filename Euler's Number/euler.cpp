#include "euler.h"

double infiniteSeries(int number) {
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
        e += infiniteSeries(i);
    }
    return e;
}
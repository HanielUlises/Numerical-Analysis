#include "MonteCarlo.h"
#include <random>
#include <numeric>
#include <iostream>

MonteCarlo::MonteCarlo(int numSimulations, std::function<double()> randomVariable)
    : numSimulations(numSimulations), randomVariable(randomVariable) {}

MonteCarlo::MonteCarlo(int numSimulations, std::function<double(double)> integrand, double a, double b)
    : numSimulations(numSimulations), integrand1D(integrand), a(a), b(b) {}

MonteCarlo::MonteCarlo(int numSimulations, std::function<double(const std::vector<double>&)> integrand, const std::vector<double>& lowerBounds, const std::vector<double>& upperBounds)
    : numSimulations(numSimulations), integrandND(integrand), lowerBounds(lowerBounds), upperBounds(upperBounds) {}

double MonteCarlo::calculateExpectedValue() {
    double sum = 0.0;
    for (int i = 0; i < numSimulations; ++i) {
        sum += randomVariable();
    }
    return sum / numSimulations;
}

double MonteCarlo::calculateIntegral() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(a, b);

    double sum = 0.0;
    for (int i = 0; i < numSimulations; ++i) {
        double x = dis(gen);
        sum += integrand1D(x);
    }

    return (b - a) * sum / numSimulations;
}

double MonteCarlo::calculateMultidimensionalIntegral() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    int dimensions = lowerBounds.size();
    double volume = 1.0;
    for (int i = 0; i < dimensions; ++i) {
        volume *= (upperBounds[i] - lowerBounds[i]);
    }

    double sum = 0.0;
    for (int i = 0; i < numSimulations; ++i) {
        std::vector<double> x(dimensions);
        for (int j = 0; j < dimensions; ++j) {
            std::uniform_real_distribution<> dis(lowerBounds[j], upperBounds[j]);
            x[j] = dis(gen);
        }
        sum += integrandND(x);
    }

    return volume * sum / numSimulations;
}

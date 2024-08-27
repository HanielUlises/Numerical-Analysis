#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <functional>
#include <vector>

class MonteCarlo {
public:
    // General Monte Carlo simulation
    MonteCarlo(int numSimulations, std::function<double()> randomVariable);
    
    // Monte Carlo integration over [a, b]
    MonteCarlo(int numSimulations, std::function<double(double)> integrand, double a, double b);
    
    // Monte Carlo multidimensional integration
    MonteCarlo(int numSimulations, std::function<double(const std::vector<double>&)> integrand, const std::vector<double>& lowerBounds, const std::vector<double>& upperBounds);

    // Calculate expected value (general Monte Carlo)
    double calculateExpectedValue();

    // Calculate the integral over [a, b]
    double calculateIntegral();

    // Calculate multidimensional integral
    double calculateMultidimensionalIntegral();

private:
    int numSimulations;
    std::function<double()> randomVariable;
    std::function<double(double)> integrand1D;
    std::function<double(const std::vector<double>&)> integrandND;
    double a, b; // Interval [a, b] for 1D integration
    std::vector<double> lowerBounds, upperBounds; // Bounds for multidimensional integration
};

#endif // MONTECARLO_H

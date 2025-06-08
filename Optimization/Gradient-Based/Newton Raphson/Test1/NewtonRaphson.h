#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include <cmath>
#include <stdexcept>
#include <functional>
#include <optional>
#include <limits>

template<typename T, typename Func, typename DerivFunc>
class NewtonRaphson {
public:
    struct Config {
        int maxIterations = 100;
        T tolerance = 1e-6;
        T derivativeStep = 1e-6;
        T divergenceThreshold = 1e6;
    };

    NewtonRaphson(Func f, DerivFunc df, Config config = Config());
    explicit NewtonRaphson(Func f, Config config = Config());

    std::optional<T> findRoot(T initialGuess) const;

    struct ConvergenceInfo {
        int iterationsUsed = 0;
        bool converged = false;
        T lastError = 0;
        std::string status;
    };
    ConvergenceInfo getConvergenceInfo() const;

private:
    Func f;
    DerivFunc df;
    bool useNumericalDeriv;
    Config config;
    mutable ConvergenceInfo lastRunInfo;

    T numericalDerivative(T x) const;
    void validateParameters() const;
};

#endif
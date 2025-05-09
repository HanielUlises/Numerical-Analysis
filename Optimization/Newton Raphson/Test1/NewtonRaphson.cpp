#include "NewtonRaphson.h"

template<typename T, typename Func, typename DerivFunc>
NewtonRaphson<T, Func, DerivFunc>::NewtonRaphson(Func f, DerivFunc df, Config config)
    : f(f), df(df), useNumericalDeriv(false), config(config) {
    validateParameters();
}

template<typename T, typename Func, typename DerivFunc>
NewtonRaphson<T, Func, DerivFunc>::NewtonRaphson(Func f, Config config)
    : f(f), df(nullptr), useNumericalDeriv(true), config(config) {
    validateParameters();
}

template<typename T, typename Func, typename DerivFunc>
void NewtonRaphson<T, Func, DerivFunc>::validateParameters() const {
    if (config.maxIterations <= 0) {
        throw std::invalid_argument("Maximum iterations must be positive");
    }
    if (config.tolerance <= 0) {
        throw std::invalid_argument("Tolerance must be positive");
    }
    if (config.derivativeStep <= 0) {
        throw std::invalid_argument("Derivative step must be positive");
    }
    if (config.divergenceThreshold <= 0) {
        throw std::invalid_argument("Divergence threshold must be positive");
    }
}

template<typename T, typename Func, typename DerivFunc>
T NewtonRaphson<T, Func, DerivFunc>::numericalDerivative(T x) const {
    T h = config.derivativeStep;
    return (f(x + h) - f(x - h)) / (2 * h);
}

template<typename T, typename Func, typename DerivFunc>
std::optional<T> NewtonRaphson<T, Func, DerivFunc>::findRoot(T initialGuess) const {
    T x0 = initialGuess, x1, h;
    lastRunInfo = ConvergenceInfo();

    for (int itr = 1; itr <= config.maxIterations; ++itr) {
        T deriv = useNumericalDeriv ? numericalDerivative(x0) : df(x0);
        
        if (std::abs(deriv) < std::numeric_limits<T>::epsilon()) {
            lastRunInfo.status = "Derivative too small";
            return std::nullopt;
        }

        h = f(x0) / deriv;
        x1 = x0 - h;

        lastRunInfo.iterationsUsed = itr;
        lastRunInfo.lastError = std::abs(h);

        if (std::abs(h) < config.tolerance) {
            lastRunInfo.converged = true;
            lastRunInfo.status = "Converged";
            return x1;
        }

        if (std::abs(x1) > config.divergenceThreshold) {
            lastRunInfo.status = "Solution diverged";
            return std::nullopt;
        }

        x0 = x1;
    }

    lastRunInfo.status = "Maximum iterations reached";
    return std::nullopt;
}

template<typename T, typename Func, typename DerivFunc>
typename NewtonRaphson<T, Func, DerivFunc>::ConvergenceInfo 
NewtonRaphson<T, Func, DerivFunc>::getConvergenceInfo() const {
    return lastRunInfo;
}
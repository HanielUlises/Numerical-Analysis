#include "NewtonRaphson.h"

template<typename Func, typename DerivFunc>
NewtonRaphson<Func, DerivFunc>::NewtonRaphson(Func f, DerivFunc df)
    : f(f), df(df) {}

template<typename Func, typename DerivFunc>
float NewtonRaphson<Func, DerivFunc>::findRoot(float initialGuess, int maxIterations, float tolerance) const {
    float h, x0 = initialGuess, x1;
    for(int itr = 1; itr <= maxIterations; itr++) {
        h = f(x0) / df(x0);
        x1 = x0 - h;

        if(std::fabs(h) < tolerance) {
            return x1;
        }
        x0 = x1;
    }
    throw std::runtime_error("Maximum iterations reached without converging");
}

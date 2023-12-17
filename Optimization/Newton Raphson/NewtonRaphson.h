#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include <cmath>

// Class template for Newton-Raphson Method
template<typename Func, typename DerivFunc>
class NewtonRaphson {
public:
    NewtonRaphson(Func f, DerivFunc df);

    float findRoot(float initialGuess, int maxIterations, float tolerance) const;

private:
    Func f;        // Function whose root is to be found
    DerivFunc df;  // Derivative of the function
};

#endif

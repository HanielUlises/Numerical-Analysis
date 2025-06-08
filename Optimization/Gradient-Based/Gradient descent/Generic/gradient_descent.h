#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include "../Analysis/Differentiation/autodiff.h"
#include <vector>
#include <iostream>

template<typename T, typename F>
void gradient_descent(F objective, std::vector<variable<T>*>& variables, 
                      T learning_rate, int max_iterations, T tolerance);

template<int max_iterations, typename T, typename F>
struct gradient_descent_static {
    static void apply(F objective, std::vector<variable<T>*>& variables, 
                      T learning_rate, T tolerance);
};

#endif // GRADIENT_DESCENT_H
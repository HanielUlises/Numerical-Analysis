#ifndef SECANT_H
#define SECANT_H

template<typename F, typename T>
void secantMethod(F func, T a, T b, int maxitr, T delta);

#endif // SECANT_H
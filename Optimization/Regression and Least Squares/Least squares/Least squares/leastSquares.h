#include <iostream>
#include <array>

// A structure to hold a compile-time point
template<int X, int Y>
struct Point {
    static constexpr int x = X;
    static constexpr int y = Y;
};

// Calculate sum of X, Y, XY, and X^2 for points
template<typename... Points>
struct LeastSquaresCalculator;

template<int X, int Y, typename... Rest>
struct LeastSquaresCalculator<Point<X, Y>, Rest...> {
    static constexpr int sumX = X + LeastSquaresCalculator<Rest...>::sumX;
    static constexpr int sumY = Y + LeastSquaresCalculator<Rest...>::sumY;
    static constexpr int sumXY = X * Y + LeastSquaresCalculator<Rest...>::sumXY;
    static constexpr int sumX2 = X * X + LeastSquaresCalculator<Rest...>::sumX2;
    static constexpr int count = 1 + LeastSquaresCalculator<Rest...>::count;
};

template<>
struct LeastSquaresCalculator<> {
    static constexpr int sumX = 0;
    static constexpr int sumY = 0;
    static constexpr int sumXY = 0;
    static constexpr int sumX2 = 0;
    static constexpr int count = 0;
};

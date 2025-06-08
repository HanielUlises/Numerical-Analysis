#include "leastSquares.h"

int main (){
    using Points = LeastSquaresCalculator<
        Point<1, 2>,
        Point<2, 3>,
        Point<3, 4>
        
    >;

    constexpr int n = Points::count;
    constexpr double m = (n * Points::sumXY - Points::sumX * Points::sumY) / 
                         (n * Points::sumX2 - Points::sumX * Points::sumX);
    constexpr double b = (Points::sumY - m * Points::sumX) / n;

    std::cout << "Line: y = " << m << "x + " << b << std::endl;

    return 0;
}
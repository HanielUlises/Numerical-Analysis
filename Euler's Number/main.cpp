#include "euler.h"

int main() {
    int number;
    std::cout << "Enter the number of terms in the series: ";
    std::cin >> number;

    double e_approximation = approach(number);
    std::cout << "Approximation of e after " << number << " terms: " << e_approximation << std::endl;

    return 0;
}
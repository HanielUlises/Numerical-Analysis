#include "decToBin.h"

void decToBin() {
    int decimalNumber;
    std::cout << "Enter a decimal number to convert to its binary equivalent: ";
    std::cin >> decimalNumber;

    if (decimalNumber == 0) {
        std::cout << "The binary number equivalent is: 0" << std::endl;
        return;
    }

    std::string binaryNumber = "";
    while (decimalNumber > 0) {
        binaryNumber = std::to_string(decimalNumber % 2) + binaryNumber;
        decimalNumber /= 2;
    }

    std::cout << "The binary number equivalent is: " << binaryNumber << std::endl;
}
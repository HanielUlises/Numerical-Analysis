#include "binToDec.h"

void conversion(){
    std::string line;
    std::cout<<"Enter a binary number to convert to its decimal equivalent"<<std::endl;
    getline(std::cin,line);

    int decimalNumber = 0;
    int binaryNumber = 0;
    int multiplier = 1;

    for (int i = line.length(); i > 0; i--){
        // Extraction of one number per iteration
        std::string number = line.substr(i-1,1);
        // Converts the number using c_str-function from string to interger
        binaryNumber = atof(number.c_str());

        // Calculate decimal number
        decimalNumber += binaryNumber * multiplier;
        multiplier *= 2;
    }

    std::cout<<"The decimal number equivalent is: "<<decimalNumber <<std::endl;
}
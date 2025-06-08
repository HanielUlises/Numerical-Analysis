#include <iostream>
#include <fstream>
#include <cmath>

void minimo(){
    float Xo = -0.5;
    float Yo = -0.5;
    float Xaux=0;
    float Yaux=0;
    float err = 0;

    const float tol = 0.001;
    const float lambda = 0.0002;

    std::ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        int i = 1;

        outputFile << "X: " << Xo << std::endl;
        outputFile << "Y: " << Yo << std::endl;
        do {
            Xaux = Xo;
            Yaux = Yo;
            outputFile << "Iteration " << i << ":" << std::endl;

            Yo = Yo - lambda * (3 * std::pow(Yaux, 2) + Xaux + 1);
            Xo = Xo - lambda * (2 * Xaux + Yaux + 1);

            outputFile << "X: " << Xo << std::endl;
            outputFile << "Y: " << Yo << std::endl;

            err = std::sqrt((std::pow((Xaux - Xo), 2) + std::pow((Yaux - Yo), 2)));
            outputFile << "Error: " <<err<<std::endl;

            i++;
        } while (err > tol);

        outputFile.close(); 
    } else {
        std::cerr << "Unable to open the output file." << std::endl;
    }
}

int main() {
    minimo();
    return 0;
}

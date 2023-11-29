#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

float parcialEnX (float X, float Y, float Z){
    return (1-Y+2*X);
}

float parcialEnY (float X, float Y, float Z){
    return (-X + 2*Y);
}

float parcialEnZ (float X, float Y, float Z){
    return(2 + 2*Z);
}

void minimo(std::vector<float>& minimo){
    float Xo = 1.0f;
    float Yo = 1.0f;
    float Zo = 1.0f;

    float Xaux = 0.0f;
    float Yaux = 0.0f;
    float Zaux = 0.0f;

    float err = 0.0f;

    const float tol = 0.05;
    const float lambda = 0.25;

    std::ofstream outputFile("minimo.txt");

    if (outputFile.is_open()) {
        int i = 1;

        outputFile << "=======================================" << std::endl;
        outputFile << "Valores iniciales" <<std::endl;
        outputFile << "=======================================" << std::endl;
        outputFile << "X: " << Xo << std::endl;
        outputFile << "Y: " << Yo << std::endl;
        outputFile << "Z: " << Zo << std::endl;
        do {
            Xaux = Xo;
            Yaux = Yo;
            Zaux = Zo;
            outputFile << "=======================================" << std::endl;
            outputFile << "Iteracion " << i << ":" << std::endl;

            Xo = Xo - lambda * parcialEnX(Xaux, Yaux, Zaux);
            Yo = Yo - lambda * parcialEnY(Xaux, Yaux, Zaux);
            Zo = Zo - lambda * parcialEnZ(Xaux, Yaux, Zaux);

            outputFile << "=======================================" << std::endl;
            outputFile << "< " << Xo << " , "<< Yo <<" , "<< Zo <<" >" << std::endl;
            outputFile << "=======================================" << std::endl;

            outputFile << "X: " << Xo << std::endl;
            outputFile << "Y: " << Yo << std::endl;
            outputFile << "Z: " << Zo << std::endl;

            err = std::sqrt((std::pow((Xaux - Xo), 2) + std::pow((Yaux - Yo), 2)) + std::pow((Zaux - Zo), 2));
            outputFile << "=======================================" << std::endl;
            outputFile << "Error: " <<err<<std::endl;
            outputFile << std::endl;

            i++;
        } while (err >= tol);

        outputFile.close(); 
    } else {
        std::cerr << "Unable to open the output file." << std::endl;
    }

    minimo.push_back(Xo);
    minimo.push_back(Yo);
    minimo.push_back(Zo);
}

void maximo(std::vector<float>& maximo){
    float Xo = 1.0f;
    float Yo = 1.0f;
    float Zo = 1.0f;

    float Xaux=0.0f;
    float Yaux=0.0f;
    float Zaux = 0.0f;

    float err = 0.0f;

    const float tol = 0.05;
    const float lambda = 0.25;

    std::ofstream outputFile("maximo.txt");

    if (outputFile.is_open()) {
        int i = 1;

        outputFile << "=======================================" << std::endl;
        outputFile << "Valores iniciales" <<std::endl;
        outputFile << "=======================================" << std::endl;
        outputFile << "X: " << Xo << std::endl;
        outputFile << "Y: " << Yo << std::endl;
        outputFile << "Z: " << Zo << std::endl;
        do {
             Xaux = Xo;
            Yaux = Yo;
            Zaux = Zo;
            outputFile << "=======================================" << std::endl;
            outputFile << "Iteracion " << i << ":" << std::endl;

            Xo = Xo + lambda * parcialEnX(Xaux, Yaux, Zaux);
            Yo = Yo + lambda * parcialEnY(Xaux, Yaux, Zaux);
            Zo = Zo + lambda * parcialEnZ(Xaux, Yaux, Zaux);

            outputFile << "=======================================" << std::endl;
            outputFile << "< " << Xo << " , "<< Yo <<" , "<< Zo <<" >" << std::endl;
            outputFile << "=======================================" << std::endl;

            outputFile << "X: " << Xo << std::endl;
            outputFile << "Y: " << Yo << std::endl;
            outputFile << "Z: " << Zo << std::endl;

            err = std::sqrt((std::pow((Xaux - Xo), 2) + std::pow((Yaux - Yo), 2)) + std::pow((Zaux - Zo), 2));
            outputFile << "Error: " <<err<<std::endl;
            outputFile << std::endl;

            i++;
        } while (err >= tol);

        outputFile.close(); 
    } else {
        std::cerr << "Unable to open the output file." << std::endl;
    }
    maximo.push_back(Xo);
    maximo.push_back(Yo);
    maximo.push_back(Zo);

}


int main() {
    int sel = 0;
    std::vector<float> res = {0.0f};
    std::cout << "Seleccione \n 1) Minimo 2) Maximo" << std::endl;
    std::cin >> sel;

    switch (sel){
    case 1:
        std::cout << "Minimo de la funcion" << std::endl;
        minimo(res);
        std::cout << "Punto minimo en: ";
        std::cout   << "X(" << res.at(1) <<")" 
                    << "Y(" << res.at(2) <<")"
                    << "Z(" << res.at(3) <<")";
        break;
    case 2:
        std::cout << "Maximo de la funcion" << std::endl;
        maximo(res);
        std::cout   << "Punto maximo en: ";
        std::cout   << "X(" << res.at(1) <<")" 
                    << "Y(" << res.at(2) <<")"
                    << "Z(" << res.at(3) <<")";
        break;
    default:
        std::cout << "Respuesta no valida" << std::endl;
        break;
    }
    return 0;
}
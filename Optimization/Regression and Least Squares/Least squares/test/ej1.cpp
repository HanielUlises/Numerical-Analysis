#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

const int m = 9;

struct Data {
    double x;
    double y;
};

void readCSV(const std::string& filename, std::vector<Data>& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string lineX, lineY;
    if (!std::getline(file, lineX) || !std::getline(file, lineY)) {
        std::cerr << "Error al leer líneas del archivo" << std::endl;
        return;
    }

    std::istringstream issX(lineX), issY(lineY);
    std::string valueX, valueY;
    while (std::getline(issX, valueX, ';') && std::getline(issY, valueY, ';')) {
        Data rowData;
        rowData.x = std::stod(valueX);
        rowData.y = std::stod(valueY);
        data.push_back(rowData);
    }

    file.close();
}

void minimosCuadrados() {
    std::vector<Data> data;
    readCSV("test.csv", data);

    double Co = 0.5f, C1 = 200.0f;
    double lambda = 0.02f, tol = 3.0f, err = 0.0f;

    do {
        double sumError = 0.0f;
        double C1f = 0.0f;
        for (const auto& d : data) {
            double prediction = Co + C1 * d.x;
            double error = prediction - d.y;
            sumError += error * error;
            C1f += C1 - lambda * (1.0 / m) * error * d.x;
        }
        C1 = C1f;
        err = std::sqrt(sumError / m);
    } while (err > tol);

    std::cout << "El valor C1f es " << C1 << " con un error de " << err << std::endl;
}

int main() {
    minimosCuadrados();
    return 0;
}
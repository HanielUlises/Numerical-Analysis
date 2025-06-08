#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

struct IrisData {
    double sepal_length;
    double petal_width;
};

bool leerCSV(const std::string& archivo, std::vector<IrisData>& datos) {
    std::ifstream file(archivo);
    std::string linea, temp;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return false;
    }

    std::getline(file, linea);

    while (std::getline(file, linea)) {
        std::istringstream ss(linea);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 5) {
            try {
                double sepal_length = std::stod(tokens[0]);
                double petal_width = std::stod(tokens[3]);
                datos.push_back({sepal_length, petal_width});
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error al convertir los datos: " << e.what() << std::endl;
                continue;
            }
        }
    }

    file.close();
    return true;
}

void ajusteLineal(const std::vector<IrisData>& datos, double& Co, double& C1) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    int n = datos.size();

    for (const auto& dato : datos) {
        sum_x += dato.petal_width;
        sum_y += dato.sepal_length;
        sum_xy += dato.sepal_length * dato.petal_width;
        sum_x2 += dato.petal_width * dato.petal_width;
    }

    C1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    Co = (sum_y - C1 * sum_x) / n;
}

int main() {
    std::vector<IrisData> datos;
    std::string archivo = "iris.csv";

    if (!leerCSV(archivo, datos)) {
        std::cerr << "No se pudo leer el archivo." << std::endl;
        return 1;
    }

    double Co = 0;
    double C1 = 0;
    ajusteLineal(datos, Co, C1);

    std::cout << "Ajuste Lineal: sepal_length = " << Co << " + " << C1 << " * petal_width" << std::endl;

    return 0;
}
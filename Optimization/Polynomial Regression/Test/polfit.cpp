#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

struct Datos {
    double T;
    double P;
};

bool leerCSV(const std::string& archivo, std::vector<Datos>& datos) {
    std::ifstream file(archivo);
    std::string linea, temp;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return false;
    }

    if (!getline(file, linea)) {
        std::cerr << "Error al leer la línea de encabezado." << std::endl;
        return false;
    }

    while (getline(file, linea)) {
        std::stringstream ss(linea);
        double valorT, valorP;

        if (getline(ss, temp, ';')) {
            try {
                valorT = std::stod(temp);
                if (getline(ss, temp, ';')) {
                    valorP = std::stod(temp);
                    datos.push_back({valorT, valorP});
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error al convertir los datos a double en la línea: " << linea << std::endl;
                continue;
            }
        }
    }

    file.close();
    return true;
}
// Se calculan los coeficientes del ajuste polinómico
std::vector<double> ajustePolinomico(const std::vector<Datos>& datos, double tol) {
    int n = datos.size();
    double C0 = 0, C1 = 0, C2 = 0;
    double C0_new, C1_new, C2_new;
    double error;

    do {
        double sumT = 0, sumT2 = 0, sumT3 = 0, sumT4 = 0;
        double sumP = 0, sumPT = 0, sumPT2 = 0;

        for (const auto& dato : datos) {
            sumT += dato.T;
            sumT2 += dato.T * dato.T;
            sumT3 += dato.T * dato.T * dato.T;
            sumT4 += dato.T * dato.T * dato.T * dato.T;
            sumP += dato.P;
            sumPT += dato.P * dato.T;
            sumPT2 += dato.P * dato.T * dato.T;
        }

        double denom = n * sumT2 * sumT4 + 2 * sumT * sumT3 * sumT2 - sumT2 * sumT2 * sumT2 - n * sumT3 * sumT3 - sumT4 * sumT * sumT;
        C0_new = (sumP * sumT2 * sumT4 + sumPT * sumT3 * sumT2 + sumPT2 * sumT * sumT2 - sumPT2 * sumT2 * sumT2 - sumP * sumT3 * sumT3 - sumT4 * sumPT * sumT) / denom;
        C1_new = (n * sumPT * sumT4 + sumP * sumT3 * sumT2 + sumPT2 * sumT * sumT3 - sumPT2 * sumT2 * sumT2 - n * sumT3 * sumPT - sumP * sumT4 * sumT) / denom;
        C2_new = (n * sumT2 * sumPT2 + sumT * sumT3 * sumP + sumT * sumT2 * sumPT - sumP * sumT2 * sumT2 - n * sumT3 * sumPT - sumT * sumT * sumPT2) / denom;

        error = std::max(std::abs(C0_new - C0), std::max(std::abs(C1_new - C1), std::abs(C2_new - C2)));

        C0 = C0_new;
        C1 = C1_new;
        C2 = C2_new;
    } while (error > tol);

    return {C0, C1, C2};
}

int main() {
    std::vector<Datos> datos;
    std::string archivo = "Libro2.csv";

    if (!leerCSV(archivo, datos)) {
        std::cerr << "No se pudo leer el archivo." << std::endl;
        return 1;
    }

    double tol = 0.00001;
    std::vector<double> coeficientes = ajustePolinomico(datos, tol);

    std::cout << "Coeficientes del ajuste: C0 = " << coeficientes[0] << ", C1 = " << coeficientes[1] << ", C2 = " << coeficientes[2] << std::endl;

    return 0;
}

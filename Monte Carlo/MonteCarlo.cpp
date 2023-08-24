#include <iostream>
#include <cstdlib>
#include <cmath>

template <typename T>
class FuncionMonteCarlo {
public:
    T evaluar(T x) const {
        return (std::pow(x, 4) * std::exp(-x)) / (x + 1);
    }
};

template <typename T>
class EstimadorMonteCarlo {
public:
    EstimadorMonteCarlo(const FuncionMonteCarlo<T>& funcion) : funcion_(funcion) {}

    T estimar(T limiteInferior, T limiteSuperior, int iteraciones) {
        T sumaTotal = 0;

        for (int i = 0; i < iteraciones; i++) {
            T numAleatorio = limiteInferior + (T(std::rand()) / RAND_MAX) * (limiteSuperior - limiteInferior);
            T valorFuncion = funcion_.evaluar(numAleatorio);
            sumaTotal += valorFuncion;
        }

        T estimacion = (limiteSuperior - limiteInferior) * sumaTotal / iteraciones;
        return estimacion;
    }

private:
    const FuncionMonteCarlo<T>& funcion_;
};


int main() {
    FuncionMonteCarlo<double> funcionMonteCarlo;
    EstimadorMonteCarlo<double> estimador(funcionMonteCarlo);

    double limiteInferior;
    double limiteSuperior;
    int iteraciones = 800;

    std::cout << "--Limites de integracion--" << std::endl;
    std::cout << "Limite inferior: ";
    std::cin >> limiteInferior;
    std::cout << "\nLimite superior: ";
    std::cin >> limiteSuperior;

    double estimacion = estimador.estimar(limiteInferior, limiteSuperior, iteraciones);

    std::cout << "Estimación para " << limiteInferior << " -> " << limiteSuperior << " es " << estimacion << " (" << iteraciones << " iteraciones)" << std::endl;

    return 0;
}

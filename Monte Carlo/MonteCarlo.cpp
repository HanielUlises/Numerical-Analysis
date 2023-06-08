#include <iostream>
#include <cstdlib>
#include <cmath>

class FuncionMonteCarlo{
public:
    double evaluar(double x) const{
        return (pow(x, 4) * exp(-x))/(x+1); //Funcion a evaluar con la variable que se toma en cada iteracion
    }
};

class EstimadorMonteCarlo{
public:
    EstimadorMonteCarlo(const FuncionMonteCarlo& funcion) : funcion_(funcion) {}

    double estimar(double limiteInferior, double limiteSuperior, int iteraciones){
        double sumaTotal = 0;

        for (int i = 0; i < iteraciones; i++){
            double numAleatorio = limiteInferior + (double(rand()) / RAND_MAX) * (limiteSuperior - limiteInferior); //Variable Xi aleatoria que varía entre los límites de integración
            double valorFuncion = funcion_.evaluar(numAleatorio); //Evaluacion de la funcion en el punto
            sumaTotal += valorFuncion; 
        }
 
        double estimacion = (limiteSuperior - limiteInferior) * sumaTotal / iteraciones; //Estimacion dada: (b - a) * 1/n * Σf(Xi) i=1 hasta n
        return estimacion;
    }

private:
    const FuncionMonteCarlo& funcion_;
};

int main(){
    FuncionMonteCarlo funcionMonteCarlo;
    EstimadorMonteCarlo estimador(funcionMonteCarlo);

    double limiteInferior; //a
    double limiteSuperior; //b
    int iteraciones = 800; //Aproximaciones varían según la cantidad de operaciones realizadas

    printf("--Limites de integracion--\n");
    printf("Limite inferior: " );
    scanf("%lf", &limiteInferior);
    printf("\nLimite superior: ");
    scanf("%lf", &limiteSuperior);

    double estimacion = estimador.estimar(limiteInferior, limiteSuperior, iteraciones);


    printf("Estimación para %.1f -> %.1f es %.2f, (%i iteraciones)\n",
           limiteInferior, limiteSuperior, estimacion, iteraciones);

    return 0;
}

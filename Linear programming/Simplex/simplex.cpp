#include "simplex.h"
#include <iostream>
#include <limits>

Simplex::Simplex(const std::vector<std::vector<double>> &A, const std::vector<double> &b, const std::vector<double> &c) {
    numConstraints = b.size();
    numVariables = c.size();

    // Create tableau with slack variables
    tableau.resize(numConstraints + 1, std::vector<double>(numVariables + numConstraints + 1, 0));

    // Fill the tableau
    for (int i = 0; i < numConstraints; ++i) {
        for (int j = 0; j < numVariables; ++j) {
            tableau[i][j] = A[i][j];
        }
        tableau[i][numVariables + i] = 1; // Slack variable
        tableau[i].back() = b[i];
    }

    // Objective function row
    for (int j = 0; j < numVariables; ++j) {
        tableau[numConstraints][j] = -c[j];
    }
}

int Simplex::findPivotColumn() {
    int pivotCol = 0;
    double minValue = tableau[numConstraints][0];

    for (int i = 1; i < numVariables + numConstraints; ++i) {
        if (tableau[numConstraints][i] < minValue) {
            minValue = tableau[numConstraints][i];
            pivotCol = i;
        }
    }

    // All coefficients are non-negative, optimal solution found
    if (minValue >= 0) return -1; 
    return pivotCol;
}

int Simplex::findPivotRow(int pivotCol) {
    int pivotRow = -1;
    double minRatio = std::numeric_limits<double>::max();

    for (int i = 0; i < numConstraints; ++i) {
        if (tableau[i][pivotCol] > 0) {
            double ratio = tableau[i].back() / tableau[i][pivotCol];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }

    return pivotRow;
}

void Simplex::pivot(int pivotRow, int pivotCol) {
    double pivotElement = tableau[pivotRow][pivotCol];
    for (int i = 0; i < tableau[0].size(); ++i) {
        tableau[pivotRow][i] /= pivotElement;
    }

    for (int i = 0; i <= numConstraints; ++i) {
        if (i != pivotRow) {
            double factor = tableau[i][pivotCol];
            for (int j = 0; j < tableau[0].size(); ++j) {
                tableau[i][j] -= factor * tableau[pivotRow][j];
            }
        }
    }
}

std::vector<double> Simplex::solve() {
    while (true) {
        int pivotCol = findPivotColumn();
        if (pivotCol == -1) break; // Optimal solution found

        int pivotRow = findPivotRow(pivotCol);
        if (pivotRow == -1) {
            std::cerr << "Unbounded solution." << std::endl;
            return {};
        }

        pivot(pivotRow, pivotCol);
    }

    std::vector<double> solution(numVariables);
    for (int i = 0; i < numVariables; ++i) {
        solution[i] = tableau[i].back();
    }

    return solution;
}

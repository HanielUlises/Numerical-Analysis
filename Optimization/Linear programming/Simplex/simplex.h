#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>

class Simplex {
public:
    Simplex(const std::vector<std::vector<double>>& A, const std::vector<double>& b, const std::vector<double>& c);
    std::vector<double> solve();

private:
    std::vector<std::vector<double>> tableau;
    int numConstraints;
    int numVariables;

    int findPivotColumn();
    int findPivotRow(int pivotCol);
    void pivot(int pivotRow, int pivotCol);
    bool isOptimal();
};

#endif // SIMPLEX_H

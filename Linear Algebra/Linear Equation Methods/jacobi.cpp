#include <iostream>
#include <vector>
#include <cmath>

std::vector<double> jacobi(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double> x, int max_iter) {
    int n = A.size();
    std::vector<double> prev_x = x;

    for (int iter = 0; iter < max_iter; ++iter) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                // Diagonal matrix
                if (i != j) {
                    sum += A[i][j] * prev_x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        prev_x = x; // Update the previous iteration values
    }

    return x;
}

int main() {
    std::vector<std::vector<double>> A = {
        {2, 1, -1},
        {-1, 2, 2},
        {3, 2, -3}
    };
    std::vector<double> b = {3, 8, 2};
    std::vector<double> x0 = {2, 2, 2};
    int max_iter = 25;

    std::vector<double> x = jacobi(A, b, x0, max_iter);

    for (int i = 0; i < x.size(); ++i) {
        std::cout << "x" << i+1 << " = " << x[i] << std::endl;
    }

    return 0;
}

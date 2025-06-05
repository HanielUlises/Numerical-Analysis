#include "interior_point.h"
#include <iostream>

int main() {
    // Example: maximize 3x1 + 5x2
    // Subject to: x1 + x2 = 4
    //             2x1 + x2 = 5
    //             x1, x2 >= 0
    std::vector<std::vector<double>> a = {{1.0, 1.0}, {2.0, 1.0}};
    std::vector<double> b = {4.0, 5.0};
    std::vector<double> c = {3.0, 5.0};

    interior_point solver;
    auto solution = solver.solve(a, b, c);

    if (solution) {
        std::cout << "Solution found:\n";
        for (size_t i = 0; i < solution->size(); ++i) {
            std::cout << "x" << i + 1 << " = " << (*solution)[i] << "\n";
        }
        std::cout << "Objective value: " << solver.get_objective_value() << "\n";
        std::cout << "Feasible: " << (solver.is_feasible() ? "Yes" : "No") << "\n";
    } else {
        std::cout << "No solution found.\n";
    }

    return 0;
}
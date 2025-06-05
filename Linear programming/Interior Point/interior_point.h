#ifndef INTERIOR_POINT_H
#define INTERIOR_POINT_H

#include <span>
#include <vector>
#include <optional>

class interior_point {
private:
    std::vector<std::vector<double>> constraint_matrix; // A in Ax = b
    std::vector<double> rhs; // b in Ax = b
    std::vector<double> objective; // c in c^T * x
    std::vector<double> primal_vars; // x
    std::vector<double> dual_vars; // y
    std::vector<double> slack_vars; // s
    size_t num_vars; // Number of variables
    size_t num_constraints; // Number of constraints
    bool is_solved{false};

    // Helper functions
    void initialize_solution();
    [[nodiscard]] auto compute_residuals() const -> std::tuple<std::vector<double>, std::vector<double>, double>;
    [[nodiscard]] auto solve_newton_system(std::span<const double> primal_res,
                                          std::span<const double> dual_res,
                                          double complementarity) const -> std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>;
    [[nodiscard]] auto compute_step_size(std::span<const double> delta_x,
                                        std::span<const double> delta_s,
                                        double alpha_max) const -> double;

public:
    interior_point() = default;
    [[nodiscard]] auto solve(std::span<const std::vector<double>> a,
                             std::span<const double> b,
                             std::span<const double> c) -> std::optional<std::vector<double>>;
    [[nodiscard]] auto get_objective_value() const -> double;
    [[nodiscard]] auto is_feasible() const -> bool;
};

#endif // INTERIOR_POINT_H
#include "interior_point.h"
#include <algorithm>
#include <stdexcept>
#include <ranges>
#include <numeric>
#include <cmath>

namespace {
    constexpr double TOLERANCE = 1e-8;
    constexpr double ALPHA_MAX = 0.95;
    constexpr double SIGMA = 0.1;
    constexpr size_t MAX_ITERATIONS = 100;
}

void interior_point::initialize_solution() {
    primal_vars.assign(num_vars, 1.0);
    dual_vars.assign(num_constraints, 1.0);
    slack_vars.assign(num_vars, 1.0);
}

auto interior_point::compute_residuals() const -> std::tuple<std::vector<double>, std::vector<double>, double> {
    std::vector<double> primal_residual(num_constraints, 0.0);
    std::vector<double> dual_residual(num_vars, 0.0);
    double complementarity = 0.0;

    // Primal residual: r_p = Ax - b
    for (size_t i = 0; i < num_constraints; ++i) {
        primal_residual[i] = -rhs[i];
        for (size_t j = 0; j < num_vars; ++j) {
            primal_residual[i] += constraint_matrix[i][j] * primal_vars[j];
        }
    }

    // Dual residual: r_d = A^T y + s - c
    for (size_t j = 0; j < num_vars; ++j) {
        dual_residual[j] = -objective[j] + slack_vars[j];
        for (size_t i = 0; i < num_constraints; ++i) {
            dual_residual[j] += constraint_matrix[i][j] * dual_vars[i];
        }
    }

    // Complementarity: mu = x^T s / n
    complementarity = std::inner_product(primal_vars.begin(), primal_vars.end(),
                                        slack_vars.begin(), 0.0) / num_vars;

    return {primal_residual, dual_residual, complementarity};
}

auto interior_point::compute_step_size(std::span<const double> delta_x,
                                      std::span<const double> delta_s,
                                      double alpha_max) const -> double {
    double alpha = alpha_max;
    for (size_t i = 0; i < num_vars; ++i) {
        if (delta_x[i] < 0) {
            alpha = std::min(alpha, -primal_vars[i] / delta_x[i]);
        }
        if (delta_s[i] < 0) {
            alpha = std::min(alpha, -slack_vars[i] / delta_s[i]);
        }
    }
    return alpha;
}

// Simplified Newton system solver (assumes A has full row rank)
auto interior_point::solve_newton_system(std::span<const double> primal_res,
                                        std::span<const double> dual_res,
                                        double complementarity) const -> std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> {
    std::vector<double> delta_x(num_vars, 0.0);
    std::vector<double> delta_y(num_constraints, 0.0);
    std::vector<double> delta_s(num_vars, 0.0);

    // Simplified: solve (A A^T) delta_y = A r_d - r_p
    // Then compute delta_x, delta_s
    std::vector<std::vector<double>> ata(num_constraints, std::vector<double>(num_constraints, 0.0));
    std::vector<double> rhs_newton(num_constraints, 0.0);

    for (size_t i = 0; i < num_constraints; ++i) {
        for (size_t j = 0; j < num_constraints; ++j) {
            for (size_t k = 0; k < num_vars; ++k) {
                ata[i][j] += constraint_matrix[i][k] * constraint_matrix[j][k];
            }
        }
        rhs_newton[i] = -primal_res[i];
        for (size_t k = 0; k < num_vars; ++k) {
            rhs_newton[i] += constraint_matrix[i][k] * dual_res[k];
        }
    }

    // Solve linear system (using simple Gaussian elimination for demo)
    for (size_t i = 0; i < num_constraints; ++i) {
        size_t pivot = i;
        for (size_t k = i + 1; k < num_constraints; ++k) {
            if (std::abs(ata[k][i]) > std::abs(ata[pivot][i])) {
                pivot = k;
            }
        }
        std::swap(ata[i], ata[pivot]);
        std::swap(rhs_newton[i], rhs_newton[pivot]);

        double pivot_val = ata[i][i];
        if (std::abs(pivot_val) < TOLERANCE) {
            throw std::runtime_error("singular matrix in newton system");
        }

        for (size_t j = i; j < num_constraints; ++j) {
            ata[i][j] /= pivot_val;
        }
        rhs_newton[i] /= pivot_val;

        for (size_t k = 0; k < num_constraints; ++k) {
            if (k != i) {
                double factor = ata[k][i];
                for (size_t j = i; j < num_constraints; ++j) {
                    ata[k][j] -= factor * ata[i][j];
                }
                rhs_newton[k] -= factor * rhs_newton[i];
            }
        }
    }

    delta_y = rhs_newton;

    // Compute delta_x and delta_s
    for (size_t j = 0; j < num_vars; ++j) {
        delta_x[j] = dual_res[j];
        for (size_t i = 0; i < num_constraints; ++i) {
            delta_x[j] -= constraint_matrix[i][j] * delta_y[i];
        }
        delta_s[j] = SIGMA * complementarity / primal_vars[j] - slack_vars[j] * delta_x[j] / primal_vars[j] - dual_res[j];
    }

    return {delta_x, delta_y, delta_s};
}

auto interior_point::solve(std::span<const std::vector<double>> a,
                           std::span<const double> b,
                           std::span<const double> c) -> std::optional<std::vector<double>> {
    if (a.empty() || b.empty() || c.empty() || a[0].empty()) {
        throw std::invalid_argument("empty input matrices or vectors");
    }
    if (a.size() != b.size() || a[0].size() != c.size()) {
        throw std::invalid_argument("incompatible dimensions");
    }
    for (const auto& row : a) {
        if (row.size() != c.size()) {
            throw std::invalid_argument("inconsistent constraint matrix dimensions");
        }
    }

    num_constraints = a.size();
    num_vars = c.size();
    constraint_matrix = a | std::ranges::to<std::vector<std::vector<double>>>();
    rhs = b | std::ranges::to<std::vector<double>>();
    objective = c | std::ranges::to<std::vector<double>>();

    initialize_solution();

    for (size_t iter = 0; iter < MAX_ITERATIONS; ++iter) {
        auto [primal_res, dual_res, mu] = compute_residuals();
        
        // Check convergence
        double primal_norm = std::ranges::max(std::ranges::transform_view(primal_res, [](double x) { return std::abs(x); }));
        double dual_norm = std::ranges::max(std::ranges::transform_view(dual_res, [](double x) { return std::abs(x); }));
        if (primal_norm < TOLERANCE && dual_norm < TOLERANCE && mu < TOLERANCE) {
            is_solved = true;
            return primal_vars;
        }

        // Solve Newton system
        auto [delta_x, delta_y, delta_s] = solve_newton_system(primal_res, dual_res, mu);

        // Compute step size and update
        double alpha = compute_step_size(delta_x, delta_s, ALPHA_MAX);
        for (size_t i = 0; i < num_vars; ++i) {
            primal_vars[i] += alpha * delta_x[i];
            slack_vars[i] += alpha * delta_s[i];
        }
        for (size_t i = 0; i < num_constraints; ++i) {
            dual_vars[i] += alpha * delta_y[i];
        }
    }

    return std::nullopt; // No convergence
}

auto interior_point::get_objective_value() const -> double {
    if (!is_solved) {
        throw std::runtime_error("problem not solved");
    }
    return std::inner_product(primal_vars.begin(), primal_vars.end(), objective.begin(), 0.0);
}

auto interior_point::is_feasible() const -> bool {
    if (!is_solved) {
        return false;
    }
    for (double x : primal_vars) {
        if (x < -TOLERANCE) return false;
    }
    std::vector<double> ax(num_constraints, 0.0);
    for (size_t i = 0; i < num_constraints; ++i) {
        for (size_t j = 0; j < num_vars; ++j) {
            ax[i] += constraint_matrix[i][j] * primal_vars[j];
        }
        if (std::abs(ax[i] - rhs[i]) > TOLERANCE) {
            return false;
        }
    }
    return true;
}
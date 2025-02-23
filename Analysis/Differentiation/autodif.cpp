#include "autodiff.h"

// ---------- Variable Implementation ----------

template <typename T>
Variable<T>::Variable(T value) : value(value) {}

template <typename T>
ValueAndPartial<T> Variable<T>::evaluateAndDerive(Variable<T>* variable) {
    T partial = (this == variable) ? static_cast<T>(1) : static_cast<T>(0);
    return { value, partial };
}

// ---------- Plus Implementation ----------

template <typename T, typename... Ops>
Plus<T, Ops...>::Plus(Ops... ops) : operands(ops...) {
    static_assert((std::is_same_v<Ops, Expression<T>*> && ...),
                  "All operands must be Expression<T>*");
}

template <typename T, typename... Ops>
ValueAndPartial<T> Plus<T, Ops...>::evaluateAndDerive(Variable<T>* variable) {
    ValueAndPartial<T> result{ static_cast<T>(0), static_cast<T>(0) };
    std::apply([&](auto... ops) {
        (([&] {
            auto temp = ops->evaluateAndDerive(variable);
            result.value += temp.value;
            result.partial += temp.partial;
        }()), ...);
    }, operands);
    return result;
}

// ---------- Multiply Implementation ----------

template <typename T, typename... Ops>
Multiply<T, Ops...>::Multiply(Ops... ops) : operands(ops...) {
    static_assert((std::is_same_v<Ops, Expression<T>*> && ...),
                  "All operands must be Expression<T>*");
}

template <typename T, typename... Ops>
ValueAndPartial<T> Multiply<T, Ops...>::evaluateAndDerive(Variable<T>* variable) {
    constexpr std::size_t N = sizeof...(Ops);

    // Evaluate every operand exactly once; store in an array.
    auto evals = std::apply([&](auto*... ops) -> std::array<ValueAndPartial<T>, N> {
        return { ops->evaluateAndDerive(variable)... };
    }, operands);

    // Product of all operand values.
    T prod = static_cast<T>(1);
    for (const auto& ev : evals)
        prod *= ev.value;

    // Derivative using the product rule:
    // ∂(f₁f₂...fₙ)/∂x = Σ[i=1..n] ( (∏[j≠i] fⱼ) * (∂fᵢ/∂x) )
    T deriv = static_cast<T>(0);
    for (std::size_t i = 0; i < evals.size(); ++i) {
        T term = evals[i].partial;
        for (std::size_t j = 0; j < evals.size(); ++j) {
            if (i != j)
                term *= evals[j].value;
        }
        deriv += term;
    }
    return { prod, deriv };
}

// ---------- Explicit Template Instantiations ----------

template struct Variable<float>;
template struct Variable<double>;

template struct Plus<float, Expression<float>*, Expression<float>*>;
template struct Plus<double, Expression<double>*, Expression<double>*>;
  
template struct Multiply<float, Expression<float>*, Expression<float>*>;
template struct Multiply<double, Expression<double>*, Expression<double>*>;

#ifndef AUTODIFF_H
#define AUTODIFF_H

#include <tuple>
#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

template <typename T>
struct ValueAndPartial {
    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>,
                  "Only float and double are supported.");
    T value, partial;
};

template <typename T>
struct Variable; 

template <typename T>
struct Expression {
    virtual ~Expression() = default;
    virtual ValueAndPartial<T> evaluateAndDerive(Variable<T>* variable) = 0;
};

// An independent variable
template <typename T>
struct Variable : public Expression<T> {
    T value;
    explicit Variable(T value);
    ValueAndPartial<T> evaluateAndDerive(Variable<T>* variable) override;
};

// Plus 
template <typename T, typename... Ops>
struct Plus : public Expression<T> {
    std::tuple<Ops...> operands;
    explicit Plus(Ops... ops);
    ValueAndPartial<T> evaluateAndDerive(Variable<T>* variable) override;
};

// Multiply
// It implements the product rule for the derivative.
template <typename T, typename... Ops>
struct Multiply : public Expression<T> {
    std::tuple<Ops...> operands;
    explicit Multiply(Ops... ops);
    ValueAndPartial<T> evaluateAndDerive(Variable<T>* variable) override;
};

#endif // AUTODIFF_H

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>
#include <cmath>
#include <cassert>

template<typename T>
class Vector2D {
public:
    static const Vector2D<T> zero;

    Vector2D() : Vector2D(0, 0) {}
    Vector2D(T x, T y) : mX(x), mY(y) {}

    inline void setX(T x) { mX = x; }
    inline void setY(T y) { mY = y; }

    inline T getX() const { return mX; }
    inline T getY() const { return mY; }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& consoleOut, const Vector2D<U>& vector);

    bool operator==(const Vector2D<T>& Vect) const;
    bool operator!=(const Vector2D<T>& Vect) const;

    Vector2D<T> operator-() const;
    Vector2D<T> operator*(T scale) const;
    Vector2D<T> operator/(T scale) const;
    Vector2D<T>& operator*=(T scale);
    Vector2D<T>& operator/=(T scale);

    Vector2D<T> operator+(const Vector2D<T>& vec) const;
    Vector2D<T> operator-(const Vector2D<T>& vec) const;
    Vector2D<T>& operator+=(const Vector2D<T>& vec);
    Vector2D<T>& operator-=(const Vector2D<T>& vec);

    T Magnitude() const;
    Vector2D<T> getUnitVect() const;
    Vector2D<T>& normalizeVect();

    T distance(const Vector2D<T>& vec) const;
    T dotProduct(const Vector2D<T>& vec) const;
    T crossProduct(const Vector2D<T>& vec) const;
    T angleBetween(const Vector2D<T>& vec2) const;
    Vector2D<T> projectOnto(const Vector2D<T>& vec) const;
    Vector2D<T> reflect(const Vector2D<T>& normal) const;
    void rotate(T angle, const Vector2D<T>& aroundPoint);
    void clampMagnitude(T maxMagnitude);
    Vector2D<T> rotation(T angle, const Vector2D<T>& aroundPoint) const;
    static Vector2D<T> lerp(const Vector2D<T>& a, const Vector2D<T>& b, T t);
    static T angleTo(const Vector2D<T>& from, const Vector2D<T>& to);

    template<typename U>
    friend Vector2D<U> operator*(U scalar, const Vector2D<U>& vect);

private:
    T mX, mY;
};

template<typename T>
const Vector2D<T> Vector2D<T>::zero = Vector2D<T>(0, 0);

#endif

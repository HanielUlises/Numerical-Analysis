#include "Vector2D.h"
#include "Utils.h"
#include <cmath>
#include <cassert>

template<typename T>
std::ostream& operator<<(std::ostream& consoleOut, const Vector2D<T>& vector) {
    consoleOut << "X: " << vector.mX << " Y: " << vector.mY << std::endl;
    return consoleOut;
}

template<typename T>
bool Vector2D<T>::operator==(const Vector2D<T>& Vect) const {
    return std::fabs(mX - Vect.mX) < std::numeric_limits<T>::epsilon() && 
           std::fabs(mY - Vect.mY) < std::numeric_limits<T>::epsilon();
}

template<typename T>
bool Vector2D<T>::operator!=(const Vector2D<T>& Vect) const {
    return !(*this == Vect);
}

template<typename T>
Vector2D<T> Vector2D<T>::operator-() const {
    return Vector2D<T>(-mX, -mY);
}

template<typename T>
Vector2D<T> Vector2D<T>::operator*(T scale) const {
    return Vector2D<T>(mX * scale, mY * scale);
}

template<typename T>
Vector2D<T> Vector2D<T>::operator/(T scale) const {
    assert(std::fabs(scale) > std::numeric_limits<T>::epsilon());
    return Vector2D<T>(mX / scale, mY / scale);
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator*=(T scale) {
    *this = *this * scale;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator/=(T scale) {
    assert(std::fabs(scale) > std::numeric_limits<T>::epsilon());
    *this = *this / scale;
    return *this;
}

template<typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& vec) const {
    return Vector2D<T>(mX + vec.mX, mY + vec.mY);
}

template<typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& vec) const {
    return Vector2D<T>(mX - vec.mX, mY - vec.mY);
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<T>& vec) {
    *this = *this + vec;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<T>& vec) {
    *this = *this - vec;
    return *this;
}

template<typename T>
T Vector2D<T>::Magnitude() const {
    return std::sqrt((mX * mX) + (mY * mY));
}

template<typename T>
Vector2D<T> Vector2D<T>::getUnitVect() const {
    T magnitude = Magnitude();

    if (magnitude > std::numeric_limits<T>::epsilon()) {
        return *this / magnitude;
    }

    return Vector2D<T>::zero;
}

template<typename T>
Vector2D<T>& Vector2D<T>::normalizeVect() {
    T magnitude = Magnitude();
    if (magnitude > std::numeric_limits<T>::epsilon()) {
        *this /= magnitude;
    }

    return *this;
}

template<typename T>
T Vector2D<T>::distance(const Vector2D<T>& vec) const {
    return (vec - *this).Magnitude();
}

template<typename T>
T Vector2D<T>::dotProduct(const Vector2D<T>& vec) const {
    return (mX * vec.mX) + (mY * vec.mY);
}

template<typename T>
T Vector2D<T>::crossProduct(const Vector2D<T>& vec) const {
    return (mX * vec.mY) - (mY * vec.mX);
}

template<typename T>
T Vector2D<T>::angleBetween(const Vector2D<T>& vec2) const {
    return std::acos(getUnitVect().dotProduct(vec2.getUnitVect()));
}

template<typename T>
Vector2D<T> Vector2D<T>::projectOnto(const Vector2D<T>& vec) const {
    Vector2D<T> unitVec2 = vec.getUnitVect();

    T magnitude2 = vec.Magnitude();

    if (magnitude2 <= std::numeric_limits<T>::epsilon()) {
        return Vector2D<T>::zero;
    }
    T dot = dotProduct(vec);
    return unitVec2 * dot;
}

template<typename T>
Vector2D<T> Vector2D<T>::reflect(const Vector2D<T>& normal) const {
    return *this - 2 * projectOnto(normal);
}

template<typename T>
void Vector2D<T>::rotate(T angle, const Vector2D<T>& aroundPoint) {
    T cosine = std::cos(angle);
    T sine = std::sin(angle);

    Vector2D<T> thisVector(mX, mY);

    thisVector -= aroundPoint;

    T xRot = thisVector.mX * cosine - thisVector.mY * sine;
    T yRot = thisVector.mX * sine + thisVector.mY * cosine;

    Vector2D<T> rotated = Vector2D<T>(xRot, yRot);
    *this = rotated + aroundPoint;
}

template<typename T>
Vector2D<T> Vector2D<T>::rotation(T angle, const Vector2D<T>& aroundPoint) const {
    T cosine = std::cos(angle);
    T sine = std::sin(angle);

    Vector2D<T> thisVector(mX, mY);

    thisVector -= aroundPoint;

    T xRot = thisVector.mX * cosine - thisVector.mY * sine;
    T yRot = thisVector.mX * sine + thisVector.mY * cosine;

    Vector2D<T> rotated = Vector2D<T>(xRot, yRot);
    return rotated + aroundPoint;
}

template<typename T>
void Vector2D<T>::clampMagnitude(T maxMagnitude) {
    T mag = Magnitude();
    if (mag > maxMagnitude) {
        T scale = maxMagnitude / mag;
        *this *= scale;
    }
}

template<typename T>
Vector2D<T> Vector2D<T>::lerp(const Vector2D<T>& a, const Vector2D<T>& b, T t) {
    return a + t * (b - a);
}

template<typename T>
T Vector2D<T>::angleTo(const Vector2D<T>& from, const Vector2D<T>& to) {
    return std::atan2(to.mY - from.mY, to.mX - from.mX);
}

template<typename T>
Vector2D<T> operator*(T scalar, const Vector2D<T>& vect) {
    return Vector2D<T>(vect.mX * scalar, vect.mY * scalar);
}

template class Vector2D<float>;
template class Vector2D<double>;
template std::ostream& operator<< <float>(std::ostream&, const Vector2D<float>&);
template std::ostream& operator<< <double>(std::ostream&, const Vector2D<double>&);
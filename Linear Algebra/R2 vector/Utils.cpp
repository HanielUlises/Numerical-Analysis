#include "Vector2D.h"
#include "Utils.h"
#include <cmath>
#include <cassert>

bool isEqual(float x, float y) {
    return fabs(x - y) < EPSILON;
}

bool isGreaterThanOrEqual(float x, float y) {
    return x > y || isEqual(x, y);
}

bool isLessThanOrEqual(float x, float y) {
    return x < y || isEqual(x, y);
}

Vector2D operator*(float scalar, const Vector2D& vect) {
    return vect * scalar;
}

std::ostream& operator<<(std::ostream& consoleOut, const Vector2D& vector) {
    consoleOut << "(" << vector.getX() << ", " << vector.getY() << ")";
    return consoleOut;
}

bool Vector2D::operator==(const Vector2D& Vect) const {
    return isEqual(mX, Vect.mX) && isEqual(mY, Vect.mY);
}

bool Vector2D::operator!=(const Vector2D& Vect) const {
    return !(*this == Vect);
}

Vector2D Vector2D::operator-() const {
    return Vector2D(-mX, -mY);
}

Vector2D Vector2D::operator*(float scale) const {
    return Vector2D(mX * scale, mY * scale);
}

Vector2D Vector2D::operator/(float scale) const {
    assert(fabs(scale) > EPSILON);
    return Vector2D(mX / scale, mY / scale);
}

Vector2D& Vector2D::operator*=(float scale) {
    mX *= scale;
    mY *= scale;
    return *this;
}

Vector2D& Vector2D::operator/=(float scale) {
    assert(fabs(scale) > EPSILON);
    mX /= scale;
    mY /= scale;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec) const {
    return Vector2D(mX + vec.mX, mY + vec.mY);
}

Vector2D Vector2D::operator-(const Vector2D& vec) const {
    return Vector2D(mX - vec.mX, mY - vec.mY);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    mX += vec.mX;
    mY += vec.mY;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    mX -= vec.mX;
    mY -= vec.mY;
    return *this;
}

float Vector2D::Magnitude() const {
    return sqrt((mX * mX) + (mY * mY));
}

Vector2D Vector2D::getUnitVect() const {
    float magnitude = Magnitude();
    if (magnitude > EPSILON) {
        return *this / magnitude;
    }
    return Vector2D::zero;
}

Vector2D& Vector2D::normalizeVect() {
    float magnitude = Magnitude();
    if (magnitude > EPSILON) {
        *this /= magnitude;
    }
    return *this;
}

float Vector2D::distance(const Vector2D& vec) const {
    return (*this - vec).Magnitude();
}

float Vector2D::dotProduct(const Vector2D& vec) const {
    return (mX * vec.mX) + (mY * vec.mY);
}

float Vector2D::crossProduct(const Vector2D& vec) const {
    return mX * vec.mY - mY * vec.mX;
}

Vector2D Vector2D::projectOnto(const Vector2D& vec) const {
    Vector2D unitVec = vec.getUnitVect();
    float dot = dotProduct(unitVec);
    return unitVec * dot;
}

float Vector2D::angleBetween(const Vector2D& vec2) const {
    return acosf(getUnitVect().dotProduct(vec2.getUnitVect()));
}

float Vector2D::angleTo(const Vector2D& from, const Vector2D& to) {
    float dot = from.dotProduct(to);
    float det = from.crossProduct(to);
    return atan2(det, dot);
}

Vector2D Vector2D::reflect(const Vector2D& normal) const {
    return *this - 2 * projectOnto(normal);
}

void Vector2D::rotate(float angle, const Vector2D& aroundPoint) {
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vector2D thisVector(mX, mY);
    thisVector -= aroundPoint;

    float xRot = thisVector.mX * cosine - thisVector.mY * sine;
    float yRot = thisVector.mX * sine + thisVector.mY * cosine;

    *this = Vector2D(xRot, yRot) + aroundPoint;
}

Vector2D Vector2D::rotation(float angle, const Vector2D& aroundPoint) const {
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vector2D thisVector(mX, mY);
    thisVector -= aroundPoint;

    float xRot = thisVector.mX * cosine - thisVector.mY * sine;
    float yRot = thisVector.mX * sine + thisVector.mY * cosine;

    return Vector2D(xRot, yRot) + aroundPoint;
}

void Vector2D::clampMagnitude(float maxMagnitude) {
    float mag = Magnitude();
    if (mag > maxMagnitude) {
        float scale = maxMagnitude / mag;
        *this *= scale;
    }
}

Vector2D Vector2D::lerp(const Vector2D& a, const Vector2D& b, float t) {
    return a + t * (b - a);
}

Vector2D Vector2D::orthogonal() const {
    return Vector2D(-mY, mX);
}
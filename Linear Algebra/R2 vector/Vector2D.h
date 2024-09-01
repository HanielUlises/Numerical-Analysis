#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>

class Vector2D {
public:
    static const Vector2D zero;

    // Constructors
    Vector2D() : Vector2D(0, 0) {}
    Vector2D(float x, float y) : mX(x), mY(y) {}

    // Setters
    inline void setX(float x) { mX = x; }
    inline void setY(float y) { mY = y; }

    // Getters
    inline float getX() const { return mX; }
    inline float getY() const { return mY; }

    // Friend function to enable outputting to streams
    friend std::ostream& operator<<(std::ostream& consoleOut, const Vector2D& vector);

    // Comparison operators
    bool operator==(const Vector2D &Vect) const;
    bool operator!=(const Vector2D &Vect) const;

    // Unary operators
    Vector2D operator-() const;

    // Scalar multiplication and division
    Vector2D operator*(float scale) const;
    Vector2D operator/(float scale) const;
    Vector2D& operator*=(float scale);
    Vector2D& operator/=(float scale);

    // Vector addition and subtraction
    Vector2D operator+(const Vector2D& vec) const;
    Vector2D operator-(const Vector2D& vec) const;
    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);

    // Magnitude and normalization
    float Magnitude() const;
    Vector2D getUnitVect() const;
    Vector2D& normalizeVect();

    // Distance and angle
    float distance(const Vector2D& vec) const;
    float dotProduct(const Vector2D& vec) const;
    float crossProduct(const Vector2D& vec) const;
    float angleBetween(const Vector2D& vec2) const;
    static float angleTo(const Vector2D& from, const Vector2D& to);

    // Projection, reflection, and rotation
    Vector2D projectOnto(const Vector2D& vec) const;
    Vector2D reflect(const Vector2D& normal) const;
    void rotate(float angle, const Vector2D& aroundPoint);
    Vector2D rotation(float angle, const Vector2D& aroundPoint) const;

    // Clamp magnitude
    void clampMagnitude(float maxMagnitude);

    // Linear interpolation
    static Vector2D lerp(const Vector2D& a, const Vector2D& b, float t);

    // Orthogonal vector
    Vector2D orthogonal() const;

    // Operator for scalar multiplication
    friend Vector2D operator*(float scalar, const Vector2D& vect);

private:
    float mX, mY;
};

#endif /* VECTOR2D_H_ */
/*
 * Utils.cpp
 *
 *  Created on: 16 jul 2023
 *      Author: Haniel
 */
#include "Vector2D.h"
#include "Utils.h"
#include "cmath"
#include "cassert"

bool isEqual (float x, float y){
	return fabs(x- y )< EPSILON;
}

Vector2D operator*(float scalar, const Vector2D& vect){
	return vect * scalar;
}

bool isGreaterThanOrEqual (float x, float y){
	return x > y || isEqual (x,y);
}

bool isLessThanOrEqual (float x, float y){
	return x < y || isEqual (x, y);
}

bool Vector2D::operator==(const Vector2D& Vect) const{
	return isEqual(mX, Vect.mX) && isEqual(mY, Vect.mY);
}

bool Vector2D::operator!=(const Vector2D& Vect) const{
	return !(*this == Vect);
}
//Negation of a vector (All the elements get negated when applied)
Vector2D Vector2D::operator-() const{
	return Vector2D(-mX, -mY);
}
//Vector multiplication by a scalar
Vector2D Vector2D::operator*(float scale) const{
	return Vector2D (mX * scale, mY* scale);
}
//Dividing by some scalar
Vector2D Vector2D::operator/(float scale)const{
	assert(fabs(scale)>EPSILON);
	return Vector2D (mX/scale, mY/scale);
}
Vector2D& Vector2D::operator*=(float scale){
	*this = *this *scale;
	return *this;
}
Vector2D& Vector2D::operator/=(float scale){
	assert(fabs(scale)>EPSILON);
	*this = *this/scale;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec) const{
	return Vector2D(mX + vec.mX, mY + vec.mY);
}

Vector2D Vector2D::operator-(const Vector2D& vec) const{
	return Vector2D(mX - vec.mX, mY - vec.mY);
}

Vector2D Vector2D::operator+=(const Vector2D& vec){
	*this = *this + vec;
	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D& vec){
	*this = *this - vec;
	return *this;
}

float Vector2D::Magnitude () const{
	return sqrt((mX*mX) + (mY*mY));
}

Vector2D Vector2D::getUnitVect () const{
	float magnitude = Magnitude();

	if (magnitude > EPSILON){
		return *this/magnitude;
	}

	return Vector2D::zero;
}

Vector2D& Vector2D::normalizeVect () {
	float magnitude = Magnitude();
	if(magnitude > EPSILON){
		*this /= magnitude;
	}

	return *this;
}

float Vector2D::distance (const Vector2D& vec) const{
	return (vec - *this).Magnitude();
}

float Vector2D::dotProduct(const Vector2D& vec) const{
	return (mX * vec.mX) + (mY * vec.mY);
}

Vector2D Vector2D::projectOnto (const Vector2D& vec2) const{
	Vector2D unitVec2 = vec2.getUnitVect();

	float magnitude2 = vec2.Magnitude();

	if(isLessThanOrEqual(magnitude2, EPSILON)){
		return Vector2D::zero;
	}
	float dot = dotProduct(vec2);
	return unitVec2 * dot;
}

float Vector2D::angleBetween (const Vector2D& vec2) const{
	return acosf(getUnitVect().dotProduct(vec2.getUnitVect()));
}

Vector2D Vector2D::reflect(const Vector2D& normal) const{
	return *this - 2 * projectOnto(normal);
}

void Vector2D::rotate (float angle, const Vector2D& aroundPoint){
	float cosine  = cosf(angle);
	float sine = sinf(angle);

	Vector2D thisVector(mX, mY);

	thisVector -= aroundPoint;

	float xRot = thisVector.mX * cosine - thisVector.mY * sine;
	float yRot = thisVector.mX * sine + thisVector.mY * cosine;

	Vector2D rotated = Vector2D(xRot, yRot);
	*this = rotated + aroundPoint;
}

Vector2D Vector2D::rotation (float angle, const Vector2D& aroundPoint) const{
		float cosine  = cosf(angle);
	float sine = sinf(angle);

	Vector2D thisVector(mX, mY);

	thisVector -= aroundPoint;

	float xRot = thisVector.mX * cosine - thisVector.mY * sine;
	float yRot = thisVector.mX * sine + thisVector.mY * cosine;

	Vector2D rotated = Vector2D(xRot, yRot);
	return rotated + aroundPoint;
}

void Vector2D::clampMagnitude(float maxMagnitude) {
    float mag = Magnitude();
    if (mag > maxMagnitude) {
        float scale = maxMagnitude / mag;
        mX *= scale;
        mY *= scale;
    }
}

static float Vector2D::(const Vector2D& from, const Vector2D& to) {
    float dot = from.dotProduct(to);
    float det = from.crossProduct(to);
    return atan2(det, dot);
}

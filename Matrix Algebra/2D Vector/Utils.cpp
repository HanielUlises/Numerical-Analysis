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




/*
 * Vector2D.h
 *
 *  Created on: 16 jul 2023
 *      Author: Haniel
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>

class Vector2D{
public:
	static const Vector2D zero;

	Vector2D() : Vector2D(0, 0){}
	Vector2D(float x, float y) : mX(x), mY(y){}

	inline void setX (float x) {mX = x;}
	inline void setY (float y) {mY = y;}

	inline float getX () const {return mX;}
	inline float getY () const {return mY;}

	friend void operator<< (std::ostream & consoleOut, const Vector2D& vector);

	bool operator== (const Vector2D &Vect) const;
	bool operator!= (const Vector2D &Vect) const;

	Vector2D operator-() const;
	Vector2D operator*(float scale) const;
	Vector2D operator/(float scale) const;
	Vector2D& operator*= (float scale);
	Vector2D& operator/= (float scale);

	friend Vector2D operator*(float scalar, const Vector2D& vect);

private:
	float mX, mY;
};



#endif /* VECTOR2D_H_ */

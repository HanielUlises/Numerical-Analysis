/*
 * Vector2D.cpp
 *
 *  Created on: 16 jul 2023
 *      Author: Haniel
 */
#include "Vector2D.h"


void operator<<(std::ostream & consoleOut, const Vector2D& vector){
	consoleOut << "X: "<<vector.mX<<" Y: "<<vector.mY<< std::endl;
}

int main() {
	Vector2D aVector(2, 8);
	Vector2D resultVector = -4*aVector;
	std::cout<<resultVector;
	return 0;
}

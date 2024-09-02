#include <iostream>
#include "Vector2D.h"

int main() {
    // Float datatypes (testing templates)
    Vector2D<float> vecFloat1(2.0f, 8.0f);
    Vector2D<float> vecFloat2(3.0f, -4.0f);

    Vector2D<float> negatedVecFloat = -vecFloat1;
    std::cout << "Negated vecFloat1: " << negatedVecFloat;

    Vector2D<float> scaledUpVecFloat = 2.0f * vecFloat1;
    Vector2D<float> scaledDownVecFloat = vecFloat1 / 2.0f;
    std::cout << "Scaled up vecFloat1 (by 2): " << scaledUpVecFloat;
    std::cout << "Scaled down vecFloat1 (by 2): " << scaledDownVecFloat;

    Vector2D<float> sumVecFloat = vecFloat1 + vecFloat2;
    Vector2D<float> diffVecFloat = vecFloat1 - vecFloat2;
    std::cout << "Sum of vecFloat1 and vecFloat2: " << sumVecFloat;
    std::cout << "Difference between vecFloat1 and vecFloat2: " << diffVecFloat;

    float magnitudeVecFloat1 = vecFloat1.Magnitude();
    std::cout << "Magnitude of vecFloat1: " << magnitudeVecFloat1 << std::endl;

    Vector2D<float> unitVecFloat = vecFloat1.getUnitVect();
    std::cout << "Unit vector of vecFloat1: " << unitVecFloat;

    // Double datatypes (testing templates)
    Vector2D<double> vecDouble1(123.456789, -987.654321);
    Vector2D<double> vecDouble2(-456.123456, 321.654987);

    Vector2D<double> negatedVecDouble = -vecDouble1;
    std::cout << "Negated vecDouble1: " << negatedVecDouble;

    Vector2D<double> scaledUpVecDouble = 2.5 * vecDouble1;
    Vector2D<double> scaledDownVecDouble = vecDouble1 / 2.5;
    std::cout << "Scaled up vecDouble1 (by 2.5): " << scaledUpVecDouble;
    std::cout << "Scaled down vecDouble1 (by 2.5): " << scaledDownVecDouble;

    Vector2D<double> sumVecDouble = vecDouble1 + vecDouble2;
    Vector2D<double> diffVecDouble = vecDouble1 - vecDouble2;
    std::cout << "Sum of vecDouble1 and vecDouble2: " << sumVecDouble;
    std::cout << "Difference between vecDouble1 and vecDouble2: " << diffVecDouble;

    double magnitudeVecDouble1 = vecDouble1.Magnitude();
    std::cout << "Magnitude of vecDouble1: " << magnitudeVecDouble1 << std::endl;

    Vector2D<double> unitVecDouble = vecDouble1.getUnitVect();
    std::cout << "Unit vector of vecDouble1: " << unitVecDouble;

    return 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& consoleOut, const Vector2D<T>& vector) {
    consoleOut << "X: " << vector.getX() << " Y: " << vector.getY();
    return consoleOut;
}

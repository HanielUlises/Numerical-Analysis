#include "Vector2D.h"

std::ostream& operator<<(std::ostream& consoleOut, const Vector2D& vector) {
    consoleOut << "X: " << vector.getX() << " Y: " << vector.getY() << std::endl;
    return consoleOut;
}


int main() {
    // Create some Vector2D objects
    Vector2D vec1(2, 8);
    Vector2D vec2(3, -4);
    Vector2D vec3(1, 1);

    // Test negation
    Vector2D negatedVec = -vec1;
    std::cout << "Negated vec1: " << negatedVec;

    // Test scalar multiplication and division
    Vector2D scaledUpVec = 2 * vec1;
    Vector2D scaledDownVec = vec1 / 2;
    std::cout << "Scaled up vec1 (by 2): " << scaledUpVec;
    std::cout << "Scaled down vec1 (by 2): " << scaledDownVec;

    // Test addition and subtraction
    Vector2D sumVec = vec1 + vec2;
    Vector2D diffVec = vec1 - vec2;
    std::cout << "Sum of vec1 and vec2: " << sumVec;
    std::cout << "Difference between vec1 and vec2: " << diffVec;

    // Test magnitude
    float magnitudeVec1 = vec1.Magnitude();
    std::cout << "Magnitude of vec1: " << magnitudeVec1 << std::endl;

    // Test normalization
    Vector2D unitVec = vec1.getUnitVect();
    std::cout << "Unit vector of vec1: " << unitVec;

    // Test dot product
    float dotProd = vec1.dotProduct(vec2);
    std::cout << "Dot product of vec1 and vec2: " << dotProd << std::endl;

    // Test cross product
    float crossProd = vec1.crossProduct(vec2);
    std::cout << "Cross product of vec1 and vec2: " << crossProd << std::endl;

    // Test angle between vectors
    float angleBetweenVecs = vec1.angleBetween(vec2);
    std::cout << "Angle between vec1 and vec2: " << angleBetweenVecs << " radians" << std::endl;

    // Test projection of vec1 onto vec2
    Vector2D projectionVec = vec1.projectOnto(vec2);
    std::cout << "Projection of vec1 onto vec2: " << projectionVec;

    // Test reflection of vec1 across vec3
    Vector2D reflectionVec = vec1.reflect(vec3);
    std::cout << "Reflection of vec1 across vec3: " << reflectionVec;

    // Test rotation of vec1 around vec3 by 90 degrees (PI/2 radians)
    vec1.rotate(3.14159265358979323846 / 2, vec3);
    std::cout << "vec1 rotated 90 degrees around vec3: " << vec1;

    // Test clamping magnitude
    vec2.clampMagnitude(5.0f);
    std::cout << "vec2 clamped to max magnitude 5: " << vec2;

    // Test orthogonal vector
    Vector2D orthogonalVec = vec1.orthogonal();
    std::cout << "Orthogonal vector to vec1: " << orthogonalVec;

    // Test linear interpolation (lerp)
    Vector2D lerpVec = Vector2D::lerp(vec1, vec2, 0.5f);
    std::cout << "Lerp between vec1 and vec2 at t=0.5: " << lerpVec;

    return 0;
}


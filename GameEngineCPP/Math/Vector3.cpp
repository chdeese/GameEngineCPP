#include "Vector3.h"
#include <cmath>

GameMath::Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

GameMath::Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float GameMath::Vector3::getMagnitude()
{
    return sqrt(x * x + y * y + z * z);
}

GameMath::Vector3 GameMath::Vector3::getNormalized()
{
    return normalize(*this);
}

GameMath::Vector3 GameMath::Vector3::normalize(Vector3 vector)
{
    if (vector.getMagnitude() == 0)
        return Vector3();

    return vector / vector.getMagnitude();
}

GameMath::Vector3 GameMath::Vector3::normalize()
{
    if (getMagnitude() == 0)
        return Vector3();

    *this = *this / getMagnitude();

    return *this;
}

float GameMath::Vector3::dotProduct(Vector3 lhs, Vector3 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

GameMath::Vector3 GameMath::Vector3::crossProduct(Vector3 lhs, Vector3 rhs)
{
    return Vector3((lhs.y * rhs.z) - (lhs.z * rhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z), (lhs.x * rhs.y) - (lhs.y * rhs.x));
}

GameMath::Vector3 GameMath::Vector3::operator +(Vector3 rhs)
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

GameMath::Vector3 GameMath::Vector3::operator -(Vector3 rhs)
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

GameMath::Vector3 GameMath::Vector3::operator *(float scalar)
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

GameMath::Vector3 operator *(float scalar, GameMath::Vector3 rhs)
{
    return GameMath::Vector3(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
}

GameMath::Vector3 GameMath::Vector3::operator / (float scalar)
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

bool GameMath::Vector3::operator==(Vector3 rhs)
{
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

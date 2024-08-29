#include "Vector4.h"
#include <cmath>

GameMath::Vector4::Vector4()
{
    x = 0; y = 0; z = 0; w = 0;
}

GameMath::Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float GameMath::Vector4::getMagnitude()
{
    return (float)sqrt(x * x + y * y + z * z + w * w);
}

GameMath::Vector4 GameMath::Vector4::getNormalized()
{
    return normalize(*this);
}

GameMath::Vector4 GameMath::Vector4::normalize(Vector4 vector)
{
    if (vector.getMagnitude() == 0)
        return Vector4();

    return vector / vector.getMagnitude();
}

GameMath::Vector4 GameMath::Vector4::normalize()
{
    if (getMagnitude() == 0)
        return Vector4();

    return *this = *this / getMagnitude();
}

float GameMath::Vector4::dotProduct(Vector4 lhs, Vector4 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

GameMath::Vector4 GameMath::Vector4::crossProduct(Vector4 lhs, Vector4 rhs)
{
    return Vector4(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x, 0);
}

GameMath::Vector4 GameMath::Vector4::operator +(Vector4 rhs)
{
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

GameMath::Vector4 GameMath::Vector4::operator-(Vector4 rhs)
{
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

GameMath::Vector4 GameMath::Vector4::operator*(float scalar)
{
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

GameMath::Vector4 GameMath::Vector4::operator/(float scalar)
{
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

bool GameMath::Vector4::operator==(Vector4 rhs)
{
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

GameMath::Vector4 operator*(float scalar, GameMath::Vector4 rhs)
{
    return GameMath::Vector4(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z, scalar * rhs.w);
}

GameMath::Vector4 GameMath::operator*(float scalar, Vector4 lhs)
{
    return Vector4();
}

#include "Vector2.h"
#include <cmath>

GameMath::Vector2::Vector2()
{
    x = 0;
    y = 0;
}

GameMath::Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float GameMath::Vector2::getMagnitude()
{
    return sqrt(x * x + y * y);
}

GameMath::Vector2 GameMath::Vector2::getNormalized()
{
    return normalize(*this);
}

GameMath::Vector2 GameMath::Vector2::normalize(Vector2 vector)
{
    if (vector.getMagnitude() == 0)
        return Vector2();

    return vector / vector.getMagnitude();
}

GameMath::Vector2 GameMath::Vector2::normalize()
{
    if (getMagnitude() == 0)
        return Vector2();

    *this = *this / getMagnitude();

    return *this;
}

float GameMath::Vector2::dotProduct(Vector2 lhs, Vector2 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

float GameMath::Vector2::findAngle(Vector2 lhs, Vector2 rhs)
{
    lhs = normalize(lhs);
    rhs = normalize(rhs);

    //Use the dotproduct to find the angle the actor needs to rotate
    float dotProd = dotProduct(lhs, rhs);

    if (abs(dotProd) > 1)
        return 0;

    float angle = (float)acos(dotProd);

    //Find a perpindicular vector to the direction
    Vector2 perp = Vector2(rhs.y, -rhs.x);

    //Find the dot product of the perpindicular vector and the current forward
    float perpDot = dotProduct(perp, lhs);

    //If the result isn't 0, use it to change the sign of the angle to be either positive or negative
    if (perpDot != 0)
        angle *= perpDot / abs(perpDot);

    return angle;
}

GameMath::Vector2 GameMath::Vector2::operator +(Vector2 rhs)
{
    return Vector2(x + rhs.x, y + rhs.y);
}

GameMath::Vector2 GameMath::Vector2::operator -(Vector2 rhs)
{
    return Vector2(x - rhs.x, y - rhs.y);
}

GameMath::Vector2 GameMath::Vector2::operator *(float scalar)
{
    return Vector2(x * scalar, y * scalar);
}

GameMath::Vector2 operator *(float scalar, GameMath::Vector2 rhs)
{
    return GameMath::Vector2(scalar * rhs.x, scalar * rhs.y);
}

GameMath::Vector2 GameMath::Vector2::operator / (float scalar)
{
    return Vector2(x / scalar, y / scalar);
}

bool GameMath::Vector2::operator==(Vector2 rhs)
{
    return x == rhs.x && y == rhs.y;
}

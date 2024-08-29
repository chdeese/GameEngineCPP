#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include <cmath>

GameMath::Matrix3::Matrix3()
{
    m00 = 1; m01 = 0; m02 = 0;
    m10 = 0; m11 = 1; m12 = 0;
    m20 = 0; m21 = 0; m22 = 1;
}

GameMath::Matrix3::Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
    this->m00 = m11; this->m01 = m12; this->m02 = m13;
    this->m10 = m21; this->m11 = m22; this->m12 = m23;
    this->m20 = m31; this->m21 = m32; this->m22 = m33;
}

GameMath::Matrix3 GameMath::Matrix3::operator+(Matrix3 rhs)
{
    return Matrix3
    (
        this->m00 + rhs.m00, this->m01 + rhs.m01, this->m02 + rhs.m02,
        this->m10 + rhs.m10, this->m11 + rhs.m11, this->m12 + rhs.m12,
        this->m20 + rhs.m20, this->m21 + rhs.m21, this->m22 + rhs.m22
    );
}

GameMath::Matrix3 GameMath::Matrix3::operator-(Matrix3 rhs)
{
    return Matrix3
    (
        this->m00 - rhs.m00, this->m01 - rhs.m01, this->m02 - rhs.m02,
        this->m10 - rhs.m10, this->m11 - rhs.m11, this->m12 - rhs.m12,
        this->m20 - rhs.m20, this->m21 - rhs.m21, this->m22 - rhs.m22
    );
}

GameMath::Matrix3 GameMath::Matrix3::operator*(Matrix3 rhs)
{
    return Matrix3
    (
        //Row1
        this->m00 * rhs.m00 + this->m01 * rhs.m10 + this->m02 * rhs.m20,
        this->m00 * rhs.m01 + this->m01 * rhs.m11 + this->m02 * rhs.m21,
        this->m00 * rhs.m02 + this->m01 * rhs.m12 + this->m02 * rhs.m22,
        //Row 2
        this->m10 * rhs.m00 + this->m11 * rhs.m10 + this->m12 * rhs.m20,
        this->m10 * rhs.m01 + this->m11 * rhs.m11 + this->m12 * rhs.m21,
        this->m10 * rhs.m02 + this->m11 * rhs.m12 + this->m12 * rhs.m22,
        //Row 3
        this->m20 * rhs.m00 + this->m21 * rhs.m10 + this->m22 * rhs.m20,
        this->m20 * rhs.m01 + this->m21 * rhs.m11 + this->m22 * rhs.m21,
        this->m20 * rhs.m02 + this->m21 * rhs.m12 + this->m22 * rhs.m22
    );
}

GameMath::Vector3 GameMath::Matrix3::operator*(Vector3 rhs)
{
    return Vector3
    (
        //Row1
        (this->m00 * rhs.x) + (this->m01 * rhs.y) + (this->m02 * rhs.z),
        //Row 2
        (this->m10 * rhs.x) + (this->m11 * rhs.y) + (this->m12 * rhs.z),
        //Row 3
        (this->m20 * rhs.x) + (this->m21 * rhs.y) + (this->m22 * rhs.z)
    );
}

bool GameMath::Matrix3::operator ==(Matrix3 rhs)
{
    return m00 == rhs.m00 && m01 == rhs.m01 && m02 == rhs.m02 &&
           m10 == rhs.m10 && m11 == rhs.m11 && m12 == rhs.m12 &&
           m20 == rhs.m20 && m21 == rhs.m21 && m22 == rhs.m22;
}

GameMath::Matrix3 GameMath::Matrix3::createRotation(float radians)
{
    return Matrix3
    (
        (float)cos(radians), (float)sin(radians), 0,
        -(float)sin(radians), (float)cos(radians), 0,
        0, 0, 1
    );
}

GameMath::Matrix3 GameMath::Matrix3::createTranslation(Vector2 position)
{
    return Matrix3
    (
        1, 0, position.x,
        0, 1, position.y,
        0, 0, 1
    );
}

GameMath::Matrix3 GameMath::Matrix3::createScale(Vector2 scale)
{
    return Matrix3
    (
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, 1
    );
}

#include <cmath>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

GameMath::Matrix4::Matrix4()
{
    m00 = 1; m01 = 0; m02 = 0; m03 = 0;
    m10 = 0; m11 = 1; m12 = 0; m13 = 0;
    m20 = 0; m21 = 0; m22 = 1; m23 = 0;
    m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

GameMath::Matrix4::Matrix4(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44)
{
    this->m00 = m11; this->m01 = m12; this->m02 = m13; this->m03 = m14;
    this->m10 = m21; this->m11 = m22; this->m12 = m23; this->m13 = m24;
    this->m20 = m31; this->m21 = m32; this->m22 = m33; this->m23 = m34;
    this->m30 = m41; this->m31 = m42; this->m32 = m43; this->m33 = m44;
}

GameMath::Matrix4 GameMath::Matrix4::operator+(Matrix4 rhs)
{
    return Matrix4
    (
        this->m00 + rhs.m00, this->m01 + rhs.m01, this->m02 + rhs.m02, this->m03 + rhs.m03,
        this->m10 + rhs.m10, this->m11 + rhs.m11, this->m12 + rhs.m12, this->m13 + rhs.m13,
        this->m20 + rhs.m20, this->m21 + rhs.m21, this->m22 + rhs.m22, this->m23 + rhs.m23,
        this->m30 + rhs.m30, this->m31 + rhs.m31, this->m32 + rhs.m32, this->m33 + rhs.m33
    );
}

GameMath::Matrix4 GameMath::Matrix4::operator-(Matrix4 rhs)
{
    return Matrix4
    (
        this->m00 - rhs.m00, this->m01 - rhs.m01, this->m02 - rhs.m02, this->m03 - rhs.m03,
        this->m10 - rhs.m10, this->m11 - rhs.m11, this->m12 - rhs.m12, this->m13 - rhs.m13,
        this->m20 - rhs.m20, this->m21 - rhs.m21, this->m22 - rhs.m22, this->m23 - rhs.m23,
        this->m30 - rhs.m30, this->m31 - rhs.m31, this->m32 - rhs.m32, this->m33 - rhs.m33
    );
}

GameMath::Matrix4 GameMath::Matrix4::operator*(Matrix4 rhs)
{
    return Matrix4
    (
        //Row1
        this->m00 * rhs.m00 + this->m01 * rhs.m10 + this->m02 * rhs.m20 + this->m03 * rhs.m30,
        this->m00 * rhs.m01 + this->m01 * rhs.m11 + this->m02 * rhs.m21 + this->m03 * rhs.m31,
        this->m00 * rhs.m02 + this->m01 * rhs.m12 + this->m02 * rhs.m22 + this->m03 * rhs.m32,
        this->m00 * rhs.m03 + this->m01 * rhs.m13 + this->m02 * rhs.m23 + this->m03 * rhs.m33,
        //Row 2
        this->m10 * rhs.m00 + this->m11 * rhs.m10 + this->m12 * rhs.m20 + this->m13 * rhs.m30,
        this->m10 * rhs.m01 + this->m11 * rhs.m11 + this->m12 * rhs.m21 + this->m13 * rhs.m31,
        this->m10 * rhs.m02 + this->m11 * rhs.m12 + this->m12 * rhs.m22 + this->m13 * rhs.m32,
        this->m10 * rhs.m03 + this->m11 * rhs.m13 + this->m12 * rhs.m23 + this->m13 * rhs.m33,
        //Row 3
        this->m20 * rhs.m00 + this->m21 * rhs.m10 + this->m22 * rhs.m20 + this->m23 * rhs.m30,
        this->m20 * rhs.m01 + this->m21 * rhs.m11 + this->m22 * rhs.m21 + this->m23 * rhs.m31,
        this->m20 * rhs.m02 + this->m21 * rhs.m12 + this->m22 * rhs.m22 + this->m23 * rhs.m32,
        this->m20 * rhs.m03 + this->m21 * rhs.m13 + this->m22 * rhs.m23 + this->m23 * rhs.m33,
        //Row 4
        this->m30 * rhs.m00 + this->m31 * rhs.m10 + this->m32 * rhs.m20 + this->m33 * rhs.m30,
        this->m30 * rhs.m01 + this->m31 * rhs.m11 + this->m32 * rhs.m21 + this->m33 * rhs.m31,
        this->m30 * rhs.m02 + this->m31 * rhs.m12 + this->m32 * rhs.m22 + this->m33 * rhs.m32,
        this->m30 * rhs.m03 + this->m31 * rhs.m13 + this->m32 * rhs.m23 + this->m33 * rhs.m33
    );
}

GameMath::Vector4 GameMath::Matrix4::operator*(Vector4 rhs)
{
    return Vector4
    (
        //Row1
        (m00 * rhs.x) + (m01 * rhs.y) + (m02 * rhs.z) + (m03 * rhs.w),
        //Row 2
        (m10 * rhs.x) + (m11 * rhs.y) + (m12 * rhs.z) + (m13 * rhs.w),
        //Row 3
        (m20 * rhs.x) + (m21 * rhs.y) + (m22 * rhs.z) + (m23 * rhs.w),
        //Row 4
        (m30 * rhs.x) + (m31 * rhs.y) + (m32 * rhs.z) + (m33 * rhs.w)
    );
}

bool GameMath::Matrix4::operator==(Matrix4 rhs)
{
    return m00 == rhs.m00 && m01 == rhs.m01 && m02 == rhs.m02 && m03 == rhs.m03 &&
        m10 == rhs.m10 && m11 == rhs.m11 && m12 == rhs.m12 && m13 == rhs.m13 &&
        m20 == rhs.m20 && m21 == rhs.m21 && m22 == rhs.m22 && m23 == rhs.m23 &&
        m30 == rhs.m30 && m31 == rhs.m31 && m32 == rhs.m32 && m33 == rhs.m33;
}

GameMath::Matrix4 GameMath::Matrix4::createRotationZ(float radians)
{
    return Matrix4
    (
        (float)cos(radians), -(float)sin(radians), 0, 0,
        (float)sin(radians), (float)cos(radians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

GameMath::Matrix4 GameMath::Matrix4::createRotationY(float radians)
{
    return Matrix4
    (
        (float)cos(radians), 0, (float)sin(radians), 0,
        0, 1, 0, 0,
        -(float)sin(radians), 0, (float)cos(radians), 0,
        0, 0, 0, 1
    );
}

GameMath::Matrix4 GameMath::Matrix4::createRotationX(float radians)
{
    return Matrix4
    (
        1, 0, 0, 0,
        0, (float)cos(radians), -(float)sin(radians), 0,
        0, (float)sin(radians), (float)cos(radians), 0,
        0, 0, 0, 1
    );
}

GameMath::Matrix4 GameMath::Matrix4::createTranslation(Vector3 position)
{
    return Matrix4
    (
        1, 0, 0, position.x,
        0, 1, 0, position.y,
        0, 0, 1, position.z,
        0, 0, 0, 1
    );
}

GameMath::Matrix4 GameMath::Matrix4::createScale(Vector3 scale)
{
    return Matrix4
    (
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );
}

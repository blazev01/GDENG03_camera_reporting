#pragma once
#include "math.h"
#include "iostream"

class Vector3D;

class Vector4D
{
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4D(float n = 0.0f);
    Vector4D(float x, float y, float z, float w);
    Vector4D(const Vector3D& vector3, float w);
    Vector4D(const Vector4D& vector4);

public:
    void Normalize();
    Vector4D Normalized() const;
    float Magnitude() const;
    float SqrMagnitude() const;

    static Vector4D Zero();
    static Vector4D One();
    static float Dot(const Vector4D& left, const Vector4D& right);
    static Vector4D Cross(const Vector4D& v1, const Vector4D& v2, const Vector4D& v3);
    static Vector4D Lerp(const Vector4D& start, const Vector4D& end, float delta);

    Vector4D& operator=(const Vector3D& right);
    Vector4D& operator=(const Vector4D& right);

    friend Vector4D operator-(const Vector4D& right);
    friend Vector4D operator+(const Vector4D& left, const Vector4D& right);
    friend Vector4D& operator+=(Vector4D& left, const Vector4D& right);
    friend Vector4D operator-(const Vector4D& left, const Vector4D& right);
    friend Vector4D& operator-=(Vector4D& left, const Vector4D& right);
    friend Vector4D operator*(const Vector4D& left, const Vector4D& right);
    friend Vector4D& operator*=(Vector4D& left, const Vector4D& right);
    friend Vector4D operator*(const Vector4D& left, const float& right);
    friend Vector4D operator*(const float& left, const Vector4D& right);
    friend Vector4D& operator*=(Vector4D& left, const float& right);
    friend Vector4D operator/(const Vector4D& left, const Vector4D& right);
    friend Vector4D& operator/=(Vector4D& left, const Vector4D& right);
    friend Vector4D operator/(const Vector4D& left, const float& right);
    friend Vector4D operator/(const float& left, const Vector4D& right);
    friend Vector4D& operator/=(Vector4D& left, const float& right);
    friend bool operator==(const Vector4D& left, const Vector4D& right);
    friend bool operator!=(const Vector4D& left, const Vector4D& right);

    friend std::ostream& operator<<(std::ostream& out, const Vector4D& vector4);
};


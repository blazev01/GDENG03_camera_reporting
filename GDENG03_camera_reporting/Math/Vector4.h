#pragma once
#include "math.h"
#include "iostream"

class Vector3;

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4(float n = 0.0f);
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector3& vector3, float w);
    Vector4(const Vector4& vector4);

public:
    void Normalize();
    Vector4 Normalized() const;
    float Magnitude() const;
    float SqrMagnitude() const;

    static Vector4 Zero();
    static Vector4 One();
    static float Dot(const Vector4& left, const Vector4& right);
    static Vector4 Cross(const Vector4& v1, const Vector4& v2, const Vector4& v3);
    static Vector4 Lerp(const Vector4& start, const Vector4& end, float delta);

    Vector4& operator=(const Vector3& right);
    Vector4& operator=(const Vector4& right);

    friend Vector4 operator-(const Vector4& right);
    friend Vector4 operator+(const Vector4& left, const Vector4& right);
    friend Vector4& operator+=(Vector4& left, const Vector4& right);
    friend Vector4 operator-(const Vector4& left, const Vector4& right);
    friend Vector4& operator-=(Vector4& left, const Vector4& right);
    friend Vector4 operator*(const Vector4& left, const Vector4& right);
    friend Vector4& operator*=(Vector4& left, const Vector4& right);
    friend Vector4 operator*(const Vector4& left, const float& right);
    friend Vector4 operator*(const float& left, const Vector4& right);
    friend Vector4& operator*=(Vector4& left, const float& right);
    friend Vector4 operator/(const Vector4& left, const Vector4& right);
    friend Vector4& operator/=(Vector4& left, const Vector4& right);
    friend Vector4 operator/(const Vector4& left, const float& right);
    friend Vector4 operator/(const float& left, const Vector4& right);
    friend Vector4& operator/=(Vector4& left, const float& right);
    friend bool operator==(const Vector4& left, const Vector4& right);
    friend bool operator!=(const Vector4& left, const Vector4& right);

    friend std::ostream& operator<<(std::ostream& out, const Vector4& vector4);
};


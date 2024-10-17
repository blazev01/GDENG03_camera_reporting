#pragma once
#include "math.h"
#include "iostream"

class Vector3;

class Vector2
{
public:
    float x;
    float y;

public:
    Vector2(float n = 0.0f);
    Vector2(float x, float y);
    Vector2(const Vector2& v);

public:
    void Normalize();
    Vector2 Normalized() const;
    float Direction() const;
    float Magnitude() const;
    float SqrMagnitude() const;

    static Vector2 Zero();
    static Vector2 One();
    static float Dot(const Vector2& left, const Vector2& right);
    static Vector2 Lerp(const Vector2& start, const Vector2& end, float delta);

    Vector2& operator=(const Vector2& right);
    Vector2& operator=(const Vector3& right);

    friend Vector2 operator-(const Vector2& right);
    friend Vector2 operator+(const Vector2& left, const Vector2& right);
    friend Vector2& operator+=(Vector2& left, const Vector2& right);
    friend Vector2 operator-(const Vector2& left, const Vector2& right);
    friend Vector2& operator-=(Vector2& left, const Vector2& right);
    friend Vector2 operator*(const Vector2& left, const Vector2& right);
    friend Vector2& operator*=(Vector2& left, const Vector2& right);
    friend Vector2 operator*(const Vector2& left, const float& right);
    friend Vector2 operator*(const float& left, const Vector2& right);
    friend Vector2& operator*=(Vector2& left, const float& right);
    friend Vector2 operator/(const Vector2& left, const Vector2& right);
    friend Vector2& operator/=(Vector2& left, const Vector2& right);
    friend Vector2 operator/(const Vector2& left, const float& right);
    friend Vector2 operator/(const float& left, const Vector2& right);
    friend Vector2& operator/=(Vector2& left, const float& right);
    friend bool operator==(const Vector2& left, const Vector2& right);
    friend bool operator!=(const Vector2& left, const Vector2& right);

    friend std::ostream& operator<<(std::ostream& out, const Vector2& vector2);
};
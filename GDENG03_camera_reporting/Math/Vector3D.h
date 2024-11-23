#pragma once
#include "iostream"

class Vector2D;

class Vector3D
{
public:
    float x;
    float y;
    float z;

public:
    Vector3D(float n = 0.0f);
    Vector3D(float x, float y, float z);
    Vector3D(Vector2D vector2, float z);
    Vector3D(const Vector3D& vector3);

public:
    void Normalize();
    Vector3D Normalized() const;
    float Magnitude() const;
    float SqrMagnitude() const;

    static Vector3D Zero();
    static Vector3D One();
    static float Dot(const Vector3D& left, const Vector3D& right);
    static Vector3D Cross(const Vector3D& left, const Vector3D& right);
    static Vector3D Lerp(const Vector3D& start, const Vector3D& end, float delta);

    Vector3D& operator=(const Vector2D& right);
    Vector3D& operator=(const Vector3D& right);

    friend Vector3D operator-(const Vector3D& right);
    friend Vector3D operator+(const Vector3D& left, const Vector3D& right);
    friend Vector3D& operator+=(Vector3D& left, const Vector3D& right);
    friend Vector3D operator-(const Vector3D& left, const Vector3D& right);
    friend Vector3D& operator-=(Vector3D& left, const Vector3D& right);
    friend Vector3D operator*(const Vector3D& left, const Vector3D& right);
    friend Vector3D& operator*=(Vector3D& left, const Vector3D& right);
    friend Vector3D operator*(const Vector3D& left, const float& right);
    friend Vector3D operator*(const float& left, const Vector3D& right);
    friend Vector3D& operator*=(Vector3D& left, const float& right);
    friend Vector3D operator/(const Vector3D& left, const Vector3D& right);
    friend Vector3D& operator/=(Vector3D& left, const Vector3D& right);
    friend Vector3D operator/(const Vector3D& left, const float& right);
    friend Vector3D operator/(const float& left, const Vector3D& right);
    friend Vector3D& operator/=(Vector3D& left, const float& right);
    friend bool operator==(const Vector3D& left, const Vector3D& right);
    friend bool operator!=(const Vector3D& left, const Vector3D& right);

    friend std::ostream& operator<<(std::ostream& out, const Vector3D& vector3);
};
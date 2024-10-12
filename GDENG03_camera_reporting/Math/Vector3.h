#pragma once

class Vector2;

class Vector3
{
public:
    float x;
    float y;
    float z;

public:
    Vector3(float n = 0.0f);
    Vector3(float x, float y, float z);
    Vector3(Vector2 vector2, float z);

public:
    void Normalize();
    Vector3 Normalized() const;
    float Magnitude() const;
    float SqrMagnitude() const;

    static Vector3 Zero();
    static Vector3 One();
    static float Dot(const Vector3& left, const Vector3& right);
    static Vector3 Cross(const Vector3& left, const Vector3& right);
    static Vector3 Lerp(const Vector3& start, const Vector3& end, float delta);

    friend Vector3 operator-(const Vector3& right);
    friend Vector3 operator+(const Vector3& left, const Vector3& right);
    friend Vector3& operator+=(Vector3& left, const Vector3& right);
    friend Vector3 operator-(const Vector3& left, const Vector3& right);
    friend Vector3& operator-=(Vector3& left, const Vector3& right);
    friend Vector3 operator*(const Vector3& left, const Vector3& right);
    friend Vector3& operator*=(Vector3& left, const Vector3& right);
    friend Vector3 operator*(const Vector3& left, const float& right);
    friend Vector3 operator*(const float& left, const Vector3& right);
    friend Vector3& operator*=(Vector3& left, const float& right);
    friend Vector3 operator/(const Vector3& left, const Vector3& right);
    friend Vector3& operator/=(Vector3& left, const Vector3& right);
    friend Vector3 operator/(const Vector3& left, const float& right);
    friend Vector3 operator/(const float& left, const Vector3& right);
    friend Vector3& operator/=(Vector3& left, const float& right);
    friend bool operator==(const Vector3& left, const Vector3& right);
    friend bool operator!=(const Vector3& left, const Vector3& right);

};
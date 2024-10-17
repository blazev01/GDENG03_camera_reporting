#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4(float n)
{
    this->x = n;
    this->y = n;
    this->z = n;
    this->w = n;
}

Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4::Vector4(const Vector3& vector3, float w)
{
    this->x = vector3.x;
    this->y = vector3.y;
    this->z = vector3.z;
    this->w = w;
}

Vector4::Vector4(const Vector4& vector4)
{
    this->x = vector4.x;
    this->y = vector4.y;
    this->z = vector4.z;
    this->w = vector4.w;
}

Vector4 Vector4::Zero()
{
    return Vector4(0.0f);
}

Vector4 Vector4::One()
{
    return Vector4(1.0f);
}

void Vector4::Normalize()
{
    *this = this->Normalized();
}

Vector4 Vector4::Normalized() const
{
    float mag = this->Magnitude();
    if (mag != 0) return *this / mag;
    return Vector4::Zero();
}

float Vector4::Magnitude() const
{
    return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

float Vector4::SqrMagnitude() const
{
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
}

float Vector4::Dot(const Vector4& left, const Vector4& right)
{
    Vector4 Prod = left * right;
    return Prod.x + Prod.y + Prod.z + Prod.w;
}

Vector4 Vector4::Cross(const Vector4& v1, const Vector4& v2, const Vector4& v3)
{
    float x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
    float y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
    float z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
    float w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
    return Vector4(x, y, z, w);
}

Vector4 Vector4::Lerp(const Vector4& start, const Vector4& end, float delta)
{
    Vector4 v;
    v.x = (start.x * (1.0f - delta)) + (end.x * delta);
    v.y = (start.y * (1.0f - delta)) + (end.y * delta);
    v.z = (start.z * (1.0f - delta)) + (end.z * delta);
    v.w = (start.w * (1.0f - delta)) + (end.w * delta);

    return v;
}

Vector4& Vector4::operator=(const Vector3& right)
{
    this->x = right.x;
    this->y = right.y;
    this->z = right.z;
    this->w = 0.0f;

    return *this;
}

Vector4& Vector4::operator=(const Vector4& right)
{
    if (this != &right)
    {
        this->x = right.x;
        this->y = right.y;
        this->z = right.z;
        this->w = right.w;
    }

    return *this;
}

Vector4 operator-(const Vector4& right)
{
    return Vector4(-right.x, -right.y, -right.z, -right.w);
}

Vector4 operator+(const Vector4& left, const Vector4& right)
{
    return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

Vector4& operator+=(Vector4& left, const Vector4& right)
{
    left = left + right;
    return left;
}

Vector4 operator-(const Vector4& left, const Vector4& right)
{
    return Vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

Vector4& operator-=(Vector4& left, const Vector4& right)
{
    left = left - right;
    return left;
}

Vector4 operator*(const Vector4& left, const Vector4& right)
{
    return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

Vector4& operator*=(Vector4& left, const Vector4& right)
{
    left = left * right;
    return left;
}

Vector4 operator*(const Vector4& left, const float& right)
{
    return Vector4(left.x * right, left.y * right, left.z * right, left.w * right);
}

Vector4 operator*(const float& left, const Vector4& right)
{
    return Vector4(left * right.x, left * right.y, left * right.z, left * right.w);
}

Vector4& operator*=(Vector4& left, const float& right)
{
    left = left * right;
    return left;
}

Vector4 operator/(const Vector4& left, const Vector4& right)
{
    return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

Vector4& operator/=(Vector4& left, const Vector4& right)
{
    left = left / right;
    return left;
}

Vector4 operator/(const Vector4& left, const float& right)
{
    return Vector4(left.x / right, left.y / right, left.z / right, left.w / right);
}

Vector4 operator/(const float& left, const Vector4& right)
{
    return Vector4(left / right.x, left / right.y, left / right.z, left / right.w);
}

Vector4& operator/=(Vector4& left, const float& right)
{
    left = left / right;
    return left;
}

bool operator==(const Vector4& left, const Vector4& right)
{
    return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
}

bool operator!=(const Vector4& left, const Vector4& right)
{
    return (left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w);
}

std::ostream& operator<<(std::ostream& out, const Vector4& vector4)
{
    out << "(" << vector4.x << ", " << vector4.y << ", " << vector4.z << ", " << vector4.w << ")";
    return out;
}

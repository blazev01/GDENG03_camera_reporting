#include "Vector4D.h"
#include "Vector3D.h"

Vector4D::Vector4D(float n)
{
    this->x = n;
    this->y = n;
    this->z = n;
    this->w = n;
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4D::Vector4D(const Vector3D& vector3, float w)
{
    this->x = vector3.x;
    this->y = vector3.y;
    this->z = vector3.z;
    this->w = w;
}

Vector4D::Vector4D(const Vector4D& vector4)
{
    this->x = vector4.x;
    this->y = vector4.y;
    this->z = vector4.z;
    this->w = vector4.w;
}

Vector4D Vector4D::Zero()
{
    return Vector4D(0.0f);
}

Vector4D Vector4D::One()
{
    return Vector4D(1.0f);
}

void Vector4D::Normalize()
{
    *this = this->Normalized();
}

Vector4D Vector4D::Normalized() const
{
    float mag = this->Magnitude();
    if (mag != 0) return *this / mag;
    return Vector4D::Zero();
}

float Vector4D::Magnitude() const
{
    return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

float Vector4D::SqrMagnitude() const
{
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
}

float Vector4D::Dot(const Vector4D& left, const Vector4D& right)
{
    Vector4D Prod = left * right;
    return Prod.x + Prod.y + Prod.z + Prod.w;
}

Vector4D Vector4D::Cross(const Vector4D& v1, const Vector4D& v2, const Vector4D& v3)
{
    float x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
    float y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
    float z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
    float w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
    return Vector4D(x, y, z, w);
}

Vector4D Vector4D::Lerp(const Vector4D& start, const Vector4D& end, float delta)
{
    Vector4D v;
    v.x = (start.x * (1.0f - delta)) + (end.x * delta);
    v.y = (start.y * (1.0f - delta)) + (end.y * delta);
    v.z = (start.z * (1.0f - delta)) + (end.z * delta);
    v.w = (start.w * (1.0f - delta)) + (end.w * delta);

    return v;
}

Vector4D& Vector4D::operator=(const Vector3D& right)
{
    this->x = right.x;
    this->y = right.y;
    this->z = right.z;
    this->w = 0.0f;

    return *this;
}

Vector4D& Vector4D::operator=(const Vector4D& right)
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

Vector4D operator-(const Vector4D& right)
{
    return Vector4D(-right.x, -right.y, -right.z, -right.w);
}

Vector4D operator+(const Vector4D& left, const Vector4D& right)
{
    return Vector4D(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

Vector4D& operator+=(Vector4D& left, const Vector4D& right)
{
    left = left + right;
    return left;
}

Vector4D operator-(const Vector4D& left, const Vector4D& right)
{
    return Vector4D(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

Vector4D& operator-=(Vector4D& left, const Vector4D& right)
{
    left = left - right;
    return left;
}

Vector4D operator*(const Vector4D& left, const Vector4D& right)
{
    return Vector4D(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

Vector4D& operator*=(Vector4D& left, const Vector4D& right)
{
    left = left * right;
    return left;
}

Vector4D operator*(const Vector4D& left, const float& right)
{
    return Vector4D(left.x * right, left.y * right, left.z * right, left.w * right);
}

Vector4D operator*(const float& left, const Vector4D& right)
{
    return Vector4D(left * right.x, left * right.y, left * right.z, left * right.w);
}

Vector4D& operator*=(Vector4D& left, const float& right)
{
    left = left * right;
    return left;
}

Vector4D operator/(const Vector4D& left, const Vector4D& right)
{
    return Vector4D(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

Vector4D& operator/=(Vector4D& left, const Vector4D& right)
{
    left = left / right;
    return left;
}

Vector4D operator/(const Vector4D& left, const float& right)
{
    return Vector4D(left.x / right, left.y / right, left.z / right, left.w / right);
}

Vector4D operator/(const float& left, const Vector4D& right)
{
    return Vector4D(left / right.x, left / right.y, left / right.z, left / right.w);
}

Vector4D& operator/=(Vector4D& left, const float& right)
{
    left = left / right;
    return left;
}

bool operator==(const Vector4D& left, const Vector4D& right)
{
    return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
}

bool operator!=(const Vector4D& left, const Vector4D& right)
{
    return (left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w);
}

std::ostream& operator<<(std::ostream& out, const Vector4D& vector4)
{
    out << "(" << vector4.x << ", " << vector4.y << ", " << vector4.z << ", " << vector4.w << ")";
    return out;
}

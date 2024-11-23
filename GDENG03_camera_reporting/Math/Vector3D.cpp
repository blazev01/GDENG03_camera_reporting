#include "Vector3D.h"
#include "Vector2D.h"

Vector3D::Vector3D(float n) {
    this->x = n;
    this->y = n;
    this->z = n;
}

Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(Vector2D vector2, float z) {
    this->x = vector2.x;
    this->y = vector2.y;
    this->z = z;
}

Vector3D::Vector3D(const Vector3D& vector3) {
    this->x = vector3.x;
    this->y = vector3.y;
    this->z = vector3.z;
}

Vector3D Vector3D::Zero() {
    return Vector3D(0.0f);
}

Vector3D Vector3D::One() {
    return Vector3D(1.0f);
}

void Vector3D::Normalize() {
    *this = this->Normalized();
}

Vector3D Vector3D::Normalized() const {
    float mag = this->Magnitude();
    if (mag != 0) return *this / mag;
    return Vector3D::Zero();
}

float Vector3D::Magnitude() const {
    return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

float Vector3D::SqrMagnitude() const {
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

float Vector3D::Dot(const Vector3D& left, const Vector3D& right) {
    Vector3D Prod = left * right;
    return Prod.x + Prod.y + Prod.z;
}

Vector3D Vector3D::Cross(const Vector3D& left, const Vector3D& right) {
    float x = (left.y * right.z) - (left.z * right.y);
    float y = (left.x * right.z) - (left.z * right.x);
    float z = (left.x * right.y) - (left.y * right.x);
    return Vector3D(x, y, z);
}

Vector3D Vector3D::Lerp(const Vector3D& start, const Vector3D& end, float delta)
{
    Vector3D v;
    v.x = (start.x * (1.0f - delta)) + (end.x * delta);
    v.y = (start.y * (1.0f - delta)) + (end.y * delta);
    v.z = (start.z * (1.0f - delta)) + (end.z * delta);

    return v;
}

Vector3D& Vector3D::operator=(const Vector2D& right)
{
    this->x = right.x;
    this->y = right.y;
    this->z = 0.0f;

    return *this;
}

Vector3D& Vector3D::operator=(const Vector3D& right)
{
    if (this != &right)
    {
        this->x = right.x;
        this->y = right.y;
        this->z = right.z;
    }

    return *this;
}

Vector3D operator-(const Vector3D& right) {
    return Vector3D(-right.x, -right.y, -right.z);
}

Vector3D operator+(const Vector3D& left, const Vector3D& right) {
    return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3D& operator+=(Vector3D& left, const Vector3D& right) {
    left = left + right;
    return left;
}

Vector3D operator-(const Vector3D& left, const Vector3D& right) {
    return Vector3D(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3D& operator-=(Vector3D& left, const Vector3D& right) {
    left = left - right;
    return left;
}

Vector3D operator*(const Vector3D& left, const Vector3D& right) {
    return Vector3D(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3D& operator*=(Vector3D& left, const Vector3D& right) {
    left = left * right;
    return left;
}

Vector3D operator*(const Vector3D& left, const float& right) {
    return Vector3D(left.x * right, left.y * right, left.z * right);
}

Vector3D operator*(const float& left, const Vector3D& right) {
    return Vector3D(left * right.x, left * right.y, left * right.z);
}

Vector3D& operator*=(Vector3D& left, const float& right) {
    left = left * right;
    return left;
}

Vector3D operator/(const Vector3D& left, const Vector3D& right) {
    return Vector3D(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3D& operator/=(Vector3D& left, const Vector3D& right) {
    left = left / right;
    return left;
}

Vector3D operator/(const Vector3D& left, const float& right) {
    return Vector3D(left.x / right, left.y / right, left.z / right);
}

Vector3D operator/(const float& left, const Vector3D& right) {
    return Vector3D(left / right.x, left / right.y, left / right.z);
}

Vector3D& operator/=(Vector3D& left, const float& right) {
    left = left / right;
    return left;
}

bool operator==(const Vector3D& left, const Vector3D& right) {
    return (left.x == right.x && left.y == right.y && left.z == right.z);
}

bool operator!=(const Vector3D& left, const Vector3D& right) {
    return (left.x != right.x || left.y != right.y || left.z != right.z);
}

std::ostream& operator<<(std::ostream& out, const Vector3D& vector3)
{
    out << "(" << vector3.x << ", " << vector3.y << ", " << vector3.z << ")";
    return out;
}

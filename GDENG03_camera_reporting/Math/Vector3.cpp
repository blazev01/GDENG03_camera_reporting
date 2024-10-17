#include "Vector3.h"
#include "Vector2.h"

Vector3::Vector3(float n) {
    this->x = n;
    this->y = n;
    this->z = n;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(Vector2 vector2, float z) {
    this->x = vector2.x;
    this->y = vector2.y;
    this->z = z;
}

Vector3::Vector3(const Vector3& vector3) {
    this->x = vector3.x;
    this->y = vector3.y;
    this->z = vector3.z;
}

Vector3 Vector3::Zero() {
    return Vector3(0.0f);
}

Vector3 Vector3::One() {
    return Vector3(1.0f);
}

void Vector3::Normalize() {
    *this = this->Normalized();
}

Vector3 Vector3::Normalized() const {
    float mag = this->Magnitude();
    if (mag != 0) return *this / mag;
    return Vector3::Zero();
}

float Vector3::Magnitude() const {
    return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

float Vector3::SqrMagnitude() const {
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

float Vector3::Dot(const Vector3& left, const Vector3& right) {
    Vector3 Prod = left * right;
    return Prod.x + Prod.y + Prod.z;
}

Vector3 Vector3::Cross(const Vector3& left, const Vector3& right) {
    float x = (left.y * right.z) - (left.z * right.y);
    float y = (left.x * right.z) - (left.z * right.x);
    float z = (left.x * right.y) - (left.y * right.x);
    return Vector3(x, y, z);
}

Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float delta)
{
    Vector3 v;
    v.x = (start.x * (1.0f - delta)) + (end.x * delta);
    v.y = (start.y * (1.0f - delta)) + (end.y * delta);
    v.z = (start.z * (1.0f - delta)) + (end.z * delta);

    return v;
}

Vector3& Vector3::operator=(const Vector2& right)
{
    this->x = right.x;
    this->y = right.y;
    this->z = 0.0f;

    return *this;
}

Vector3& Vector3::operator=(const Vector3& right)
{
    if (this != &right)
    {
        this->x = right.x;
        this->y = right.y;
        this->z = right.z;
    }

    return *this;
}

Vector3 operator-(const Vector3& right) {
    return Vector3(-right.x, -right.y, -right.z);
}

Vector3 operator+(const Vector3& left, const Vector3& right) {
    return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3& operator+=(Vector3& left, const Vector3& right) {
    left = left + right;
    return left;
}

Vector3 operator-(const Vector3& left, const Vector3& right) {
    return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3& operator-=(Vector3& left, const Vector3& right) {
    left = left - right;
    return left;
}

Vector3 operator*(const Vector3& left, const Vector3& right) {
    return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3& operator*=(Vector3& left, const Vector3& right) {
    left = left * right;
    return left;
}

Vector3 operator*(const Vector3& left, const float& right) {
    return Vector3(left.x * right, left.y * right, left.z * right);
}

Vector3 operator*(const float& left, const Vector3& right) {
    return Vector3(left * right.x, left * right.y, left * right.z);
}

Vector3& operator*=(Vector3& left, const float& right) {
    left = left * right;
    return left;
}

Vector3 operator/(const Vector3& left, const Vector3& right) {
    return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3& operator/=(Vector3& left, const Vector3& right) {
    left = left / right;
    return left;
}

Vector3 operator/(const Vector3& left, const float& right) {
    return Vector3(left.x / right, left.y / right, left.z / right);
}

Vector3 operator/(const float& left, const Vector3& right) {
    return Vector3(left / right.x, left / right.y, left / right.z);
}

Vector3& operator/=(Vector3& left, const float& right) {
    left = left / right;
    return left;
}

bool operator==(const Vector3& left, const Vector3& right) {
    return (left.x == right.x && left.y == right.y && left.z == right.z);
}

bool operator!=(const Vector3& left, const Vector3& right) {
    return (left.x != right.x || left.y != right.y || left.z != right.z);
}

std::ostream& operator<<(std::ostream& out, const Vector3& vector3)
{
    out << "(" << vector3.x << ", " << vector3.y << ", " << vector3.z << ")";
    return out;
}

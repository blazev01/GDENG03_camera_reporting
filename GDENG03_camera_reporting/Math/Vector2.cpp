#include "Vector2.h"
#include "Vector3.h"

Vector2::Vector2(float n) {
    this->x = n;
    this->y = n;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector2& vector2) {
    this->x = vector2.x;
    this->y = vector2.y;
}

Vector2 Vector2::Zero() {
    return Vector2(0.0f);
}

Vector2 Vector2::One() {
    return Vector2(1.0f);
}

void Vector2::Normalize() {
    *this = this->Normalized();
}

Vector2 Vector2::Normalized() const {
    float mag = this->Magnitude();
    if (mag != 0) return *this / mag;
    return Vector2::Zero();
}

float Vector2::Direction() const {
    return atan2f(this->y, this->x);
}

float Vector2::Magnitude() const {
    return sqrtf((this->x * this->x) + (this->y * this->y));
}

float Vector2::SqrMagnitude() const
{
    return (this->x * this->x) + (this->y * this->y);
}

float Vector2::Dot(const Vector2& left, const Vector2& right) {
    Vector2 Prod = left * right;
    return Prod.x + Prod.y;
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, float delta)
{
    Vector2 v;
    v.x = (start.x * (1.0f - delta)) + (end.x * delta);
    v.y = (start.y * (1.0f - delta)) + (end.y * delta);

    return v;
}

Vector2& Vector2::operator=(const Vector2& right)
{
    if (this != &right)
    {
        this->x = right.x;
        this->y = right.y;
    }

    return *this;
}

Vector2& Vector2::operator=(const Vector3& right)
{
    this->x = right.x;
    this->y = right.y;

    return *this;
}

Vector2 operator-(const Vector2& right) {
    return Vector2(-right.x, -right.y);
}

Vector2 operator+(const Vector2& left, const Vector2& right) {
    return Vector2(left.x + right.x, left.y + right.y);
}

Vector2& operator+=(Vector2& left, const Vector2& right) {
    left = left + right;
    return left;
}

Vector2 operator-(const Vector2& left, const Vector2& right) {
    return Vector2(left.x - right.x, left.y - right.y);
}

Vector2& operator-=(Vector2& left, const Vector2& right) {
    left = left - right;
    return left;
}

Vector2 operator*(const Vector2& left, const Vector2& right) {
    return Vector2(left.x * right.x, left.y * right.y);
}

Vector2& operator*=(Vector2& left, const Vector2& right) {
    left = left * right;
    return left;
}

Vector2 operator*(const Vector2& left, const float& right) {
    return Vector2(left.x * right, left.y * right);
}

Vector2 operator*(const float& left, const Vector2& right) {
    return Vector2(left * right.x, left * right.y);
}

Vector2& operator*=(Vector2& left, const float& right) {
    left = left * right;
    return left;
}

Vector2 operator/(const Vector2& left, const Vector2& right) {
    return Vector2(left.x / right.x, left.y / right.y);
}

Vector2& operator/=(Vector2& left, const Vector2& right) {
    left = left / right;
    return left;
}

Vector2 operator/(const Vector2& left, const float& right) {
    return Vector2(left.x / right, left.y / right);
}

Vector2 operator/(const float& left, const Vector2& right) {
    return Vector2(left / right.x, left / right.y);
}

Vector2& operator/=(Vector2& left, const float& right) {
    left = left / right;
    return left;
}

bool operator==(const Vector2& left, const Vector2& right) {
    return (left.x == right.x && left.y == right.y);
}

bool operator!=(const Vector2& left, const Vector2& right) {
    return (left.x != right.x || left.y != right.y);
}

std::ostream& operator<<(std::ostream& out, const Vector2& vector2)
{
    out << "(" << vector2.x << ", " << vector2.y << ")";
    return out;
}

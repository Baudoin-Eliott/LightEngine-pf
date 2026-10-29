#include "Vector.h"

#include "Utils.h"

#include <cmath>

float Vector2f::Dot(const Vector2f& a, const Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

float Vector2f::Cross(const Vector2f& a, const Vector2f& b)
{
    return a.x * b.y - a.y * b.x;
}

float Vector2f::Distance(const Vector2f& a, const Vector2f& b)
{
    return (b - a).Magnitude();
}

float Vector2f::DistanceSqr(const Vector2f& a, const Vector2f& b)
{
    Vector2f trans = b - a;

    return Dot(trans, trans);
}

float Vector2f::GetAngleRadian(const Vector2f& v1, const Vector2f& v2)
{
    float dot = Dot(v1, v2);
    float det = Cross(v1, v2);

    return std::atan2(det, dot);
}

float Vector2f::GetAngleDegree(const Vector2f& v1, const Vector2f& v2)
{
    return GetAngleRadian(v1, v2) * RAD_TO_DEG;
}

bool Vector2f::Normalize()
{
    const float length = Magnitude();

    if (length == 0.f || std::isfinite(length) == false)
        return false;

    x /= length;
    y /= length;

    return true;
}

Vector2f Vector2f::Normalized() const
{
    Vector2f result = *this;
    result.Normalize();
    return result;
}

float Vector2f::Magnitude() const
{
    return std::hypot(x, y);
}

Vector2f Vector2f::operator+(const Vector2f& other) const
{
    return { x + other.x, y + other.y };
}

Vector2f Vector2f::operator+(float value) const
{
    return { x + value, y + value };
}

Vector2f Vector2f::operator-(float value) const
{
    return { x - value, y - value };
}

Vector2f Vector2f::operator-(const Vector2f& other) const
{
    return { x - other.x, y - other.y };
}

Vector2f Vector2f::operator*(float scalar) const
{
    return { x * scalar, y * scalar };
}

Vector2f Vector2f::operator/(float scalar) const
{
    return { x / scalar, y / scalar };
}

Vector2f operator*(float scalar, const Vector2f& vector)
{
    return vector * scalar;
}

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

bool Vector2f::operator==(const Vector2f& other) const
{
    return x == other.x && y == other.y;
}

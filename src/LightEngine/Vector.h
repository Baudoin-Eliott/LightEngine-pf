#pragma once

class Vector2f
{
public:
    float x = 0.f;
    float y = 0.f;

    Vector2f() = default;
    Vector2f(float x, float y) : x(x), y(y) {}
    Vector2f(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

    static float Dot(const Vector2f& a, const Vector2f& b);
    static float Cross(const Vector2f& a, const Vector2f& b);
    static float Distance(const Vector2f& a, const Vector2f& b);
    static float DistanceSqr(const Vector2f& a, const Vector2f& b);
    static float GetAngleRadian(const Vector2f& a, const Vector2f& b);
    static float GetAngleDegree(const Vector2f& a, const Vector2f& b);

    bool Normalize();
    Vector2f Normalized() const;
    float Magnitude() const;

    Vector2f operator+(const Vector2f& other) const;
    Vector2f operator+(float value) const;
    Vector2f operator-(float value) const;
    Vector2f operator-(const Vector2f& other) const;
    Vector2f operator*(float scalar) const;
    Vector2f operator/(float scalar) const;
    Vector2f& operator+=(const Vector2f& other);
    bool operator==(const Vector2f& other) const;
};

Vector2f operator*(float scalar, const Vector2f& vector);

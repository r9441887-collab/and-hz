#pragma once
#include <cmath>

struct Vec2 {
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& o) const;
    Vec2 operator-(const Vec2& o) const;
    Vec2 operator*(float s) const;
    Vec2 operator/(float s) const;
    Vec2& operator+=(const Vec2& o);
    Vec2& operator-=(const Vec2& o);
    Vec2& operator*=(float s);
    Vec2& operator/=(float s);

    float length() const;
    float lengthSq() const;
    Vec2 normalized() const;
    float dot(const Vec2& o) const;
    float cross(const Vec2& o) const;
    Vec2 rotated(float angle) const;
    Vec2 lerp(const Vec2& o, float t) const;

    static Vec2 Zero();
    static Vec2 One();
    static Vec2 Up();
    static Vec2 Down();
    static Vec2 Left();
    static Vec2 Right();
};

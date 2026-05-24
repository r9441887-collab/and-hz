#include "../../include/utils/Vector2.hpp"
#include <cmath>

Vec2 Vec2::operator+(const Vec2& o) const {
    return Vec2(x + o.x, y + o.y);
}

Vec2 Vec2::operator-(const Vec2& o) const {
    return Vec2(x - o.x, y - o.y);
}

Vec2 Vec2::operator*(float s) const {
    return Vec2(x * s, y * s);
}

Vec2 Vec2::operator/(float s) const {
    return Vec2(x / s, y / s);
}

Vec2& Vec2::operator+=(const Vec2& o) {
    x += o.x; y += o.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& o) {
    x -= o.x; y -= o.y;
    return *this;
}

Vec2& Vec2::operator*=(float s) {
    x *= s; y *= s;
    return *this;
}

Vec2& Vec2::operator/=(float s) {
    x /= s; y /= s;
    return *this;
}

float Vec2::length() const {
    return std::sqrt(x * x + y * y);
}

float Vec2::lengthSq() const {
    return x * x + y * y;
}

Vec2 Vec2::normalized() const {
    float len = std::sqrt(x * x + y * y);
    if (len > 0.00001f) {
        return Vec2(x / len, y / len);
    }
    return Vec2(0, 0);
}

float Vec2::dot(const Vec2& o) const {
    return x * o.x + y * o.y;
}

float Vec2::cross(const Vec2& o) const {
    return x * o.y - y * o.x;
}

Vec2 Vec2::rotated(float angle) const {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vec2(x * c - y * s, x * s + y * c);
}

Vec2 Vec2::lerp(const Vec2& o, float t) const {
    return Vec2(x + (o.x - x) * t, y + (o.y - y) * t);
}

Vec2 Vec2::Zero() { return Vec2(0, 0); }
Vec2 Vec2::One() { return Vec2(1, 1); }
Vec2 Vec2::Up() { return Vec2(0, -1); }
Vec2 Vec2::Down() { return Vec2(0, 1); }
Vec2 Vec2::Left() { return Vec2(-1, 0); }
Vec2 Vec2::Right() { return Vec2(1, 0); }

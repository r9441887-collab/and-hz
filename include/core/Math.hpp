#pragma once
#include <cmath>
#include <cstdint>

struct Vec2 {
    float x = 0, y = 0;
    Vec2() = default;
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    Vec2 operator/(float s) const { return {x / s, y / s}; }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
    Vec2& operator-=(const Vec2& o) { x -= o.x; y -= o.y; return *this; }
    Vec2& operator*=(float s) { x *= s; y *= s; return *this; }
    bool operator==(const Vec2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vec2& o) const { return x != o.x || y != o.y; }
    float length() const { return std::sqrt(x * x + y * y); }
    float lengthSq() const { return x * x + y * y; }
    Vec2 normalized() const { float l = length(); return l > 0 ? *this / l : Vec2{}; }
    void normalize() { float l = length(); if (l > 0) { x /= l; y /= l; } }
    float dot(const Vec2& o) const { return x * o.x + y * o.y; }
    float cross(const Vec2& o) const { return x * o.y - y * o.x; }
    Vec2 perpendicular() const { return {-y, x}; }
    Vec2 rotated(float angle) const {
        float c = std::cos(angle), s = std::sin(angle);
        return {x * c - y * s, x * s + y * c};
    }
    static Vec2 fromAngle(float angle) { return {std::cos(angle), std::sin(angle)}; }
};

struct Color {
    uint8_t r = 255, g = 255, b = 255, a = 255;
    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}
    Color operator*(float f) const {
        return {static_cast<uint8_t>(r * f), static_cast<uint8_t>(g * f),
                static_cast<uint8_t>(b * f), a};
    }
    Color blend(const Color& o, float t) const {
        return {static_cast<uint8_t>(r + (o.r - r) * t),
                static_cast<uint8_t>(g + (o.g - g) * t),
                static_cast<uint8_t>(b + (o.b - b) * t),
                static_cast<uint8_t>(a + (o.a - a) * t)};
    }
    static Color Red() { return {255, 0, 0}; }
    static Color Green() { return {0, 255, 0}; }
    static Color Blue() { return {0, 0, 255}; }
    static Color Black() { return {0, 0, 0}; }
    static Color White() { return {255, 255, 255}; }
    static Color Yellow() { return {255, 255, 0}; }
    static Color Cyan() { return {0, 255, 255}; }
    static Color Magenta() { return {255, 0, 255}; }
    static Color Orange() { return {255, 165, 0}; }
};

struct Rect {
    float x = 0, y = 0, w = 0, h = 0;
    Rect() = default;
    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    bool contains(const Vec2& p) const { return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h; }
    bool overlaps(const Rect& o) const { return x < o.x + o.w && x + w > o.x && y < o.y + o.h && y + h > o.y; }
    Vec2 center() const { return {x + w / 2, y + h / 2}; }
};

struct Circle {
    Vec2 center;
    float radius = 0;
    Circle() = default;
    Circle(const Vec2& c, float r) : center(c), radius(r) {}
    bool contains(const Vec2& p) const { return (p - center).lengthSq() <= radius * radius; }
    bool overlaps(const Circle& o) const {
        float r2 = radius + o.radius;
        return (center - o.center).lengthSq() <= r2 * r2;
    }
};

#include "../../include/utils/Rect.hpp"
#include <algorithm>

Rect::Rect(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h) {}

bool Rect::contains(float px, float py) const {
    return px >= x && px <= x + w && py >= y && py <= y + h;
}

bool Rect::overlaps(const Rect& o) const {
    return x < o.x + o.w && x + w > o.x &&
           y < o.y + o.h && y + h > o.y;
}

Vec2 Rect::center() const {
    return Vec2(x + w * 0.5f, y + h * 0.5f);
}

void Rect::expand(float amount) {
    x -= amount;
    y -= amount;
    w += amount * 2.0f;
    h += amount * 2.0f;
}

void Rect::contract(float amount) {
    x += amount;
    y += amount;
    w -= amount * 2.0f;
    h -= amount * 2.0f;
    if (w < 0) w = 0;
    if (h < 0) h = 0;
}

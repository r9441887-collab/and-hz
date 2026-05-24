#pragma once
#include "../../include/utils/Vector2.hpp"

struct Rect {
    float x, y, w, h;

    Rect() : x(0), y(0), w(0), h(0) {}
    Rect(float x, float y, float w, float h);

    bool contains(float px, float py) const;
    bool overlaps(const Rect& o) const;
    Vec2 center() const;
    void expand(float amount);
    void contract(float amount);
};

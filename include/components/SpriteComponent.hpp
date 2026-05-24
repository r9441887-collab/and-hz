#pragma once
#include <string>

struct SpriteComponent {
    std::string spriteName;
    int frame = 0;
    float animTimer = 0.0f;
    bool flipX = false;

    SpriteComponent() = default;
    explicit SpriteComponent(std::string spriteName_)
        : spriteName(std::move(spriteName_)) {}
};

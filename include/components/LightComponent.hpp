#pragma once
#include <cstdint>

struct LightComponent {
    float radius = 64.0f;
    uint32_t color = 0xFFFFFFFF;
    bool flickering = false;

    LightComponent() = default;
    LightComponent(float radius_, uint32_t color_ = 0xFFFFFFFF,
                   bool flickering_ = false)
        : radius(radius_), color(color_), flickering(flickering_) {}
};

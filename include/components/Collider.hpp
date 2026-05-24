#pragma once

struct ColliderComponent {
    float radius = 8.0f;

    ColliderComponent() = default;
    explicit ColliderComponent(float radius_) : radius(radius_) {}
};

#pragma once

struct TransformComponent {
    float x = 0.0f;
    float y = 0.0f;
    float angle = 0.0f;

    TransformComponent() = default;
    TransformComponent(float x_, float y_, float angle_ = 0.0f)
        : x(x_), y(y_), angle(angle_) {}
};

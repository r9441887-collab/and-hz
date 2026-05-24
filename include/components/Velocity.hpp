#pragma once

struct VelocityComponent {
    float vx = 0.0f;
    float vy = 0.0f;
    float friction = 0.0f;

    VelocityComponent() = default;
    VelocityComponent(float vx_, float vy_, float friction_ = 0.0f)
        : vx(vx_), vy(vy_), friction(friction_) {}
};

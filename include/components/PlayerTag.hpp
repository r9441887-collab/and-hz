#pragma once

struct PlayerTagComponent {
    float speed = 120.0f;
    int keys = 0;

    PlayerTagComponent() = default;
    explicit PlayerTagComponent(float speed_) : speed(speed_) {}
};

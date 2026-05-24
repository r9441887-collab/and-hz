#pragma once

struct HealthComponent {
    int current = 100;
    int max = 100;
    float invincibilityTimer = 0.0f;

    HealthComponent() = default;
    HealthComponent(int current_, int max_, float invTimer_ = 0.0f)
        : current(current_), max(max_), invincibilityTimer(invTimer_) {}
};

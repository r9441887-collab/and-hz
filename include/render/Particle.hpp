#pragma once
#include <cstdint>

struct Particle {
    float x, y;
    float vx, vy;
    int lifetime;
    int maxLifetime;
    uint32_t color;
    float size;
    float gravity;

    Particle();

    bool update(float dt);

    bool isAlive() const { return lifetime > 0; }
};

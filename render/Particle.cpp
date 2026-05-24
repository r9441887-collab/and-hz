#include "../../include/render/Particle.hpp"

Particle::Particle()
    : x(0.0f), y(0.0f), vx(0.0f), vy(0.0f),
      lifetime(0), maxLifetime(0), color(0xFFFFFFFF),
      size(1.0f), gravity(0.0f) {}

bool Particle::update(float dt) {
    if (lifetime <= 0) return false;

    vx *= 0.98f;
    vy += gravity * dt;
    x += vx * dt;
    y += vy * dt;
    lifetime--;

    return lifetime > 0;
}

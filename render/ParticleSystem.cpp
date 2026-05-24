#include "../../include/render/ParticleSystem.hpp"
#include "../../include/render/PixelBuffer.hpp"
#include "../../include/render/Camera.hpp"
#include <cstdlib>

ParticleSystem::ParticleSystem() {}

void ParticleSystem::emitExplosion(float x, float y, int count,
                                   uint32_t color, float speed, int lifetime) {
    for (int i = 0; i < count; ++i) {
        Particle* p = pool_.alloc();
        if (!p) break;
        float angle = (std::rand() % 360) * 3.14159f / 180.0f;
        float spd = speed * (0.5f + (std::rand() % 100) / 100.0f);
        p->x = x;
        p->y = y;
        p->vx = std::cos(angle) * spd;
        p->vy = std::sin(angle) * spd;
        p->lifetime = lifetime + (std::rand() % lifetime / 2);
        p->maxLifetime = p->lifetime;
        p->color = color;
        p->size = 1.0f + (std::rand() % 100) / 100.0f;
        p->gravity = 0.0f;
    }
}

void ParticleSystem::emitTrail(float x, float y, uint32_t color) {
    Particle* p = pool_.alloc();
    if (!p) return;
    p->x = x;
    p->y = y;
    p->vx = (std::rand() % 100 - 50) * 0.1f;
    p->vy = (std::rand() % 100 - 50) * 0.1f;
    p->lifetime = 15;
    p->maxLifetime = 15;
    p->color = color;
    p->size = 1.0f;
    p->gravity = 0.0f;
}

void ParticleSystem::emitBlood(float x, float y, int count) {
    for (int i = 0; i < count; ++i) {
        Particle* p = pool_.alloc();
        if (!p) break;
        float angle = (std::rand() % 360) * 3.14159f / 180.0f;
        float spd = 30.0f + (std::rand() % 60);
        p->x = x + (std::rand() % 10 - 5);
        p->y = y + (std::rand() % 10 - 5);
        p->vx = std::cos(angle) * spd;
        p->vy = std::sin(angle) * spd;
        p->lifetime = 20 + std::rand() % 20;
        p->maxLifetime = p->lifetime;
        p->color = 0xFFCC1111;
        p->size = 1.0f;
        p->gravity = 200.0f;
    }
}

void ParticleSystem::emitSpark(float x, float y, int count) {
    for (int i = 0; i < count; ++i) {
        Particle* p = pool_.alloc();
        if (!p) break;
        float angle = (std::rand() % 360) * 3.14159f / 180.0f;
        float spd = 50.0f + (std::rand() % 100);
        p->x = x;
        p->y = y;
        p->vx = std::cos(angle) * spd;
        p->vy = std::sin(angle) * spd;
        p->lifetime = 10 + std::rand() % 10;
        p->maxLifetime = p->lifetime;
        p->color = 0xFFFFFFAA;
        p->size = 0.5f;
        p->gravity = 50.0f;
    }
}

void ParticleSystem::update(float dt) {
    for (int i = 0; i < pool_.size(); ++i) {
        Particle* p = pool_.get(i);
        if (p->isAlive()) {
            p->update(dt);
        }
    }
}

void ParticleSystem::render(PixelBuffer& buf, Camera& cam) {
    for (int i = 0; i < pool_.size(); ++i) {
        Particle* p = pool_.get(i);
        if (!p->isAlive()) continue;

        auto [sx, sy] = cam.worldToScreen(p->x, p->y);
        int drawSize = static_cast<int>(p->size);

        float lifeRatio = static_cast<float>(p->lifetime) /
                          static_cast<float>(p->maxLifetime);

        uint32_t col = p->color;
        int a = static_cast<int>((col >> 24) & 0xFF);
        int r = static_cast<int>((col >> 16) & 0xFF);
        int g = static_cast<int>((col >> 8) & 0xFF);
        int b = static_cast<int>(col & 0xFF);
        a = static_cast<int>(a * lifeRatio);
        uint32_t faded = (static_cast<uint32_t>(a) << 24) |
                         (static_cast<uint32_t>(r) << 16) |
                         (static_cast<uint32_t>(g) << 8) |
                         static_cast<uint32_t>(b);

        buf.fillRect(sx - drawSize / 2, sy - drawSize / 2,
                     drawSize, drawSize, faded);
    }
}

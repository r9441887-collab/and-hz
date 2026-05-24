#pragma once
#include "../core/ECS.hpp"

class Explosion {
public:
    static void create(World& world, const Vec2& position, float radius, float damage, EntityId owner, float knockback = 200);
    static void spawnExplosionParticles(World& world, const Vec2& position, const Color& color, int count, float speed);
    static void applyScreenShake(World& world, float intensity, float duration);
};

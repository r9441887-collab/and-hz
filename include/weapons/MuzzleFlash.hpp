#pragma once
#include "../core/ECS.hpp"

class MuzzleFlash {
public:
    static void spawn(World& world, const Vec2& position, float angle, WeaponType type);
    static void spawnParticles(World& world, const Vec2& position, const Color& color, int count);
};

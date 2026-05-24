#pragma once
#include "../core/ECS.hpp"
#include "WeaponData.hpp"

class BulletFactory {
public:
    static Entity createBullet(World& world, float x, float y, float angle, const WeaponDef& weaponDef, EntityId owner);
    static Entity createBulletCustom(World& world, const Vec2& pos, float angle, float speed, float damage,
        float lifetime, float radius, BulletType type, EntityId owner, bool isCrit = false);
};

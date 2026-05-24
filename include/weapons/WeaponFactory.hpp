#pragma once
#include "../core/ECS.hpp"
#include "WeaponData.hpp"

class WeaponFactory {
public:
    static void equipWeapon(World& world, Entity entity, WeaponType type);
    static void refillAmmo(World& world, Entity entity);
    static void modifyDamage(World& world, Entity entity, float multiplier);
    static void reduceCooldown(World& world, Entity entity, float factor);
};

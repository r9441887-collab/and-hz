#pragma once
#include "../core/Types.hpp"
#include <array>
#include <string>

struct WeaponDef {
    std::string name;
    WeaponType type;
    float cooldown;
    int maxAmmo;
    int bulletCount;
    float damage;
    float speed;
    float spread;
    float range;
    BulletType bulletType;
    int specialEffect;
};

const std::array<WeaponDef, 10>& getAllWeaponDefs();
const WeaponDef& getWeaponDef(WeaponType type);

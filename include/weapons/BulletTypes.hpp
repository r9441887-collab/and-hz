#pragma once
#include "../core/Types.hpp"
#include <string>

struct BulletDef {
    std::string spriteName;
    float speed;
    Color color;
    bool hasTrail;
    float damage;
    float lifetime;
    float radius;
    int specialEffect;
};

const BulletDef& getBulletDef(BulletType type);

enum class BulletSpecial : uint8_t {
    NONE,
    PIERCE,
    BOUNCE,
    EXPLOSIVE,
    CHAIN_LIGHTNING,
    BOOMERANG_RETURN,
    VOID_HOLE,
    ICE_SHATTER,
    FLAME_TICK
};

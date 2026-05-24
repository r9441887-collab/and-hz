#pragma once
#include <cstdint>
#include <string>
#include <array>

enum class EnemyType : uint8_t {
    SKELETON = 0,
    SLIME = 1,
    BAT = 2,
    GOLEM = 3,
    WRAITH = 4,
    DRAGON_BOSS = 5,
    FIRE_ELEMENTAL = 6,
    CULTIST = 7,
    ZOMBIE = 8,
    SPIDER = 9,
    GHOST = 10,
    ORC = 11,
    DARK_KNIGHT = 12,
    MIMIC = 13,
    RAT = 14,
    NECROMANCER = 15,
    COUNT = 16
};

enum class AItype : uint8_t {
    CHASE = 0,
    PATROL = 1,
    RANGED = 2,
    FLYING = 3,
    BOSS = 4,
    TELEPORT = 5
};

struct EnemyDef {
    const char* name;
    int hp;
    float speed;
    int damage;
    float attackCooldown;
    float attackRange;
    int exp;
    float detectionRange;
    AItype aiType;
    const char* spriteName;
    float size;
    EnemyType type;
};

extern const std::array<EnemyDef, 16> enemyDefinitions;

const EnemyDef& getEnemyDef(EnemyType type);

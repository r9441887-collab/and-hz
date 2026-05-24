#pragma once
#include <cstdint>
#include <vector>
#include <utility>
#include "EnemyData.hpp"

enum class LootType : uint8_t {
    NOTHING = 0,
    COIN = 1,
    HEART = 2,
    WEAPON = 3,
    RARE = 4,
    AMMO = 5,
    KEY = 6
};

struct LootEntry {
    LootType type;
    int weight;
    const char* itemName;
};

struct LootTable {
    std::vector<LootEntry> entries;
};

extern const LootTable normalLoot;
extern const LootTable bossLoot;

LootEntry rollLoot(EnemyType enemy, int floor);
LootEntry rollLootTable(const LootTable& table, int floor);

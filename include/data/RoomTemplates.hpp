#pragma once
#include <cstdint>
#include <vector>
#include <utility>
#include "EnemyData.hpp"

struct SpawnEntry {
    EnemyType type;
    int weight;
};

struct RoomSpawnList {
    std::vector<SpawnEntry> entries;
    int minCount;
    int maxCount;
};

extern const RoomSpawnList easyRoom;
extern const RoomSpawnList mediumRoom;
extern const RoomSpawnList hardRoom;
extern const RoomSpawnList bossRoom;

const RoomSpawnList& getSpawnListForFloor(int floor);
int getBossFloor();

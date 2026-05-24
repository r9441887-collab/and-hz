#pragma once
#include "../core/ECS.hpp"

struct SpawnEntry {
    EnemyType type;
    Vec2 position;
    float delay;
};

class SpawnSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
    void spawnRoomEnemies(World& world, RoomComponent& room, int floor);
    Entity spawnEnemy(World& world, EnemyType type, const Vec2& position, int floor);
    void spawnMiniboss(World& world, RoomComponent& room, int floor);
    void spawnFloorBoss(World& world, RoomComponent& room, int floor);
    void spawnSpawnEffect(World& world, const Vec2& pos);
private:
    std::vector<SpawnEntry> pendingSpawns;
    void updatePendingSpawns(World& world, float dt);
};

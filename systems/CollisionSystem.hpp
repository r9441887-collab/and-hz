#pragma once
#include "../core/ECS.hpp"
#include <unordered_map>

struct Collidable {
    Entity entity;
    Collider collider;
    Vec2 position;
    EntityId owner;
    bool isProjectile;
    bool isPlayer;
    bool isEnemy;
};

class SpatialHashGrid {
public:
    static constexpr int CELL_SIZE = 64;
    void clear();
    void insert(const Collidable& col);
    std::vector<Collidable> query(const Vec2& pos, float radius) const;
private:
    int cellKey(int x, int y) const { return x * 73856093 + y * 19349663; }
    std::unordered_map<int, std::vector<Collidable>> cells;
};

class CollisionSystem {
public:
    void update(World& world, float dt);
    void render(World& world, Renderer& renderer);
    bool circleVsCircle(const Vec2& a, float ra, const Vec2& b, float rb) const;
    bool circleVsTile(const Vec2& cPos, float radius, const TileMap& map) const;
    Vec2 pushOutCircle(const Vec2& pos, float radius, const TileMap& map) const;
private:
    SpatialHashGrid grid;
    void buildGrid(World& world);
    void resolveCollisions(World& world);
    void resolveProjectileHits(World& world);
};

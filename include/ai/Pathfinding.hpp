#pragma once
#include "../core/ECS.hpp"
#include <deque>
#include <unordered_map>

struct LRUCache {
    static constexpr int MAX_ENTRIES = 16;
    struct Key { int sx, sy, tx, ty; bool operator==(const Key& o) const { return sx==o.sx&&sy==o.sy&&tx==o.tx&&ty==o.ty; } };
    struct KeyHash { size_t operator()(const Key& k) const { return k.sx*73856093 ^ k.sy*19349663 ^ k.tx*83492791 ^ k.ty*50331653; } };
    std::unordered_map<Key, std::vector<Vec2>, KeyHash> cache;
    std::deque<Key> order;
    bool get(const Key& key, std::vector<Vec2>& result);
    void put(const Key& key, std::vector<Vec2> path);
};

class Pathfinding {
public:
    Pathfinding() = default;
    std::vector<Vec2> findPath(const TileMap& map, const Vec2& start, const Vec2& end);
    std::vector<Vec2> findPathGrid(const TileMap& map, int sx, int sy, int tx, int ty);
    bool isReachable(const TileMap& map, const Vec2& start, const Vec2& end);
    Vec2 getNearestReachable(const TileMap& map, const Vec2& start, const Vec2& target);
private:
    static constexpr int TILE_WALL_COST = 999999;
    static constexpr int TILE_FLOOR_COST = 1;
    static constexpr int TILE_WATER_COST = 3;
    float heuristic(int ax, int ay, int bx, int by) const;
    std::vector<Vec2> reconstructPath(PathNode* node);
    std::vector<Vec2> smoothPath(const TileMap& map, const std::vector<Vec2>& path);
    LRUCache cache;
};

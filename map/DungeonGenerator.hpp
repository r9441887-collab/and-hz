#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "TileMap.hpp"
#include "GraphGenerator.hpp"

enum class Biome : uint8_t {
    CATACOMBS = 0,
    CRYPT = 1,
    FOUNDRY = 2
};

struct RoomData {
    int id;
    RoomType type;
    int x, y, w, h;
    int centerX, centerY;
    std::vector<std::pair<int,int>> enemySpawns;
    std::vector<std::pair<int,int>> lootSpawns;
};

class DungeonGenerator {
public:
    DungeonGenerator();

    void generate(int floor);
    void setSeed(int seed);
    void setBiome(Biome b);

    TileMap& getTileMap() { return map_; }
    const TileMap& getTileMap() const { return map_; }
    const std::vector<RoomData>& getRoomData() const { return rooms_; }
    std::pair<int,int> getStartPosition() const;

private:
    TileMap map_;
    GraphGenerator graph_;
    std::vector<RoomData> rooms_;
    Biome biome_;
    int seed_;
    int floor_;

    void assignRoomTypes(const std::vector<RoomNode>& nodes);
    void generateGeometry();
    void connectRooms();
    void placeDoors();
    void assignEnemies();
    void assignLoot();
    void postProcess();
    bool floodFillCheck() const;
};

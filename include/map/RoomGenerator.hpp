#pragma once
#include <cstdint>
#include "GraphGenerator.hpp"
#include "TileMap.hpp"

class RoomGenerator {
public:
    RoomGenerator();

    void generateRoom(TileMap& map, const RoomNode& node,
                      RoomType type, int seed);

private:
    void carveRoom(TileMap& map, int x, int y, int w, int h);
    void addPillars(TileMap& map, int x, int y, int w, int h);
    void addPits(TileMap& map, int x, int y, int w, int h);
    void placeDoors(TileMap& map, const RoomNode& node);
};

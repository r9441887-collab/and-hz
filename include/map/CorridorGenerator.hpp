#pragma once
#include "TileMap.hpp"

class CorridorGenerator {
public:
    CorridorGenerator();

    void generateCorridor(TileMap& map,
                          int x1, int y1, int x2, int y2,
                          int roomId);
};

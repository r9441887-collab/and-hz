#pragma once
#include "TileMap.hpp"

class PixelBuffer;
class Camera;

class TileRenderer {
public:
    TileRenderer();

    void renderTiles(PixelBuffer& buf, const TileMap& map,
                     const Camera& cam);
    void renderShadows(PixelBuffer& buf, const TileMap& map,
                       const Camera& cam);

private:
    uint8_t calcNeighborMask(const TileMap& map, int x, int y) const;
};

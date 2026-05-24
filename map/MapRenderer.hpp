#pragma once
#include <cstdint>
#include "TileMap.hpp"
#include "../render/Camera.hpp"

class PixelBuffer;

class MapRenderer {
public:
    MapRenderer();

    void render(PixelBuffer& buf, const TileMap& map,
                const Camera& cam, uint32_t biomePalette[5]);

    void setBiomePalette(uint32_t floor, uint32_t wall,
                         uint32_t door, uint32_t pit, uint32_t water);

private:
    uint32_t floorColor_;
    uint32_t wallColor_;
    uint32_t doorColor_;
    uint32_t pitColor_;
    uint32_t waterColor_;
};

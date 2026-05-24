#pragma once
#include <cstdint>
#include <vector>

enum class TileType : uint8_t {
    EMPTY = 0,
    FLOOR = 1,
    WALL = 2,
    DOOR = 3,
    PIT = 4,
    WATER = 5
};

struct Tile {
    TileType type;
    int roomId;
    bool visible;
    bool explored;
    uint8_t variant;

    Tile() : type(TileType::EMPTY), roomId(-1),
             visible(false), explored(false), variant(0) {}
};

class TileMap {
public:
    TileMap();
    TileMap(int width, int height);

    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;
    void setTile(int x, int y, const Tile& tile);
    bool isWalkable(int x, int y) const;
    bool isTransparent(int x, int y) const;

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    void resize(int w, int h);

    bool inBounds(int x, int y) const;

private:
    int width_, height_;
    std::vector<Tile> tiles_;
};

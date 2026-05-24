#pragma once
#include "../core/ECS.hpp"

class Minimap {
public:
    Minimap();
    void render(PixelBuffer& buffer, World& world, Entity player, int offsetX, int offsetY);
    void setVisible(bool v) { visible = v; }
    bool isVisible() const { return visible; }
private:
    static constexpr int MAP_W = 60;
    static constexpr int MAP_H = 40;
    static constexpr int ROOM_PX = 4;
    static constexpr int ROOM_PY = 3;
    bool visible = true;
    PixelBuffer mapBuffer;
    void renderRoom(PixelBuffer& buf, const RoomComponent& room, int ox, int oy, const Vec2& playerPos);
    void renderDoors(PixelBuffer& buf, const RoomComponent& room, int ox, int oy);
    void renderEntities(PixelBuffer& buf, World& world, const RoomComponent& room, int ox, int oy, const Vec2& playerPos);
    void renderPlayer(PixelBuffer& buf, const Vec2& playerPos, int ox, int oy, float time);
};

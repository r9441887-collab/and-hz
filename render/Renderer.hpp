#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "PixelBuffer.hpp"
#include "Camera.hpp"
#include "Font.hpp"
#include "ParticleSystem.hpp"
#include "Sprite.hpp"

struct Entity {
    float x, y;
    int w, h;
    uint32_t color;
    const Sprite* sprite;
    int tileX, tileY;
    float sortY;
};

class Renderer {
public:
    Renderer();

    void renderFloor(const class TileMap& map);
    void renderEntities(const std::vector<Entity*>& entities);
    void renderParticles();
    void renderHUD(uint32_t health, uint32_t maxHealth,
                   int ammo, int coins, int keys, int floor);
    uint32_t* present();

    void drawSprite(const Sprite& spr, int x, int y,
                    bool flipX = false, bool flipY = false);
    void drawText(const std::string& text, int x, int y, uint32_t color);

    PixelBuffer& getBuffer() { return buffer_; }
    Camera& getCamera() { return camera_; }
    Font& getFont() { return font_; }

    void setFlash(uint32_t color, float duration);
    void update(float dt);

private:
    PixelBuffer buffer_;
    Camera camera_;
    Font font_;
    ParticleSystem particles_;
    uint32_t flashColor_;
    float flashTimer_;
};

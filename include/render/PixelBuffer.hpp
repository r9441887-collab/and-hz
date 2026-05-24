#pragma once
#include <cstdint>
#include <string>
#include <utility>
#include "Sprite.hpp"

class Font;

class PixelBuffer {
public:
    static const int WIDTH = 480;
    static const int HEIGHT = 270;

    PixelBuffer();
    ~PixelBuffer() = default;

    void setPixel(int x, int y, uint32_t color);
    uint32_t getPixel(int x, int y) const;
    void fill(uint32_t color);
    void clear(uint32_t color);
    void fillRect(int x, int y, int w, int h, uint32_t color);
    void drawRect(int x, int y, int w, int h, uint32_t color);
    void drawLine(int x1, int y1, int x2, int y2, uint32_t color);
    void drawCircle(int cx, int cy, int r, uint32_t color);
    void fillCircle(int cx, int cy, int r, uint32_t color);

    void blitSprite(const Sprite& spr, int x, int y,
                    bool flipX = false, bool flipY = false,
                    float alpha = 1.0f);
    void blitSpriteRotated(const Sprite& spr, int x, int y, float angle);
    void blitSpriteScaled(const Sprite& spr, int x, int y, float sx, float sy);
    void drawText(const std::string& text, int x, int y,
                  const Font& font, uint32_t color);
    void applyVignette(float strength);
    void applyScreenShake(int offsetX, int offsetY);

    uint32_t* getBuffer();
    const uint32_t* getBuffer() const;

private:
    uint32_t buffer_[WIDTH * HEIGHT];
};

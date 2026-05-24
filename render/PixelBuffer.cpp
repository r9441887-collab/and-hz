#include "../../include/render/PixelBuffer.hpp"
#include "../../include/render/Font.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>

static uint32_t blendAlpha(uint32_t dst, uint32_t src, float alpha) {
    if (alpha >= 1.0f) return src;
    if (alpha <= 0.0f) return dst;
    int sa = static_cast<int>((src >> 24) & 0xFF);
    int sr = static_cast<int>((src >> 16) & 0xFF);
    int sg = static_cast<int>((src >> 8) & 0xFF);
    int sb = static_cast<int>(src & 0xFF);

    int da = static_cast<int>((dst >> 24) & 0xFF);
    int dr = static_cast<int>((dst >> 16) & 0xFF);
    int dg = static_cast<int>((dst >> 8) & 0xFF);
    int db = static_cast<int>(dst & 0xFF);

    float a = alpha * (sa / 255.0f);
    float invA = 1.0f - a;

    int ra = static_cast<int>((a * 255 + invA * da));
    int rr = static_cast<int>((a * sr + invA * dr));
    int rg = static_cast<int>((a * sg + invA * dg));
    int rb = static_cast<int>((a * sb + invA * db));

    if (ra > 255) ra = 255;
    if (rr > 255) rr = 255;
    if (rg > 255) rg = 255;
    if (rb > 255) rb = 255;

    return (static_cast<uint32_t>(ra) << 24) |
           (static_cast<uint32_t>(rr) << 16) |
           (static_cast<uint32_t>(rg) << 8) |
           static_cast<uint32_t>(rb);
}

PixelBuffer::PixelBuffer() {
    fill(0xFF000000);
}

void PixelBuffer::setPixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    buffer_[y * WIDTH + x] = color;
}

uint32_t PixelBuffer::getPixel(int x, int y) const {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;
    return buffer_[y * WIDTH + x];
}

void PixelBuffer::fill(uint32_t color) {
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        buffer_[i] = color;
    }
}

void PixelBuffer::clear(uint32_t color) {
    fill(color);
}

void PixelBuffer::fillRect(int x, int y, int w, int h, uint32_t color) {
    for (int j = 0; j < h; ++j) {
        int cy = y + j;
        if (cy < 0 || cy >= HEIGHT) continue;
        for (int i = 0; i < w; ++i) {
            int cx = x + i;
            if (cx < 0 || cx >= WIDTH) continue;
            buffer_[cy * WIDTH + cx] = color;
        }
    }
}

void PixelBuffer::drawRect(int x, int y, int w, int h, uint32_t color) {
    for (int i = 0; i < w; ++i) {
        setPixel(x + i, y, color);
        setPixel(x + i, y + h - 1, color);
    }
    for (int j = 0; j < h; ++j) {
        setPixel(x, y + j, color);
        setPixel(x + w - 1, y + j, color);
    }
}

void PixelBuffer::drawLine(int x1, int y1, int x2, int y2, uint32_t color) {
    int dx = std::abs(x2 - x1);
    int dy = -std::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        setPixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void PixelBuffer::drawCircle(int cx, int cy, int r, uint32_t color) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y) {
        setPixel(cx + x, cy + y, color);
        setPixel(cx - x, cy + y, color);
        setPixel(cx + x, cy - y, color);
        setPixel(cx - x, cy - y, color);
        setPixel(cx + y, cy + x, color);
        setPixel(cx - y, cy + x, color);
        setPixel(cx + y, cy - x, color);
        setPixel(cx - y, cy - x, color);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void PixelBuffer::fillCircle(int cx, int cy, int r, uint32_t color) {
    for (int y = -r; y <= r; ++y) {
        int absy = std::abs(y);
        if (absy > r) continue;
        int width = static_cast<int>(std::sqrt(static_cast<float>(r * r - absy * absy)));
        for (int x = -width; x <= width; ++x) {
            setPixel(cx + x, cy + y, color);
        }
    }
}

void PixelBuffer::blitSprite(const Sprite& spr, int x, int y,
                              bool flipX, bool flipY, float alpha) {
    for (int j = 0; j < spr.h; ++j) {
        for (int i = 0; i < spr.w; ++i) {
            int sx = flipX ? (spr.w - 1 - i) : i;
            int sy = flipY ? (spr.h - 1 - j) : j;
            uint32_t pixel = spr.pixels[sy * spr.w + sx];

            if ((pixel & 0x00FFFFFF) == 0x00FF00FF) continue;

            int dx = x + i;
            int dy = y + j;
            if (dx < 0 || dx >= WIDTH || dy < 0 || dy >= HEIGHT) continue;

            if (alpha >= 1.0f) {
                buffer_[dy * WIDTH + dx] = pixel;
            } else {
                buffer_[dy * WIDTH + dx] = blendAlpha(buffer_[dy * WIDTH + dx], pixel, alpha);
            }
        }
    }
}

void PixelBuffer::blitSpriteRotated(const Sprite& spr, int x, int y, float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    int halfW = spr.w / 2;
    int halfH = spr.h / 2;

    for (int j = 0; j < spr.h; ++j) {
        for (int i = 0; i < spr.w; ++i) {
            uint32_t pixel = spr.pixels[j * spr.w + i];
            if ((pixel & 0x00FFFFFF) == 0x00FF00FF) continue;

            float rx = static_cast<float>(i - halfW);
            float ry = static_cast<float>(j - halfH);
            int dx = x + static_cast<int>(rx * cosA - ry * sinA);
            int dy = y + static_cast<int>(rx * sinA + ry * cosA);

            if (dx < 0 || dx >= WIDTH || dy < 0 || dy >= HEIGHT) continue;
            buffer_[dy * WIDTH + dx] = pixel;
        }
    }
}

void PixelBuffer::blitSpriteScaled(const Sprite& spr, int x, int y,
                                    float sx, float sy) {
    int newW = static_cast<int>(spr.w * sx);
    int newH = static_cast<int>(spr.h * sy);
    if (newW <= 0 || newH <= 0) return;

    for (int j = 0; j < newH; ++j) {
        for (int i = 0; i < newW; ++i) {
            int srcX = static_cast<int>(i / sx);
            int srcY = static_cast<int>(j / sy);
            if (srcX >= spr.w) srcX = spr.w - 1;
            if (srcY >= spr.h) srcY = spr.h - 1;

            uint32_t pixel = spr.pixels[srcY * spr.w + srcX];
            if ((pixel & 0x00FFFFFF) == 0x00FF00FF) continue;

            int dx = x + i;
            int dy = y + j;
            if (dx < 0 || dx >= WIDTH || dy < 0 || dy >= HEIGHT) continue;
            buffer_[dy * WIDTH + dx] = pixel;
        }
    }
}

void PixelBuffer::drawText(const std::string& text, int x, int y,
                            const Font& font, uint32_t color) {
    font.drawString(*this, text, x, y, color);
}

void PixelBuffer::applyVignette(float strength) {
    float cx = WIDTH / 2.0f;
    float cy = HEIGHT / 2.0f;
    float maxDist = std::sqrt(cx * cx + cy * cy);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float dx = x - cx;
            float dy = y - cy;
            float dist = std::sqrt(dx * dx + dy * dy) / maxDist;
            float darken = dist * strength;
            if (darken > 1.0f) darken = 1.0f;

            uint32_t& pixel = buffer_[y * WIDTH + x];
            int r = static_cast<int>((pixel >> 16) & 0xFF);
            int g = static_cast<int>((pixel >> 8) & 0xFF);
            int b = static_cast<int>(pixel & 0xFF);

            r = static_cast<int>(r * (1.0f - darken));
            g = static_cast<int>(g * (1.0f - darken));
            b = static_cast<int>(b * (1.0f - darken));

            pixel = 0xFF000000 |
                    (static_cast<uint32_t>(r) << 16) |
                    (static_cast<uint32_t>(g) << 8) |
                    static_cast<uint32_t>(b);
        }
    }
}

void PixelBuffer::applyScreenShake(int offsetX, int offsetY) {
    uint32_t temp[WIDTH * HEIGHT];
    std::memcpy(temp, buffer_, sizeof(uint32_t) * WIDTH * HEIGHT);
    fill(0xFF000000);

    for (int y = 0; y < HEIGHT; ++y) {
        int sy = y + offsetY;
        if (sy < 0 || sy >= HEIGHT) continue;
        for (int x = 0; x < WIDTH; ++x) {
            int sx = x + offsetX;
            if (sx < 0 || sx >= WIDTH) continue;
            buffer_[y * WIDTH + x] = temp[sy * WIDTH + sx];
        }
    }
}

uint32_t* PixelBuffer::getBuffer() {
    return buffer_;
}

const uint32_t* PixelBuffer::getBuffer() const {
    return buffer_;
}

#pragma once
#include <cstdint>

#define RGBA(r,g,b,a) (((a)&0xFF)<<24|((r)&0xFF)<<16|((g)&0xFF)<<8|((b)&0xFF))

namespace Color {
    constexpr uint32_t WHITE     = 0xFFFFFFFF;
    constexpr uint32_t BLACK     = 0xFF000000;
    constexpr uint32_t RED       = 0xFFFF0000;
    constexpr uint32_t GREEN     = 0xFF00FF00;
    constexpr uint32_t BLUE      = 0xFF0000FF;
    constexpr uint32_t YELLOW    = 0xFFFFFF00;
    constexpr uint32_t CYAN      = 0xFF00FFFF;
    constexpr uint32_t MAGENTA   = 0xFFFF00FF;
    constexpr uint32_t ORANGE    = 0xFFFF8800;
    constexpr uint32_t PURPLE    = 0xFF8800FF;
    constexpr uint32_t GRAY      = 0xFF888888;
    constexpr uint32_t DARK_GRAY = 0xFF444444;

    inline uint32_t lerpColor(uint32_t a, uint32_t b, float t) {
        uint8_t ar = (a >> 16) & 0xFF;
        uint8_t ag = (a >> 8) & 0xFF;
        uint8_t ab = a & 0xFF;
        uint8_t aa = (a >> 24) & 0xFF;
        uint8_t br = (b >> 16) & 0xFF;
        uint8_t bg = (b >> 8) & 0xFF;
        uint8_t bb = b & 0xFF;
        uint8_t ba = (b >> 24) & 0xFF;
        uint8_t r = static_cast<uint8_t>(ar + (br - ar) * t);
        uint8_t g = static_cast<uint8_t>(ag + (bg - ag) * t);
        uint8_t bv = static_cast<uint8_t>(ab + (bb - ab) * t);
        uint8_t a_ = static_cast<uint8_t>(aa + (ba - aa) * t);
        return (static_cast<uint32_t>(a_) << 24) |
               (static_cast<uint32_t>(r) << 16) |
               (static_cast<uint32_t>(g) << 8) |
               static_cast<uint32_t>(bv);
    }

    inline uint32_t multiplyAlpha(uint32_t color, uint8_t alpha) {
        uint32_t a = (color >> 24) & 0xFF;
        uint32_t r = (color >> 16) & 0xFF;
        uint32_t g = (color >> 8) & 0xFF;
        uint32_t b = color & 0xFF;
        uint32_t fa = alpha;
        a = (a * fa) / 255;
        r = (r * fa) / 255;
        g = (g * fa) / 255;
        b = (b * fa) / 255;
        return (a << 24) | (r << 16) | (g << 8) | b;
    }

    inline uint32_t addBlend(uint32_t a, uint32_t b) {
        uint32_t ar = (a >> 16) & 0xFF;
        uint32_t ag = (a >> 8) & 0xFF;
        uint32_t ab = a & 0xFF;
        uint32_t aa = (a >> 24) & 0xFF;
        uint32_t br = (b >> 16) & 0xFF;
        uint32_t bg = (b >> 8) & 0xFF;
        uint32_t bb = b & 0xFF;
        uint32_t ba = (b >> 24) & 0xFF;
        uint8_t r = static_cast<uint8_t>(std::min(ar + br, 255u));
        uint8_t g = static_cast<uint8_t>(std::min(ag + bg, 255u));
        uint8_t bv = static_cast<uint8_t>(std::min(ab + bb, 255u));
        uint8_t a_ = static_cast<uint8_t>(std::min(aa + ba, 255u));
        return (static_cast<uint32_t>(a_) << 24) |
               (static_cast<uint32_t>(r) << 16) |
               (static_cast<uint32_t>(g) << 8) |
               static_cast<uint32_t>(bv);
    }

    inline uint32_t screenBlend(uint32_t a, uint32_t b) {
        uint32_t ar = (a >> 16) & 0xFF;
        uint32_t ag = (a >> 8) & 0xFF;
        uint32_t ab = a & 0xFF;
        uint32_t br = (b >> 16) & 0xFF;
        uint32_t bg = (b >> 8) & 0xFF;
        uint32_t bb = b & 0xFF;
        uint8_t r = static_cast<uint8_t>(255 - ((255 - ar) * (255 - br)) / 255);
        uint8_t g = static_cast<uint8_t>(255 - ((255 - ag) * (255 - bg)) / 255);
        uint8_t bv = static_cast<uint8_t>(255 - ((255 - ab) * (255 - bb)) / 255);
        return (0xFF000000) |
               (static_cast<uint32_t>(r) << 16) |
               (static_cast<uint32_t>(g) << 8) |
               static_cast<uint32_t>(bv);
    }
}

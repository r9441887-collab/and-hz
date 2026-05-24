#pragma once
#include <cstdint>
#include <vector>
#include <string_view>

struct Sprite {
    int w, h;
    std::vector<uint32_t> pixels;

    Sprite() : w(0), h(0) {}
    Sprite(int w_, int h_, const uint32_t* data);
    static Sprite fromRaw(int w_, int h_, const uint32_t* data);
};

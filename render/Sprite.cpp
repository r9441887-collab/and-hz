#include "../../include/render/Sprite.hpp"
#include <cstring>

Sprite::Sprite(int w_, int h_, const uint32_t* data)
    : w(w_), h(h_)
{
    if (data && w > 0 && h > 0) {
        pixels.assign(data, data + w * h);
    }
}

Sprite Sprite::fromRaw(int w_, int h_, const uint32_t* data) {
    return Sprite(w_, h_, data);
}

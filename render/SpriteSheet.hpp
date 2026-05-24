#pragma once
#include <vector>
#include "Sprite.hpp"

class SpriteSheet {
public:
    SpriteSheet() = default;
    SpriteSheet(const Sprite& sheet, int tileW, int tileH);

    const Sprite& getSprite(int index) const;
    int count() const;

private:
    std::vector<Sprite> sprites_;
};

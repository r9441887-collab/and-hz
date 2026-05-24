#include "../../include/render/SpriteSheet.hpp"

SpriteSheet::SpriteSheet(const Sprite& sheet, int tileW, int tileH) {
    int cols = sheet.w / tileW;
    int rows = sheet.h / tileH;
    sprites_.reserve(cols * rows);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Sprite spr(tileW, tileH, nullptr);
            int srcX = col * tileW;
            int srcY = row * tileH;
            for (int j = 0; j < tileH; ++j) {
                for (int i = 0; i < tileW; ++i) {
                    spr.pixels[j * tileW + i] =
                        sheet.pixels[(srcY + j) * sheet.w + (srcX + i)];
                }
            }
            sprites_.push_back(std::move(spr));
        }
    }
}

const Sprite& SpriteSheet::getSprite(int index) const {
    return sprites_[index];
}

int SpriteSheet::count() const {
    return static_cast<int>(sprites_.size());
}

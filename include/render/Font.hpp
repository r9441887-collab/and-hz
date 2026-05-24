#pragma once
#include <string>
#include <cstdint>

class PixelBuffer;

class Font {
public:
    static const int GLYPH_W = 8;
    static const int GLYPH_H = 8;
    static const int FIRST_CHAR = 32;
    static const int LAST_CHAR = 126;

    Font();

    void drawChar(PixelBuffer& buf, char c, int x, int y, uint32_t color) const;
    void drawString(PixelBuffer& buf, const std::string& text,
                    int x, int y, uint32_t color) const;

    int stringWidth(const std::string& text) const;

private:
    static const uint32_t glyphData_[95][GLYPH_H];
};

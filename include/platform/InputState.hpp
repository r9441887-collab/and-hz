#pragma once
#include <cstdint>

struct InputState {
    bool keys[256]{};
    bool keysPressed[256]{};
    bool keysReleased[256]{};

    int mouseX{0};
    int mouseY{0};
    int mouseDX{0};
    int mouseDY{0};
    bool mouseButtons[5]{};
    bool mouseButtonsPressed[5]{};
    bool mouseButtonsReleased[5]{};
    int mouseWheel{0};

    void resetPerFrame() {
        for (int i = 0; i < 256; ++i) {
            keysPressed[i] = false;
            keysReleased[i] = false;
        }
        for (int i = 0; i < 5; ++i) {
            mouseButtonsPressed[i] = false;
            mouseButtonsReleased[i] = false;
        }
        mouseDX = 0;
        mouseDY = 0;
        mouseWheel = 0;
    }
};

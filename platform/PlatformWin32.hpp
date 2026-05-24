#pragma once
#include "../../include/platform/Platform.hpp"
#include <string>

class PlatformWin32 : public IPlatform {
    struct Impl;
    Impl* m{nullptr};
    InputState inputState;
    uint64_t ticksPerMs{0};
    uint64_t startTick{0};

public:
    PlatformWin32();
    ~PlatformWin32() override;

    bool createWindow(const char* title, int w, int h) override;
    void destroyWindow() override;
    bool pumpMessages() override;
    void present(uint32_t* pixelBuffer, int w, int h) override;
    InputState getInput() override;
    uint64_t getTicksMs() override;
    void sleepMs(int ms) override;
};

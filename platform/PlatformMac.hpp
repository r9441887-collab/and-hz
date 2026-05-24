#pragma once
#include "../../include/platform/Platform.hpp"

class PlatformMac : public IPlatform {
    struct Impl;
    Impl* m{nullptr};
    InputState inputState;

public:
    PlatformMac();
    ~PlatformMac() override;

    bool createWindow(const char* title, int w, int h) override;
    void destroyWindow() override;
    bool pumpMessages() override;
    void present(uint32_t* pixelBuffer, int w, int h) override;
    InputState getInput() override;
    uint64_t getTicksMs() override;
    void sleepMs(int ms) override;
};

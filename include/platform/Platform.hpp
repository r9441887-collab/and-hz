#pragma once
#include <cstdint>
#include "../../include/platform/InputState.hpp"

class IPlatform {
public:
    virtual ~IPlatform() = default;
    virtual bool createWindow(const char* title, int w, int h) = 0;
    virtual void destroyWindow() = 0;
    virtual bool pumpMessages() = 0;
    virtual void present(uint32_t* pixelBuffer, int w, int h) = 0;
    virtual InputState getInput() = 0;
    virtual uint64_t getTicksMs() = 0;
    virtual void sleepMs(int ms) = 0;
};

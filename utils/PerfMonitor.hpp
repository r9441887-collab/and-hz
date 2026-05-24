#pragma once
#include <cstdint>

class PerfMonitor {
    static constexpr int SAMPLE_COUNT = 60;
    float frameTimes[SAMPLE_COUNT]{};
    int currentIndex{0};
    int sampleCount{0};
    float totalTime{0.0f};
    uint64_t lastFrameTick{0};

public:
    PerfMonitor();
    void beginFrame();
    void endFrame();
    float getFrameTime() const;
    float getAverageFrameTime() const;
    float getFPS() const;
    float getMinFrameTime() const;
    float getMaxFrameTime() const;
};

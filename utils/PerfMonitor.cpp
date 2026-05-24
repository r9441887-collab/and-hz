#include "../../include/utils/PerfMonitor.hpp"
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#else
#include <chrono>
#endif

static uint64_t getTick() {
#ifdef _WIN32
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return counter.QuadPart * 1000000 / freq.QuadPart;
#else
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
#endif
}

PerfMonitor::PerfMonitor() {
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        frameTimes[i] = 0.0f;
    }
    lastFrameTick = getTick();
}

void PerfMonitor::beginFrame() {
    lastFrameTick = getTick();
}

void PerfMonitor::endFrame() {
    uint64_t now = getTick();
    float elapsed = (now - lastFrameTick) / 1000000.0f;
    totalTime -= frameTimes[currentIndex];
    frameTimes[currentIndex] = elapsed;
    totalTime += elapsed;
    currentIndex = (currentIndex + 1) % SAMPLE_COUNT;
    if (sampleCount < SAMPLE_COUNT) ++sampleCount;
}

float PerfMonitor::getFrameTime() const {
    int idx = (currentIndex == 0) ? SAMPLE_COUNT - 1 : currentIndex - 1;
    return frameTimes[idx];
}

float PerfMonitor::getAverageFrameTime() const {
    if (sampleCount == 0) return 0.0f;
    return totalTime / static_cast<float>(sampleCount);
}

float PerfMonitor::getFPS() const {
    float avg = getAverageFrameTime();
    return (avg > 0.0f) ? 1.0f / avg : 0.0f;
}

float PerfMonitor::getMinFrameTime() const {
    float minVal = 1e10f;
    int count = (sampleCount > 0) ? sampleCount : 1;
    for (int i = 0; i < count; ++i) {
        if (frameTimes[i] > 0 && frameTimes[i] < minVal) {
            minVal = frameTimes[i];
        }
    }
    return (minVal > 1e9f) ? 0.0f : minVal;
}

float PerfMonitor::getMaxFrameTime() const {
    float maxVal = 0.0f;
    int count = (sampleCount > 0) ? sampleCount : 1;
    for (int i = 0; i < count; ++i) {
        if (frameTimes[i] > maxVal) {
            maxVal = frameTimes[i];
        }
    }
    return maxVal;
}

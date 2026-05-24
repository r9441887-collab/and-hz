#include "../../include/core/Time.hpp"
#include <thread>
#include <algorithm>
#include <numeric>

Time& Time::instance() {
    static Time inst;
    return inst;
}

Time::Time() {
    lastFrame_ = Clock::now();
    std::fill(std::begin(dtHistory_), std::end(dtHistory_), 1.0f / 60.0f);
}

void Time::tick() {
    TimePoint now = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrame_);
    lastFrame_ = now;

    float dt = duration.count() / 1000000.0f;
    if (dt < 0.0f) dt = 0.0f;
    if (dt > 0.1f) dt = 0.1f;

    deltaTime_ = dt;
    totalTime_ += dt;

    dtHistory_[dtIndex_] = dt;
    dtIndex_ = (dtIndex_ + 1) % SMOOTHING_FRAMES;

    float sum = 0.0f;
    for (int i = 0; i < SMOOTHING_FRAMES; ++i) {
        sum += dtHistory_[i];
    }
    smoothDeltaTime_ = sum / static_cast<float>(SMOOTHING_FRAMES);

    fps_ = dt > 0.0f ? (1.0f / dt) : 0.0f;

    waitForTargetFPS();
}

float Time::getDeltaTime() const {
    return deltaTime_;
}

float Time::getSmoothDeltaTime() const {
    return smoothDeltaTime_;
}

float Time::getFPS() const {
    return fps_;
}

float Time::getTotalTime() const {
    return totalTime_;
}

void Time::waitForTargetFPS() {
    float targetFrameTime = 1.0f / 60.0f;
    float currentFrameTime = deltaTime_;

    auto now = Clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
        now - lastFrame_).count() / 1000000.0f;

    float waitTime = std::max(0.0f, targetFrameTime - currentFrameTime - elapsed);
    if (waitTime > 0.001f) {
        std::this_thread::sleep_for(
            std::chrono::microseconds(static_cast<int>(waitTime * 1000000.0f)));
    }
}

#pragma once
#include <chrono>

class Time {
public:
    static Time& instance();

    void tick();

    float getDeltaTime() const;
    float getSmoothDeltaTime() const;
    float getFPS() const;
    float getTotalTime() const;

private:
    Time();
    ~Time() = default;
    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;

    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint lastFrame_;
    float deltaTime_ = 0.0f;
    float smoothDeltaTime_ = 0.0f;
    float totalTime_ = 0.0f;
    float fps_ = 0.0f;

    static constexpr int SMOOTHING_FRAMES = 10;
    float dtHistory_[SMOOTHING_FRAMES]{};
    int dtIndex_ = 0;

    void waitForTargetFPS();
};

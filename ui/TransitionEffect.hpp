#pragma once
#include "../core/ECS.hpp"

enum class TransitionType : uint8_t {
    FADE, SLIDE, IRIS
};

class TransitionEffect {
public:
    TransitionEffect();
    void start(TransitionType type, float duration, bool fadingOut);
    void update(float dt);
    void render(PixelBuffer& buffer);
    bool isComplete() const { return progress >= 1.0f; }
    bool isFadingOut() const { return fadingOut; }
    float getProgress() const { return progress; }
    void setCallback(std::function<void()> cb) { callback = cb; }
private:
    TransitionType type = TransitionType::FADE;
    float duration = 1.0f;
    float progress = 0;
    bool fadingOut = true;
    bool started = false;
    std::function<void()> callback;
    void renderFade(PixelBuffer& buffer);
    void renderSlide(PixelBuffer& buffer);
    void renderIris(PixelBuffer& buffer);
};

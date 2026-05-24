#pragma once
#include <cstdint>
#include <utility>

struct Rect {
    float x, y, w, h;
    Rect() : x(0), y(0), w(0), h(0) {}
    Rect(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {}
};

class Camera {
public:
    Camera();

    void follow(float targetX, float targetY, float smoothness);
    std::pair<int, int> worldToScreen(float wx, float wy) const;
    std::pair<float, float> screenToWorld(int sx, int sy) const;

    void shake(int frames, float intensity);
    Rect getViewRect() const;

    float getX() const { return x_; }
    float getY() const { return y_; }
    int getShakeOffsetX() const { return shakeOffX_; }
    int getShakeOffsetY() const { return shakeOffY_; }

    void update(float dt);

private:
    float x_, y_;
    int shakeFrames_;
    float shakeIntensity_;
    int shakeOffX_, shakeOffY_;
};
